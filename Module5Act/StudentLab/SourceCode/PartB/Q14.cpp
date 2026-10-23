
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
 * Exercise Q14 - Indexed GL_TRIANGLE_FAN Pentagon
  ------------------------------------------------
 Objective: Practice drawing a pentagon using GL_TRIANGLE_FAN
 and glDrawElements with a shared center vertex.
 This program uses a position VBO and an index buffer to draw
 a sky-blue pentagon while storing the center vertex only once.
 */

GLuint VBOid, VBOindex;

void pentagon() {
    GLfloat pentagonVertices[] = {
         0.0f,   0.0f,  0.0f,  // 0 - Center
         0.0f,   0.75f, 0.0f,  // 1 - Top
        -0.71f,  0.23f, 0.0f,  // 2 - Upper left
        -0.44f, -0.61f, 0.0f,  // 3 - Bottom left
         0.44f, -0.61f, 0.0f,  // 4 - Bottom right
         0.71f,  0.23f, 0.0f   // 5 - Upper right
    };

    // Center first, then the outer points
    GLubyte indices[] = { 0, 1, 2, 3, 4, 5, 1 };

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pentagonVertices),
                 pentagonVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBOindex);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindex);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                 indices, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
    glDeleteBuffers(1, &VBOindex);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.35f, 0.75f, 1.0f);  // Sky blue
    pentagon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q14 - Indexed Triangle Fan Pentagon");

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
