#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

int currentShape = 1;

GLfloat triangleVertices[] = {
     0.0f,  0.70f, 0.0f,
    -0.65f, -0.45f, 0.0f,
     0.65f, -0.45f, 0.0f
};

GLfloat quadVertices[] = {
    -0.55f, -0.55f, 0.0f,
     0.55f, -0.55f, 0.0f,
     0.55f,  0.55f, 0.0f,
    -0.55f,  0.55f, 0.0f
};

GLfloat pentagonVertices[] = {
     0.0f,  0.70f, 0.0f,
     0.67f, 0.22f, 0.0f,
     0.42f, -0.57f, 0.0f,
    -0.42f, -0.57f, 0.0f,
    -0.67f, 0.22f, 0.0f
};

/*
 Exercise Q18 - Keyboard-Switched Vertex Arrays
 -----------------------------------------------
 Objective: Practice switching between vertex arrays using the keyboard.
 */

void drawShape()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    if (currentShape == 1)
    {
        glColor3f(1.0f, 0.35f, 0.20f); // orange
        glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    else if (currentShape == 2)
    {
        glColor3f(0.20f, 0.65f, 1.0f); // blue
        glVertexPointer(3, GL_FLOAT, 0, quadVertices);
        glDrawArrays(GL_QUADS, 0, 4);
    }
    else if (currentShape == 3)
    {
        glColor3f(0.75f, 0.25f, 0.95f); // purple
        glVertexPointer(3, GL_FLOAT, 0, pentagonVertices);
        glDrawArrays(GL_POLYGON, 0, 5);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawShape();

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        currentShape = 1;
    }
    else if (key == '2')
    {
        currentShape = 2;
    }
    else if (key == '3')
    {
        currentShape = 3;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q18 - Keyboard-Switched Vertex Arrays");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}