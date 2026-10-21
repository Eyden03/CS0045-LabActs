
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
 * Exercise Q02 - VBO Line Loop Square
  ------------------------------------
 Objective: Practice drawing GL_LINE_LOOP using a Vertex Buffer Object.
 This program draws a yellow square outline using four unique
 vertices stored in a VBO.
 */

GLuint VBOid;

void square() {
    GLfloat squareVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    // Upload vertices to the VBO
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, squareVertices, GL_STATIC_DRAW);

    // Set up vertex positions
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Draw the square outline
    glLineWidth(4.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    // Clean up VBO state
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.45f, 0.7f);
    square();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q02 - VBO Line Loop Square");

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
