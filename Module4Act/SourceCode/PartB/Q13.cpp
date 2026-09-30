#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q13 - Pinwheel via glDrawElements
 -------------------------------------------
 Objective: Practice indexed rendering with a shared center vertex.
 */

void pinwheel()
{
    GLfloat vertices[] = {
         0.0f,  0.0f, 0.0f, // center
        -0.55f,  0.10f, 0.0f, // left-top
        -0.55f, -0.10f, 0.0f, // left-bottom
         0.55f,  0.10f, 0.0f, // right-top
         0.55f, -0.10f, 0.0f, // right-bottom
        -0.10f,  0.55f, 0.0f, // upper-left
         0.10f,  0.55f, 0.0f, // upper-right
        -0.10f, -0.55f, 0.0f, // lower-left
         0.10f, -0.55f, 0.0f  // lower-right
    };

    GLfloat colors[] = {
    1.0f, 1.0f, 1.0f, // center
    1.0f, 0.25f, 0.20f, // left-top
    0.20f, 0.85f, 0.95f, // left-bottom
    0.55f, 0.25f, 1.0f, // right-top
    1.0f, 0.75f, 0.15f, // right-bottom
    0.20f, 0.90f, 0.40f, // upper-left
    0.10f, 0.45f, 0.20f, // upper-right
    1.0f, 0.55f, 0.25f, // lower-left
    0.85f, 0.15f, 0.10f  // lower-right
    };

    GLubyte indices[] = {
        0, 1, 2, // left
        0, 3, 4, // right
        0, 5, 6, // up
        0, 7, 8  // down
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    pinwheel();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q13 - Indexed Pinwheel");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}