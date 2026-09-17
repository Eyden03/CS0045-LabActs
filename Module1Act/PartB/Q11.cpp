#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

/*
Exercise Q11 - Concentric Circles
  ------------------------------------
 Objective: Practice reusing a helper function to draw the same shape at different sizes.
 This program draws three circle outlines with different radii and colors that share one center.
 */

void drawCircleOutline(float radius, float r, float g, float b)
{
    const int segments = 60;
    const float PI = 3.14159265f;

    glColor3f(r, g, b);

    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++)
        {
            float angle = (float)i / segments * 2.0f * PI;
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);

            glVertex2f(x, y);
        }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3.0f);

    drawCircleOutline(0.75f, 1.0f, 0.3f, 0.2f); // coral outer circle
    drawCircleOutline(0.50f, 0.0f, 0.9f, 0.8f); // turquoise middle circle
    drawCircleOutline(0.25f, 0.7f, 0.3f, 1.0f); // violet inner circle

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q11 - Concentric Circles");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}