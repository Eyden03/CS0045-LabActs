#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q05 - GLint Vertex Data Type
 --------------------------------------
 Objective: Practice using GLint data with glVertexPointer.
 */

void triangle()
{
    GLint triangleVertices[] = {
         0,  75, 0, // top
        -75,   0, 0, // lower-left
         75,   0, 0  // lower-right
    };

    glPushMatrix();
    glScalef(0.01f, 0.01f, 1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_INT, 0, triangleVertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.55f, 0.95f, 0.20f); // lime
    triangle();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q05 - GLint Vertex Data Type");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}