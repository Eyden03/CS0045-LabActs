
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
 * Exercise Q12 - Timer + glMapBuffer Moving Point
  ------------------------------------------------
 Objective: Practice moving a point using glMapBuffer and glutTimerFunc.
 This program draws a magenta point that moves to the right
 every second by updating its position in the VBO.
 */

GLuint VBOid;
bool pointReady = false;

void point() {
    if (!pointReady) {
        GLfloat pointVertices[] = {
            -0.8f, 0.0f, 0.0f  // Starting point
        };

        glGenBuffers(1, &VBOid);
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices),
                     pointVertices, GL_DYNAMIC_DRAW);
        pointReady = true;
    } else {
        glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glPointSize(20.0f);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.2f, 0.8f);  // Magenta
    point();
    glFlush();
}

void animateStep(int value) {
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    GLfloat* mapped = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (mapped != nullptr) {
        mapped[0] += 0.1f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glutPostRedisplay();
    glutTimerFunc(1000, animateStep, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q12 - Moving VBO Point");

    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        point();  // Create the VBO before starting the timer
        glutTimerFunc(1000, animateStep, 0);
        glutMainLoop();
    }
#else
    point();
    glutTimerFunc(1000, animateStep, 0);
    glutMainLoop();
#endif

    return 0;
}
