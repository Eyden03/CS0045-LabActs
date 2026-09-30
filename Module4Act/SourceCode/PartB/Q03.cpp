#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q03 - Two Lines, One Array
 ------------------------------------
 Objective: Practice drawing multiple GL_LINES from one vertex array.
 */

void lines()
{
    GLfloat lineVertices[] = {
        -0.80f,  0.45f, 0.0f, // first line start
         0.80f,  0.45f, 0.0f, // first line end
        -0.80f, -0.45f, 0.0f, // second line start
         0.80f, -0.45f, 0.0f  // second line end
    };

    glLineWidth(5.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, lineVertices);
    glDrawArrays(GL_LINES, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.05f, 0.80f, 0.70f); // teal
    lines();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q03 - Two Lines");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}