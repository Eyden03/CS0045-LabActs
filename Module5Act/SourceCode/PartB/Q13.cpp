
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
 * Exercise Q13 - ESC Cleanup Releasing Two VBOs
  ----------------------------------------------
 Objective: Practice releasing two VBOs before exiting the program.
 This program draws a lavender diamond and a mint green triangle
 using separate VBOs and deletes both buffers when ESC is pressed.
 */

GLuint diamondVBO, triangleVBO;

void buildScene() {
    GLfloat diamondVertices[] = {
         -0.5f,  0.6f, 0.0f,  // Top
         -0.2f,  0.0f, 0.0f,  // Right
         -0.5f, -0.6f, 0.0f,  // Bottom
         -0.8f,  0.0f, 0.0f   // Left
    };

    GLfloat triangleVertices[] = {
         0.5f,  0.6f, 0.0f,  // Top
         0.2f, -0.6f, 0.0f,  // Bottom left
         0.8f, -0.6f, 0.0f   // Bottom right
    };

    glGenBuffers(1, &diamondVBO);
    glBindBuffer(GL_ARRAY_BUFFER, diamondVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(diamondVertices),
                 diamondVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices),
                 triangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void diamond() {
    glBindBuffer(GL_ARRAY_BUFFER, diamondVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.7f, 0.5f, 1.0f);  // Lavender
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void triangle() {
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.4f, 1.0f, 0.7f);  // Mint green
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    diamond();
    triangle();
    glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        // Release both VBOs before closing
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &diamondVBO);
        glDeleteBuffers(1, &triangleVBO);
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q13 - ESC Cleanup Releasing Two VBOs");

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        buildScene();
        glutMainLoop();
    }
#else
    buildScene();
    glutMainLoop();
#endif

    return 0;
}
