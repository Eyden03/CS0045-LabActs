#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q12 - Interleaved Array Quad
 --------------------------------------
 Objective: Practice using position and color data in one array.
 */

void quad()
{
    GLfloat vertices[] = {
        -0.60f, -0.50f, 0.0f, 1.0f, 0.30f, 0.20f, // lower-left
         0.60f, -0.50f, 0.0f, 0.20f, 0.90f, 0.40f, // lower-right
         0.60f,  0.50f, 0.0f, 0.20f, 0.50f, 1.0f, // upper-right
        -0.60f,  0.50f, 0.0f, 0.80f, 0.20f, 1.0f  // upper-left
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices);
    glColorPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), vertices + 3);

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    quad();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q12 - Interleaved Array Quad");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}