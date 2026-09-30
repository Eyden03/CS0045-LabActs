#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q08 - Three Triangles, One Array
 ------------------------------------------
 Objective: Practice drawing multiple triangles from one vertex array.
 */

void triangles()
{
    GLfloat triangleVertices[] = {
        -0.85f,  0.45f, 0.0f, // first triangle top
        -0.98f, -0.35f, 0.0f, // first triangle left
        -0.52f, -0.35f, 0.0f, // first triangle right

        -0.23f,  0.45f, 0.0f, // second triangle top
        -0.46f, -0.35f, 0.0f, // second triangle left
         0.00f, -0.35f, 0.0f, // second triangle right

         0.39f,  0.45f, 0.0f, // third triangle top
         0.16f, -0.35f, 0.0f, // third triangle left
         0.62f, -0.35f, 0.0f  // third triangle right
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Coral triangles
    glColor3f(0.95f, 0.30f, 0.25f);
    triangles();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q08 - Three Triangles");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}