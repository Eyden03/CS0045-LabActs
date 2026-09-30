#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q06 - glDrawElements Index Order
 ------------------------------------------
 Objective: Practice using an index array with glDrawElements.
 */

void triangle()
{
    GLfloat triangleVertices[] = {
         0.0f,  0.70f, 0.0f, // top
        -0.70f, -0.45f, 0.0f, // lower-left
         0.70f, -0.45f, 0.0f  // lower-right
    };

    GLubyte triangleIndices[] = {
        2, 0, 1 // index order
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triangleIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.35f, 0.25f, 0.95f); // blue-violet
    triangle();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q06 - glDrawElements Index Order");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}