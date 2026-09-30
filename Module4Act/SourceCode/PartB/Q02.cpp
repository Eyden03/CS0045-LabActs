#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q02 - Filled Hexagon via Vertex Array
 -----------------------------------------------
 Objective: Practice drawing a polygon using a vertex array.
 */

void hexagon()
{
    GLfloat hexagonVertices[] = {
         0.0f,  0.75f, 0.0f, // top
         0.65f,  0.38f, 0.0f, // upper-right
         0.65f, -0.38f, 0.0f, // lower-right
         0.0f, -0.75f, 0.0f, // bottom
        -0.65f, -0.38f, 0.0f, // lower-left
        -0.65f,  0.38f, 0.0f  // upper-left
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, hexagonVertices);
    glDrawArrays(GL_POLYGON, 0, 6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.65f, 0.20f, 0.95f); // purple
    hexagon();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q02 - Filled Hexagon");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}