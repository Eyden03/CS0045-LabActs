
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
 * Exercise Q04 - Full Cleanup Checklist
  ------------------------------------
 Objective: Practice the complete VBO cleanup process.
 This program draws a pink triangle using a Vertex Buffer Object
 and releases the buffer properly when ESC is pressed.
 */

GLuint VBOid;

void triangle() {
    GLfloat triangleVertices[] = {
         0.0f,  0.75f, 0.0f,
        -0.75f, -0.5f, 0.0f,
         0.75f, -0.5f, 0.0f
    };

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9,
                 triangleVertices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.4f, 0.7f);
    triangle();
    glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {

        // I disabled the vertex array because it is no longer needed.
        glDisableClientState(GL_VERTEX_ARRAY);

        // I unbound the VBO to stop OpenGL from using it.
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // I deleted the VBO to free the memory it was using.
        glDeleteBuffers(1, &VBOid);

        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q04 - Full Cleanup Checklist");

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

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
