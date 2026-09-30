#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q14 - Colored Quad Strip Staircase
 --------------------------------------------
 Objective: Practice using vertex and color arrays with GL_QUAD_STRIP.
 */

void staircase()
{
    GLfloat vertices[] = {
    -0.90f, -0.70f, 0.0f, // step 1 bottom
    -0.90f, -0.40f, 0.0f, // step 1 top

    -0.50f, -0.70f, 0.0f,
    -0.50f, -0.40f, 0.0f,

    -0.50f, -0.40f, 0.0f, // step 2 bottom
    -0.50f, -0.10f, 0.0f, // step 2 top

    -0.10f, -0.40f, 0.0f,
    -0.10f, -0.10f, 0.0f,

    -0.10f, -0.10f, 0.0f, // step 3 bottom
    -0.10f,  0.20f, 0.0f, // step 3 top

     0.30f, -0.10f, 0.0f,
     0.30f,  0.20f, 0.0f,

     0.30f,  0.20f, 0.0f, // step 4 bottom
     0.30f,  0.50f, 0.0f, // step 4 top

     0.70f,  0.20f, 0.0f,
     0.70f,  0.50f, 0.0f
    };

    GLfloat colors[] = {
        1.0f, 0.25f, 0.20f,
        1.0f, 0.25f, 0.20f,
        1.0f, 0.25f, 0.20f,
        1.0f, 0.25f, 0.20f,

        1.0f, 0.65f, 0.10f,
        1.0f, 0.65f, 0.10f,
        1.0f, 0.65f, 0.10f,
        1.0f, 0.65f, 0.10f,

        0.30f, 0.85f, 0.35f,
        0.30f, 0.85f, 0.35f,
        0.30f, 0.85f, 0.35f,
        0.30f, 0.85f, 0.35f,

        0.20f, 0.55f, 1.0f,
        0.20f, 0.55f, 1.0f,
        0.20f, 0.55f, 1.0f,
        0.20f, 0.55f, 1.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawArrays(GL_QUAD_STRIP, 0, 16);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    staircase();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q14 - Colored Quad Strip Staircase");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}