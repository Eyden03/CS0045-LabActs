#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q13 - Letter F from Rectangles
  ------------------------------------
 Objective: Practice building compound shapes from several filled rectangles.
 This program draws the capital letter F using exactly three rose-colored rectangles.
 */

void drawRect(float x0, float y0, float x1, float y1)
{
    glBegin(GL_POLYGON);
        glVertex2f(x0, y0); // bottom-left
        glVertex2f(x0, y1); // top-left
        glVertex2f(x1, y1); // top-right
        glVertex2f(x1, y0); // bottom-right
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.25f, 0.45f); // rose

    drawRect(-0.45f, -0.70f, -0.20f, 0.70f); // vertical stem
    drawRect(-0.20f,  0.45f,  0.50f, 0.70f); // top bar
    drawRect(-0.20f,  0.05f,  0.30f, 0.28f); // middle bar

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q13 - Letter F from Rectangles");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}