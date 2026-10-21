
#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

/*
 * Exercise Q20 - Capstone: Animated Ship Over Indexed Ground
  ----------------------------------------------------------
 Objective: Practice combining VBO animation, indexed drawing,
 and proper buffer cleanup in one program.
 This program moves a pastel-colored ship above a static teal
 ground and releases all four VBOs when ESC is pressed.
 */

GLuint shipPosVBO, shipColorVBO, groundVBO, groundIndexVBO;

float offsetX = 0.0f;
float direction = 0.1f;

void buildScene() {
    GLfloat shipPositions[] = {
         0.0f,  0.45f, 0.0f,  // Top
        -0.3f, -0.1f,  0.0f,  // Bottom left
         0.3f, -0.1f,  0.0f   // Bottom right
    };

    GLfloat shipColors[] = {
        1.0f, 0.5f, 0.7f,  // Pink
        0.4f, 0.9f, 0.9f,  // Turquoise
        1.0f, 0.85f, 0.4f // Yellow
    };

    GLfloat groundVertices[] = {
        -0.9f, -0.9f, 0.0f,  // Bottom left
         0.9f, -0.9f, 0.0f,  // Bottom right
         0.9f, -0.6f, 0.0f,  // Top right
        -0.9f, -0.6f, 0.0f   // Top left
    };

    GLubyte groundIndices[] = { 0, 1, 2, 0, 2, 3 };

    glGenBuffers(1, &shipPosVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(shipPositions),
                 shipPositions, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &shipColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(shipColors),
                 shipColors, GL_STATIC_DRAW);

    glGenBuffers(1, &groundVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices),
                 groundVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &groundIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices),
                 groundIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawGround() {
    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);

    glColor3f(0.1f, 0.55f, 0.6f);  // Dark teal
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawShip() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, shipColorVBO);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGround();
    drawShip();
    glFlush();
}

void animateStep(int value) {
    if (offsetX >= 0.5f || offsetX <= -0.5f) {
        direction = -direction;
    }

    glBindBuffer(GL_ARRAY_BUFFER, shipPosVBO);
    GLfloat* mapped = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (mapped != nullptr) {
        // Move all three ship vertices
        mapped[0] += direction;
        mapped[3] += direction;
        mapped[6] += direction;

        glUnmapBuffer(GL_ARRAY_BUFFER);
        offsetX += direction;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, animateStep, 0);
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        // Release all four buffers before closing
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDeleteBuffers(1, &shipPosVBO);
        glDeleteBuffers(1, &shipColorVBO);
        glDeleteBuffers(1, &groundVBO);
        glDeleteBuffers(1, &groundIndexVBO);

        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q20 - Animated Ship Over Indexed Ground");

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        buildScene();
        glutTimerFunc(1000, animateStep, 0);
        glutMainLoop();
    }
#else
    buildScene();
    glutTimerFunc(1000, animateStep, 0);
    glutMainLoop();
#endif

    return 0;
}
