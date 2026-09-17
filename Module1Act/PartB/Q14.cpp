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
Exercise Q14 - Simple Landscape
  ------------------------------------
 Objective: Practice combining window settings, background color, GL_POLYGON, and GL_TRIANGLE_FAN.
 This program creates a wide landscape with a light-blue sky, green ground, and a golden sun.
 */

void drawSun()
{
    const int segments = 60;
    const float centerX = -0.65f;
    const float centerY = 0.55f;
    const float radiusX = 0.10f;
    const float radiusY = 0.20f;
    const float PI = 3.14159265f;

    glColor3f(1.0f, 0.65f, 0.1f); // golden sun

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY); // center

        for (int i = 0; i <= segments; i++)
        {
            float angle = (float)i / segments * 2.0f * PI;
            float x = centerX + radiusX * cosf(angle);
            float y = centerY + radiusY * sinf(angle);

            glVertex2f(x, y);
        }
    glEnd();
}

void display()
{
    glClearColor(0.55f, 0.82f, 0.95f, 1.0f); // light-blue sky
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.2f, 0.65f, 0.3f); // green ground

    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f); // bottom-left
        glVertex2f(-1.0f, -0.35f); // top-left
        glVertex2f( 1.0f, -0.35f); // top-right
        glVertex2f( 1.0f, -1.0f); // bottom-right
    glEnd();

    drawSun();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q14 - Simple Landscape");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}