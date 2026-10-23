
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
 * Exercise Q15 - Continuous Bouncing glMapBuffer Animation
  --------------------------------------------------------
 Objective: Practice continuous VBO animation with direction reversal.
 This program moves a lavender quad up and down using glMapBuffer
 and glutTimerFunc, reversing direction at the upper and lower limits.
 */

GLuint VBOid;
float offsetY = 0.0f;
float direction = 0.02f;

void buildQuad() {
    GLfloat quadVertices[] = {
        -0.4f, -0.2f, 0.0f,  // Bottom left
         0.4f, -0.2f, 0.0f,  // Bottom right
         0.4f,  0.2f, 0.0f,  // Top right
        -0.4f,  0.2f, 0.0f   // Top left
    };

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices),
        quadVertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void quad() {
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.75f, 0.55f, 1.0f);  // Lavender
    quad();
    glFlush();
}

void animateStep(int value) {
    // Change direction when the quad reaches the limit
    if (offsetY >= 0.5f || offsetY <= -0.5f) {
        direction = -direction;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    GLfloat* mapped = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (mapped != nullptr) {
        mapped[1] += direction;
        mapped[4] += direction;
        mapped[7] += direction;
        mapped[10] += direction;
        glUnmapBuffer(GL_ARRAY_BUFFER);

        offsetY += direction;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(100, animateStep, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q15 - Bouncing VBO Quad");

    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        buildQuad();
        glutTimerFunc(100, animateStep, 0);
        glutMainLoop();
    }
#else
    buildQuad();
    glutTimerFunc(100, animateStep, 0);
    glutMainLoop();
#endif

    return 0;
}
