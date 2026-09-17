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
Exercise Q18 - Rotating Clock Hand
  ------------------------------------
 Objective: Practice combining a static clock face with an animated hand using glutIdleFunc.
 This program draws a clock with twelve tick marks and one slowly rotating coral hand.
 */

const float PI = 3.14159265f;
const float clockRadius = 0.75f;
float handAngle = PI / 2.0f;

void drawClockFace()
{
    const int segments = 60;

    glColor3f(0.9f, 0.85f, 1.0f); // light clock face
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++)
        {
            float angle = (float)i / segments * 2.0f * PI;
            float x = clockRadius * cosf(angle);
            float y = clockRadius * sinf(angle);

            glVertex2f(x, y);
        }
    glEnd();

    glLineWidth(4.0f);

    glBegin(GL_LINES);
        for (int i = 0; i < 12; i++)
        {
            float angle = (float)i / 12 * 2.0f * PI;
            float innerX = 0.63f * cosf(angle);
            float innerY = 0.63f * sinf(angle);
            float outerX = clockRadius * cosf(angle);
            float outerY = clockRadius * sinf(angle);

            glVertex2f(innerX, innerY);
            glVertex2f(outerX, outerY);
        }
    glEnd();
}

void drawHand()
{
    const float handLength = 0.55f;

    glColor3f(1.0f, 0.35f, 0.25f); // coral hand
    glLineWidth(5.0f);

    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f); // center
        glVertex2f(handLength * cosf(handAngle),
                   handLength * sinf(handAngle)); // endpoint
    glEnd();
}

void display()
{
    glClearColor(0.10f, 0.05f, 0.18f, 1.0f); // dark-purple background
    glClear(GL_COLOR_BUFFER_BIT);

    drawClockFace();
    drawHand();

    glFlush();
}

void idle()
{
    handAngle -= 0.001f;

    if (handAngle < 0.0f)
        {
            handAngle += 2.0f * PI;
        }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q18 - Rotating Clock Hand");

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}