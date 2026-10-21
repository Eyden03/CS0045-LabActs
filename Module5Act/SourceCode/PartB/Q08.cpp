
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
 * Exercise Q08 - Indexed Quad: Position VBO + Separate Index VBO
  --------------------------------------------------------------
 Objective: Practice using a position VBO and a separate index VBO.
 This program draws a coral-colored quad using four unique vertices
 and six indices with glDrawElements.
 */

GLuint VBOid, VBOindex;

void quad() {
    GLfloat quadVertices[] = {
        -0.5f, -0.5f, 0.0f,  // Bottom-left
         0.5f, -0.5f, 0.0f,  // Bottom-right
         0.5f,  0.5f, 0.0f,  // Top-right
        -0.5f,  0.5f, 0.0f   // Top-left
    };

    // Two triangles share four vertices.
    GLubyte indices[] = { 0, 1, 2, 0, 2, 3 };

    // Upload positions.
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12,
        quadVertices, GL_STATIC_DRAW);

    // Upload indices separately.
    glGenBuffers(1, &VBOindex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6,
        indices, GL_STATIC_DRAW);

    // Set up position input.
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Draw the indexed quad.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    // Reset OpenGL state and delete buffers.
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
    glDeleteBuffers(1, &VBOindex);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.85f, 0.65f, 0.9f); // Light purple-pink
    quad();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q08 - Indexed Quad");

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
