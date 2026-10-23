
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
 * Exercise Q09 - Two-VBO Colored Triangle
  ----------------------------------------
 Objective: Practice using separate position and color VBOs.
 This program draws a triangle with three different vertex colors
 using two independent Vertex Buffer Objects.
 */

GLuint posVBO, colorVBO;

void coloredTriangle() {
    GLfloat positions[] = {
         0.0f,  0.75f, 0.0f,
        -0.75f, -0.5f, 0.0f,
         0.75f, -0.5f, 0.0f
    };

    GLfloat colors[] = {
        1.0f, 0.3f, 0.6f,
        0.1f, 0.9f, 0.8f,
        1.0f, 0.8f, 0.2f
    };

    // Store the vertex positions
    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9,
        positions, GL_STATIC_DRAW);

    // Store the colors separately
    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9,
        colors, GL_STATIC_DRAW);

    // Use both position and color arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

        // Set the position data
        glBindBuffer(GL_ARRAY_BUFFER, posVBO);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        // Set the color data
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        glColorPointer(3, GL_FLOAT, 0, 0);

        // Draw the colored triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

    // Clean up both buffers
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &posVBO);
    glDeleteBuffers(1, &colorVBO);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    coloredTriangle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q09 - Two-VBO Colored Triangle");

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
