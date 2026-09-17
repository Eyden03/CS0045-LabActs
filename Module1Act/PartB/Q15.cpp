#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q15 - Move a Square with Arrow Keys
  ------------------------------------
 Objective: Practice glutSpecialFunc and updating state in response to input.
 This program draws a lime-green square that moves with the arrow keys and stays inside the window.
 */

float squareX = 0.0f;
float squareY = 0.0f;
const float halfSize = 0.15f;
const float moveStep = 0.05f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.5f, 1.0f, 0.2f); // lime green

    glBegin(GL_POLYGON);
        glVertex2f(squareX - halfSize, squareY - halfSize); // bottom-left
        glVertex2f(squareX - halfSize, squareY + halfSize); // top-left
        glVertex2f(squareX + halfSize, squareY + halfSize); // top-right
        glVertex2f(squareX + halfSize, squareY - halfSize); // bottom-right
    glEnd();

    glFlush();
}

void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
        {
            squareX -= moveStep;
        }
    else if (key == GLUT_KEY_RIGHT)
        {
            squareX += moveStep;
        }
    else if (key == GLUT_KEY_UP)
        {
            squareY += moveStep;
        }
    else if (key == GLUT_KEY_DOWN)
        {
            squareY -= moveStep;
        }

    if (squareX > 1.0f - halfSize)
        {
            squareX = 1.0f - halfSize;
        }
    if (squareX < -1.0f + halfSize)
        {
            squareX = -1.0f + halfSize;
        }
    if (squareY > 1.0f - halfSize)
        {
            squareY = 1.0f - halfSize;
        }
    if (squareY < -1.0f + halfSize)
        {
            squareY = -1.0f + halfSize;
        }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q15 - Move a Square with Arrow Keys");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutMainLoop();

    return 0;
}