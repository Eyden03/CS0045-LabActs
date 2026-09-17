#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q09 - 4x4 Checkerboard
  ------------------------------------
 Objective: Practice nested loops to generate a grid of filled polygons.
 This program draws a 4x4 checkerboard with alternating violet and mint green cells.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    const int rows = 4;
    const int columns = 4;
    const float cellSize = 0.4f;
    const float startX = -0.8f;
    const float startY = -0.8f;

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            float x = startX + col * cellSize;
            float y = startY + row * cellSize;

            if ((row + col) % 2 == 0)
                {
                    glColor3f(0.7f, 0.3f, 1.0f); // violet
                }
            else
                {
                    glColor3f(0.2f, 0.9f, 0.6f); // mint green
                }

            glBegin(GL_POLYGON);
                glVertex2f(x, y); // bottom-left
                glVertex2f(x, y + cellSize); // top-left
                glVertex2f(x + cellSize, y + cellSize); // top-right
                glVertex2f(x + cellSize, y); // bottom-right
            glEnd();
        }
    }

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q09 - 4x4 Checkerboard");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}