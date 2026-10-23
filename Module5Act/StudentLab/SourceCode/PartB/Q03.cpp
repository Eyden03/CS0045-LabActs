
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
 * Exercise Q03 - Static Hexagon With the Correct Usage Hint
  ----------------------------------------------------------
 Objective: Practice choosing the correct glBufferData usage hint.
 This program draws a filled purple hexagon using GL_POLYGON
 and a Vertex Buffer Object with GL_STATIC_DRAW.
 */

GLuint VBOid;

void initializeHexagon() {
    GLfloat hexagonVertices[] = {
         0.0f,  0.7f, 0.0f,
        -0.6f,  0.35f, 0.0f,
        -0.6f, -0.35f, 0.0f,
         0.0f, -0.7f, 0.0f,
         0.6f, -0.35f, 0.0f,
         0.6f,  0.35f, 0.0f
    };

    // Generate and bind the Vertex Buffer Object
    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    /* I used GL_STATIC_DRAW because the hexagon's vertices will not change.
     The data only needs to be uploaded once and can be used many times.*/
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18,
                 hexagonVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void hexagon() {
    // Bind the existing VBO without uploading the data again
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    // Enable and specify the vertex array
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Draw the filled hexagon using six vertices
    glDrawArrays(GL_POLYGON, 0, 6);

    // Disable and unbind the VBO
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.6f, 0.2f, 0.9f);
    hexagon();
    glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        // Release the VBO before exiting the program
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBOid);
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q03 - Static Hexagon");

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        initializeHexagon();
        glutMainLoop();
    }
#else
    initializeHexagon();
    glutMainLoop();
#endif

    return 0;
}
