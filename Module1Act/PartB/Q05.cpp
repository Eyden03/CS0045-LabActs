#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q05 - Square Outline on Gray Background
  ------------------------------------
 Objective: Practice glClearColor together with GL_LINE_LOOP.
 This program draws a black square outline at the center of a light gray background.
 */

void display()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f); // light gray background
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 0.0f); // black
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, -0.5f); // bottom-left
        glVertex2f(-0.5f,  0.5f); // top-left
        glVertex2f( 0.5f,  0.5f); // top-right
        glVertex2f( 0.5f, -0.5f); // bottom-right
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q05 - Square Outline on Gray Background");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}