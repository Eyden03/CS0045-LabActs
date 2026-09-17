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
Exercise Q20 - Procedural Striped Flag with Star
  ------------------------------------
 Objective: Practice procedural generation using a configurable loop and a composite star.
 This program draws alternating navy and cream stripes with a filled coral star in the upper-left.
 */

const int STRIPE_COUNT = 7;
const float PI = 3.14159265f;

void drawFilledStar(float centerX, float centerY)
{
    const int vertices = 10;
    const float outerRadius = 0.18f;
    const float innerRadius = 0.08f;

    glColor3f(1.0f, 0.3f, 0.25f); // coral star

    glBegin(GL_POLYGON);
    for (int i = 0; i < vertices; i++)
    {
        float angle = (float)i / vertices * 2.0f * PI + PI / 2.0f;
        float radius;

        if (i % 2 == 0)
            {
                radius = outerRadius;
            }
        else
            {
                radius = innerRadius;
            }

        float x = centerX + radius * cosf(angle);
        float y = centerY + radius * sinf(angle);

        glVertex2f(x, y);
    }
    glEnd();
}

void display()
{
    glClearColor(0.08f, 0.08f, 0.10f, 1.0f); // charcoal background
    glClear(GL_COLOR_BUFFER_BIT);

    const float flagLeft = -0.90f;
    const float flagRight = 0.90f;
    const float flagBottom = -0.65f;
    const float flagTop = 0.65f;
    const float totalHeight = flagTop - flagBottom;
    const float stripeHeight = totalHeight / STRIPE_COUNT;

    for (int i = 0; i < STRIPE_COUNT; i++)
    {
        float y0 = flagBottom + i * stripeHeight;
        float y1 = y0 + stripeHeight;

        if (i % 2 == 0)
            {
                glColor3f(0.08f, 0.24f, 0.38f); // deep navy
            }
        else
            {
                glColor3f(0.95f, 0.84f, 0.62f); // warm cream
            }

        glBegin(GL_POLYGON);
        glVertex2f(flagLeft, y0); // bottom-left
        glVertex2f(flagLeft, y1); // top-left
        glVertex2f(flagRight, y1); // top-right
        glVertex2f(flagRight, y0); // bottom-right
        glEnd();
    }

    drawFilledStar(-0.65f, 0.40f);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Q20 - Procedural Striped Flag with Star");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}