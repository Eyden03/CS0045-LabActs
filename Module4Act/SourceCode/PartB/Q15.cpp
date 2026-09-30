#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q15 - Fully Array-Based Scene
 --------------------------------------
 Objective: Practice building a scene using only vertex arrays.
 */

GLfloat sunVertices[] = {
     0.55f,  0.55f, 0.0f, // center
     0.55f,  0.80f, 0.0f,
     0.73f,  0.73f, 0.0f,
     0.80f,  0.55f, 0.0f,
     0.73f,  0.37f, 0.0f,
     0.55f,  0.30f, 0.0f,
     0.37f,  0.37f, 0.0f,
     0.30f,  0.55f, 0.0f,
     0.37f,  0.73f, 0.0f,
     0.55f,  0.80f, 0.0f
};

GLubyte sunIndices[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

GLfloat mountainVertices[] = {
    -0.85f, -0.55f, 0.0f, // left
     0.00f,  0.45f, 0.0f, // peak
     0.85f, -0.55f, 0.0f  // right
};

GLfloat groundVertices[] = {
    -0.95f, -0.55f, 0.0f, // upper-left
     0.95f, -0.55f, 0.0f, // upper-right
     0.95f, -0.85f, 0.0f, // lower-right
    -0.95f, -0.85f, 0.0f  // lower-left
};

void sun()
{
    glColor3f(1.0f, 0.75f, 0.10f); // yellow

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, sunVertices);
    glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_BYTE, sunIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void mountain()
{
    glColor3f(0.35f, 0.20f, 0.55f); // purple

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, mountainVertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ground()
{
    glColor3f(0.20f, 0.70f, 0.30f); // green

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, groundVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    ground();
    mountain();
    sun();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q15 - Fully Array-Based Scene");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}