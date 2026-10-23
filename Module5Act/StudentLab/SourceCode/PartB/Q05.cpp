
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
 * Exercise Q05 - Two Separate VBOs Side by Side
  ----------------------------------------------
 Objective: Practice using two independent VBOs in one program.
 This program draws two triangles side by side, each using
 its own Vertex Buffer Object.
 */

GLuint leftVBO, rightVBO;

void triangleLeft() {
    GLfloat verts[] = {
        -0.7f,  0.5f, 0.0f,
        -0.9f, -0.3f, 0.0f,
        -0.5f, -0.3f, 0.0f
    };

    glGenBuffers(1, &leftVBO);
    glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, verts, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Left triangle - Lavender
    glColor3f(0.75f, 0.45f, 1.0f);

    // Bind the left VBO before drawing the first triangle
    glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void triangleRight() {
    GLfloat verts[] = {
         0.7f,  0.5f, 0.0f,
         0.5f, -0.3f, 0.0f,
         0.9f, -0.3f, 0.0f
    };

    glGenBuffers(1, &rightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, verts, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Right triangle - Turquoise
    glColor3f(0.1f, 0.9f, 0.7f);

    // Bind the right VBO before drawing the second triangle
    glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    triangleLeft();
    triangleRight();

    glDeleteBuffers(1, &leftVBO);
    glDeleteBuffers(1, &rightVBO);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q05 - Two Separate VBOs Side by Side");

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
