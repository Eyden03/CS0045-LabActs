
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
 * Exercise Q06 - Flat-Colored VBO Quad
  ------------------------------------
 Objective: Practice converting a filled square into a VBO using GL_QUADS.
 This program draws a mint green square using one Vertex Buffer Object
 and a single flat color applied through glColor3f.
 */

GLuint VBOid;

void square() {
    GLfloat quadVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Upload vertices to the VBO
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12,
                 quadVertices, GL_STATIC_DRAW);

    // Set up vertex input
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Draw the quad
    glDrawArrays(GL_QUADS, 0, 4);

    // Clean up
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Apply one flat color to the entire square
    glColor3f(0.3f, 1.0f, 0.7f);

    square();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q06 - Flat-Colored VBO Quad");

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
