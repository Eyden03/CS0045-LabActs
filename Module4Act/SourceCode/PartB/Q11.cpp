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
 Exercise Q11 - Procedural Shaded Circle
 ----------------------------------------
 Objective: Practice generating vertex and color arrays using a loop.
 */

void circle()
{
    const int segments = 40;
    const float PI = 3.14159f;

    GLfloat vertices[(segments + 2) * 3];
    GLfloat colors[(segments + 2) * 3];

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;

    colors[0] = 1.0f;
    colors[1] = 1.0f;
    colors[2] = 1.0f;

    for (int i = 0; i <= segments; i++)
    {
        float angle = (2.0f * PI * i) / segments;
        int index = (i + 1) * 3;

        vertices[index] = 0.65f * cos(angle);
        vertices[index + 1] = 0.65f * sin(angle);
        vertices[index + 2] = 0.0f;

        colors[index] = (cos(angle) + 1.0f) / 2.0f;
        colors[index + 1] = (sin(angle) + 1.0f) / 2.0f;
        colors[index + 2] = 0.85f;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    circle();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q11 - Procedural Shaded Circle");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}