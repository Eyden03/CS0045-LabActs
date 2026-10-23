
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
 * Exercise Q01 - VBO X-Pattern Points
  ------------------------------------
 Objective: Practice converting GL_POINTS to a VBO using the 5-step pattern.
 This program draws five cyan points forming an X pattern,
 including a center point, using a Vertex Buffer Object.
 */

GLuint VBOid;

void points() {
    glPointSize(15.0f);

    // 1. Initialize the five points using an array
    GLfloat pointVertices[] = {
        -0.75f,  0.75f, 0.0f,
         0.75f,  0.75f, 0.0f,
         0.0f,   0.0f,  0.0f,
        -0.75f, -0.75f, 0.0f,
         0.75f, -0.75f, 0.0f
    };

    // 2. Generate, bind, and upload the VBO
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 15, pointVertices, GL_STATIC_DRAW);

    // 3. Enable the vertex array
    glEnableClientState(GL_VERTEX_ARRAY);

    // 4. Specify the pointer and draw the points
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_POINTS, 0, 5);

    // 5. Disable, unbind, and delete the VBO
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 1.0f);
    points();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q01 - VBO X-Pattern Points");

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
