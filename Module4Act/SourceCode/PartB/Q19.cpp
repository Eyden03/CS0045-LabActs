#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q19 - Interleaved and Indexed Hexagon
 -----------------------------------------------
 Objective: Practice combining interleaved arrays with indexed rendering.
 */

void hexagon()
{
    GLfloat vertices[] = {
         0.0f,  0.75f, 0.0f, 1.0f, 0.25f, 0.20f, // top
         0.65f,  0.38f, 0.0f, 1.0f, 0.70f, 0.15f, // upper-right
         0.65f, -0.38f, 0.0f, 0.30f, 0.85f, 0.35f, // lower-right
         0.0f, -0.75f, 0.0f, 0.15f, 0.65f, 1.0f, // bottom
        -0.65f, -0.38f, 0.0f, 0.35f, 0.25f, 0.95f, // lower-left
        -0.65f,  0.38f, 0.0f, 0.90f, 0.20f, 0.65f  // upper-left
    };

    GLubyte indices[] = {
        0, 1, 2, 3, 4, 5
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices);
    glColorPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices + 3);

    glDrawElements(GL_POLYGON, 6, GL_UNSIGNED_BYTE, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    hexagon();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q19 - Interleaved Indexed Hexagon");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}