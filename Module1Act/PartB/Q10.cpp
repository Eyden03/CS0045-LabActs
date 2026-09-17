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
Exercise Q10 - Five-Pointed Star Outline
  ------------------------------------
 Objective: Practice trigonometry using sine and cosine to generate a non-trivial shape.
 This program draws a five-pointed magenta star outline by alternating outer and inner radii.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    const int vertices = 10;
    const float outerRadius = 0.75f;
    const float innerRadius = 0.32f;
    const float PI = 3.14159265f;

    glColor3f(0.95f, 0.2f, 0.65f); // magenta
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
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

            float x = radius * cosf(angle);
            float y = radius * sinf(angle);

            glVertex2f(x, y);
        }
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q10 - Five-Pointed Star Outline");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}