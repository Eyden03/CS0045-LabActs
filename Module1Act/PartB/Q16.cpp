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
Exercise Q16 - Bouncing Ball
  ------------------------------------
 Objective: Practice glutIdleFunc animation with collision against all four window edges.
 This program animates a lavender ball that moves diagonally and bounces off every edge.
 */

float ballX = 0.0f;
float ballY = 0.0f;
float dx = 0.0025f;
float dy = 0.0020f;
const float radius = 0.12f;

void drawBall()
{
    const int segments = 60;
    const float PI = 3.14159265f;

    glColor3f(0.75f, 0.55f, 1.0f); // lavender

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ballX, ballY); // center

    for (int i = 0; i <= segments; i++)
    {
        float angle = (float)i / segments * 2.0f * PI;
        float x = ballX + radius * cosf(angle);
        float y = ballY + radius * sinf(angle);

        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClearColor(0.03f, 0.04f, 0.12f, 1.0f); // dark navy background
    glClear(GL_COLOR_BUFFER_BIT);

    drawBall();

    glFlush();
}

void idle()
{
    ballX += dx;
    ballY += dy;

    if (ballX + radius >= 1.0f || ballX - radius <= -1.0f)
        {
            dx = -dx; // reverse horizontal direction
        }

    if (ballY + radius >= 1.0f || ballY - radius <= -1.0f)
        {
            dy = -dy; // reverse vertical direction
        }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q16 - Bouncing Ball");

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}