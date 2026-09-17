#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q03 - Triangle Outline
  ------------------------------------
 Objective: Practice GL_LINE_LOOP and distinguish outlines from filled shapes.
 This program draws only the blue outline of a triangle using GL_LINE_LOOP.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f); // blue
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f( 0.0f, 0.7f); // top vertex
        glVertex2f(-0.6f, -0.5f); // bottom-left vertex
        glVertex2f( 0.6f, -0.5f); // bottom-right vertex
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q03 - Triangle Outline");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}