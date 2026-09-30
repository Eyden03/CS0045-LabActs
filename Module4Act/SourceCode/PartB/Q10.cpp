#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q10 - Checkerboard Row via glDrawElements
 ---------------------------------------------------
 Objective: Practice using shared vertices and separate index lists.
 */

void checkerboard()
{
    GLfloat vertices[] = {
        -0.90f, -0.30f, 0.0f, // 0 bottom
        -0.90f,  0.30f, 0.0f, // 1 top
        -0.45f, -0.30f, 0.0f, // 2 bottom
        -0.45f,  0.30f, 0.0f, // 3 top
         0.00f, -0.30f, 0.0f, // 4 bottom
         0.00f,  0.30f, 0.0f, // 5 top
         0.45f, -0.30f, 0.0f, // 6 bottom
         0.45f,  0.30f, 0.0f, // 7 top
         0.90f, -0.30f, 0.0f, // 8 bottom
         0.90f,  0.30f, 0.0f  // 9 top
    };

    GLubyte firstQuad[] = {0, 2, 3, 1};
    GLubyte secondQuad[] = {2, 4, 5, 3};
    GLubyte thirdQuad[] = {4, 6, 7, 5};
    GLubyte fourthQuad[] = {6, 8, 9, 7};

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    // Black and white checkerboard
    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, firstQuad);

    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, secondQuad);

    glColor3f(0.0f, 0.0f, 0.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, thirdQuad);

    glColor3f(1.0f, 1.0f, 1.0f);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, fourthQuad);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    checkerboard();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);

    glutCreateWindow("Q10 - Checkerboard Row");
    glutDisplayFunc(display);

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    glutMainLoop();

    return 0;
}