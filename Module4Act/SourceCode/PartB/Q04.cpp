#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q04 - Square Plus Outline
 -----------------------------------
 Objective: Practice using one vertex array for two draw calls.
 */

void square()
{
    GLfloat squareVertices[] = {
        -0.55f, -0.55f, 0.0f, // lower-left
         0.55f, -0.55f, 0.0f, // lower-right
         0.55f,  0.55f, 0.0f, // upper-right
        -0.55f,  0.55f, 0.0f  // upper-left
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, squareVertices);

    glColor3f(0.95f, 0.65f, 0.10f); // orange
    glDrawArrays(GL_QUADS, 0, 4);

    glColor3f(0.10f, 0.85f, 0.95f); // cyan
    glLineWidth(5.0f);
    glDrawArrays(GL_LINE_LOOP, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    square();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q04 - Square Plus Outline");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}