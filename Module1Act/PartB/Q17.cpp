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
Exercise Q17 - Traffic Light Simulator
  ------------------------------------
 Objective: Practice using keyboard input to control a small state machine.
 This program cycles through red, yellow, and green traffic lights when the N key is pressed.
 */

int activeLight = 0;

void drawCircle(float centerX, float centerY, float r, float g, float b)
{
    const int segments = 60;
    const float radius = 0.18f;
    const float PI = 3.14159265f;

    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY); // center

        for (int i = 0; i <= segments; i++)
        {
            float angle = (float)i / segments * 2.0f * PI;
            float x = centerX + radius * cosf(angle);
            float y = centerY + radius * sinf(angle);

            glVertex2f(x, y);
        }
    glEnd();
}

void display()
{
    glClearColor(0.12f, 0.12f, 0.16f, 1.0f); // dark background
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.25f, 0.27f, 0.32f); // traffic light housing

    glBegin(GL_POLYGON);
        glVertex2f(-0.35f, -0.85f);
        glVertex2f(-0.35f,  0.85f);
        glVertex2f( 0.35f,  0.85f);
        glVertex2f( 0.35f, -0.85f);
    glEnd();

    if (activeLight == 0)
        {
            drawCircle(0.0f, 0.55f, 1.0f, 0.0f, 0.0f); // bright red
        }
    else
        {
            drawCircle(0.0f, 0.55f, 0.25f, 0.0f, 0.0f); // dim red
        }

    if (activeLight == 1)
        {
            drawCircle(0.0f, 0.0f, 1.0f, 0.85f, 0.0f); // bright yellow
        }
    else
        {
            drawCircle(0.0f, 0.0f, 0.25f, 0.20f, 0.0f); // dim yellow
        }

    if (activeLight == 2)
        {
            drawCircle(0.0f, -0.55f, 0.0f, 1.0f, 0.2f); // bright green
        }
    else
        {
            drawCircle(0.0f, -0.55f, 0.0f, 0.25f, 0.05f); // dim green
        }

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'n' || key == 'N')
    {
        activeLight = (activeLight + 1) % 3;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q17 - Traffic Light Simulator");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}