#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q12 - Arrow
  ------------------------------------
 Objective: Practice combining two different primitive types into one composite shape.
 This program draws a golden arrow pointing to the right using a line and a filled triangle.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.7f, 0.1f); // golden
    glLineWidth(8.0f);

    glBegin(GL_LINES);
        glVertex2f(-0.75f, 0.0f); // start of shaft
        glVertex2f( 0.35f, 0.0f); // end of shaft
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(0.35f,  0.25f); // top of arrowhead base
        glVertex2f(0.80f,  0.00f); // arrow tip
        glVertex2f(0.35f, -0.25f); // bottom of arrowhead base
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q12 - Arrow");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}