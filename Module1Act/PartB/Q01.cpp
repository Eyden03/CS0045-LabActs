#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 * Exercise Q01 - Red Center Point
 * ------------------------------------
 * Objective: Practice specifying a single vertex and controlling
 * point size.
 *
 * This program draws one large red point exactly at the center
 * of the window using GL_POINTS.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f);  // red point
    glPointSize(15.0f); // required point size

    glBegin(GL_POINTS);
        glVertex2f(0.0f, 0.0f); // center of the window
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q01 - Red Center Point");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}