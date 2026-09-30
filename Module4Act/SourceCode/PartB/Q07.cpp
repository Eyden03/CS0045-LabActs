#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q07 - Vertex and Color Array Triangle
 -----------------------------------------------
 Objective: Practice combining vertex and color arrays.
 */

void triangle()
{
    GLfloat triangleVertices[] = {
         0.0f,  0.70f, 0.0f, // top
        -0.70f, -0.45f, 0.0f, // lower-left
         0.70f, -0.45f, 0.0f  // lower-right
    };

    GLfloat triangleColors[] = {
        1.0f, 0.35f, 0.10f, // orange
        0.10f, 0.85f, 0.45f, // green
        0.25f, 0.40f, 1.0f  // blue
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
    glColorPointer(3, GL_FLOAT, 0, triangleColors);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    triangle();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q07 - Vertex and Color Array Triangle");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}