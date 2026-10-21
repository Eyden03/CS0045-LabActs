
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
 * Exercise Q11 - One-Shot glMapBuffer Vertical Shift
  --------------------------------------------------
 Objective: Practice editing a vertex using glMapBuffer.
 This program draws a peach-colored triangle and moves
 its top vertex upward by modifying the VBO data once.
 */

GLuint VBOid;

void triangle() {
    GLfloat triangleVertices[] = {
         0.0f,  0.5f, 0.0f,  // Top
        -0.7f, -0.5f, 0.0f,  // Bottom left
         0.7f, -0.5f, 0.0f   // Bottom right
    };

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9,
                 triangleVertices, GL_DYNAMIC_DRAW);

    // Move only the top vertex upward
    GLfloat* mapped = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    if (mapped != nullptr) {
        mapped[1] += 0.3f;
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.65f, 0.5f);  // Peach
    triangle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q11 - One-Shot Vertical Shift");

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
