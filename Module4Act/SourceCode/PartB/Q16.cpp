#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q16 - glDrawArrays vs glDrawElements
 -----------------------------------------------
 Objective: Compare duplicated vertices with indexed rendering.
 */

void drawArraysQuad()
{
    GLfloat vertices[] = {
        -0.85f, -0.35f, 0.0f, // lower-left
        -0.35f, -0.35f, 0.0f, // lower-right
        -0.35f,  0.35f, 0.0f, // upper-right

        -0.85f, -0.35f, 0.0f, // lower-left
        -0.35f,  0.35f, 0.0f, // upper-right
        -0.85f,  0.35f, 0.0f  // upper-left
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawElementsQuad()
{
    GLfloat vertices[] = {
         0.35f, -0.35f, 0.0f, // lower-left
         0.85f, -0.35f, 0.0f, // lower-right
         0.85f,  0.35f, 0.0f, // upper-right
         0.35f,  0.35f, 0.0f  // upper-left
    };

    GLubyte indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.95f, 0.35f, 0.20f); // orange
    drawArraysQuad();

    glColor3f(0.20f, 0.55f, 0.95f); // blue
    drawElementsQuad();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q16 - glDrawArrays vs glDrawElements");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}