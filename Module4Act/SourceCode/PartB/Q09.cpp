#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q09 - Indexed Triangle Fan Pentagon
 ---------------------------------------------
 Objective: Practice using glDrawElements with GL_TRIANGLE_FAN.
 */

void pentagon()
{
    GLfloat pentagonVertices[] = {
         0.0f,  0.0f, 0.0f, // center
         0.0f,  0.70f, 0.0f, // top
         0.67f,  0.22f, 0.0f, // upper-right
         0.42f, -0.57f, 0.0f, // lower-right
        -0.42f, -0.57f, 0.0f, // lower-left
        -0.67f,  0.22f, 0.0f  // upper-left
    };

    GLubyte pentagonIndices[] = {
        0, 1, 2, 3, 4, 5, 1 // center and outer ring
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pentagonVertices);
    glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_BYTE, pentagonIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Pink pentagon
    glColor3f(0.95f, 0.20f, 0.60f);
    pentagon();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);

    glutCreateWindow("Q09 - Indexed Triangle Fan Pentagon");
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}