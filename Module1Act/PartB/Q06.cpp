#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q06 - Hexagon Outline
  ------------------------------------
 Objective: Practice manually typing coordinates for a polygon with more than four sides.
 This program draws a violet six-sided hexagon outline using six manually specified vertices.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.7f, 0.3f, 1.0f); // violet
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f,  0.65f); // top-left
        glVertex2f( 0.3f,  0.65f); // top-right
        glVertex2f( 0.65f, 0.0f); // right
        glVertex2f( 0.3f, -0.65f); // bottom-right
        glVertex2f(-0.3f, -0.65f); // bottom-left
        glVertex2f(-0.65f, 0.0f); // left
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q06 - Hexagon Outline");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}