
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
 * Exercise Q18 - Interleaved + Indexed Hexagon
  --------------------------------------------
 Objective: Practice combining interleaved data and indexed drawing.
 This program draws a hexagon with six vertex colors using one
 position-color VBO and a separate index buffer.
 */

GLuint VBOid, VBOindex;

void hexagon() {
    GLfloat data[] = {
        // x,      y,      z,       r,     g,     b
         0.0f,   0.7f,  0.0f,    1.0f,  0.5f,  0.7f,  // Top - Pink
        -0.6f,   0.35f, 0.0f,    0.7f,  0.5f,  1.0f,  // Upper left - Lavender
        -0.6f,  -0.35f, 0.0f,    0.4f,  0.8f,  1.0f,  // Lower left - Sky blue
         0.0f,  -0.7f,  0.0f,    0.4f,  1.0f,  0.7f,  // Bottom - Mint
         0.6f,  -0.35f, 0.0f,    1.0f,  0.85f, 0.4f, // Lower right - Yellow
         0.6f,   0.35f, 0.0f,    1.0f,  0.65f, 0.4f  // Upper right - Peach
    };

    GLubyte indices[] = { 0, 1, 2, 3, 4, 5 };

    GLsizei stride = 6 * sizeof(GLfloat);

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glGenBuffers(1, &VBOindex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                 indices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glVertexPointer(3, GL_FLOAT, stride, (void*)0);
    glColorPointer(3, GL_FLOAT, stride, (void*)(3 * sizeof(GLfloat)));

    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
    glDeleteBuffers(1, &VBOindex);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    hexagon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q18 - Interleaved Indexed Hexagon");

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
