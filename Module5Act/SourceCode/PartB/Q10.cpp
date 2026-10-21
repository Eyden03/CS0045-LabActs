
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
 * Exercise Q10 - Interleaved VBO Quad
  ------------------------------------
 Objective: Practice storing position and color data in one VBO.
 This program draws a quad with four different vertex colors
 using an interleaved buffer with stride and byte offsets.
 */

GLuint VBOid;

void interleavedQuad() {
    GLfloat data[] = {
        // x,     y,     z,      r,     g,     b
        -0.5f, -0.5f, 0.0f,   0.5f, 1.0f, 0.7f,  // Bottom left - Mint
         0.5f, -0.5f, 0.0f,   1.0f, 0.7f, 0.3f,  // Bottom right - Orange
         0.5f,  0.5f, 0.0f,   1.0f, 0.4f, 0.6f,  // Top right - Pink
        -0.5f,  0.5f, 0.0f,   0.7f, 0.5f, 1.0f   // Top left - Lavender
    };

    GLsizei stride = 6 * sizeof(GLfloat);

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, stride, (void*)0);
    glColorPointer(3, GL_FLOAT, stride, (void*)(3 * sizeof(GLfloat)));

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    interleavedQuad();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q10 - Interleaved VBO Quad");

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
