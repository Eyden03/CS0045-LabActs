#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q08 - Smooth Shaded Diamond
  ------------------------------------
 Objective: Practice per-vertex color and smooth shading on a four-sided polygon.
 This program draws a diamond with four different vertex colors that blend across its interior.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_SMOOTH); // enable smooth color blending

    glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.3f, 0.2f); 
        glVertex2f(0.0f, 0.7f); // top

        glColor3f(0.0f, 0.9f, 0.8f); 
        glVertex2f(0.7f, 0.0f); // right

        glColor3f(1.0f, 0.7f, 0.0f); // gold
        glVertex2f(0.0f, -0.7f); // bottom

        glColor3f(0.7f, 0.2f, 1.0f); // violet
        glVertex2f(-0.7f, 0.0f); // left
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q08 - Smooth Shaded Diamond");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}