#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

const int teeth = 12;

GLfloat gearVertices[(teeth + 2) * 3];
GLubyte evenIndices[(teeth / 2) * 3];
GLubyte oddIndices[(teeth / 2) * 3];

/*
 Exercise Q17 - Procedural Gear Shape
 -------------------------------------
 Objective: Practice generating indexed shapes using a loop.
 */

void createGear()
{
    const float PI = 3.14159f;

    gearVertices[0] = 0.0f;
    gearVertices[1] = 0.0f;
    gearVertices[2] = 0.0f;

    for (int i = 0; i <= teeth; i++)
    {
        float angle = (2.0f * PI * i) / teeth;
        float radius = (i % 2 == 0) ? 0.75f : 0.52f;
        int index = (i + 1) * 3;

        gearVertices[index] = radius * cos(angle);
        gearVertices[index + 1] = radius * sin(angle);
        gearVertices[index + 2] = 0.0f;
    }

    int evenPosition = 0;
    int oddPosition = 0;

    for (int i = 0; i < teeth; i++)
    {
        int next = i + 1;

        if (i % 2 == 0)
        {
            evenIndices[evenPosition++] = 0;
            evenIndices[evenPosition++] = i + 1;
            evenIndices[evenPosition++] = next + 1;
        }
        else
        {
            oddIndices[oddPosition++] = 0;
            oddIndices[oddPosition++] = i + 1;
            oddIndices[oddPosition++] = next + 1;
        }
    }
}

void gear()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, gearVertices);

    glColor3f(0.95f, 0.35f, 0.10f); // orange
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, evenIndices);

    glColor3f(0.20f, 0.55f, 1.0f); // blue
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_BYTE, oddIndices);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    gear();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q17 - Procedural Gear Shape");
    glutDisplayFunc(display);

    createGear();

    glutMainLoop();

    return 0;
}