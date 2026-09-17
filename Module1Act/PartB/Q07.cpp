#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q07 - Two Triangles
  ------------------------------------
 Objective: Practice using multiple glBegin and glEnd blocks with different colors in one display.
 This program draws a red filled triangle on the left and a blue filled triangle on the right.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); // red

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.8f, -0.4f); // bottom-left
        glVertex2f(-0.5f,  0.5f); // top
        glVertex2f(-0.2f, -0.4f); // bottom-right
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f); // blue

    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, -0.4f); // bottom-left
        glVertex2f(0.5f,  0.5f); // top
        glVertex2f(0.8f, -0.4f); // bottom-right
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q07 - Two Triangles");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}