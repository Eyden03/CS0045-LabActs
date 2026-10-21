
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
 * Exercise Q07 - VBO Line-Strip Zigzag
  ------------------------------------
 Objective: Practice drawing GL_LINE_STRIP using a Vertex Buffer Object.
 This program draws a cyan zigzag line using six vertices
 with alternating Y-coordinates.
 */

GLuint VBOid;

void zigzag() {
    GLfloat lineVertices[] = {
        -0.9f, -0.5f, 0.0f,
        -0.55f, 0.5f, 0.0f,
        -0.2f, -0.5f, 0.0f,
         0.2f,  0.5f, 0.0f,
         0.55f, -0.5f, 0.0f,
         0.9f,  0.5f, 0.0f
    };

    // Make VBO and upload points
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18,
                 lineVertices, GL_STATIC_DRAW);

    // Tell OpenGL how vertex data is laid out
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Draw the zigzag line
    glLineWidth(4.0f);
    glDrawArrays(GL_LINE_STRIP, 0, 6);

    // Cleanup
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 1.0f);
    zigzag();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q07 - VBO Line-Strip Zigzag");

    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        glutMainLoop();
    }
#else
    glutMainLoop();
#endif

    return 0;
}
