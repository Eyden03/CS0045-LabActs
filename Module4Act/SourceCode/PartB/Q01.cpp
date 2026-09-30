#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q01 - Vertex Array X-Pattern Points
 ---------------------------------------------
 Objective: Practice converting GL_POINTS to a vertex array.
 */

void xPattern()
{
    GLfloat pointVertices[] = {
        -0.65f,  0.65f, 0.0f, // upper-left
         0.65f, -0.65f, 0.0f, // lower-right
        -0.65f, -0.65f, 0.0f, // lower-left
         0.65f,  0.65f, 0.0f, // upper-right
         0.0f,   0.0f, 0.0f   // center
    };

    glPointSize(16.0f); // point size

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pointVertices);
    glDrawArrays(GL_POINTS, 0, 5);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.45f, 0.05f); // orange
    xPattern();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q01 - Vertex Array X-Pattern Points");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}