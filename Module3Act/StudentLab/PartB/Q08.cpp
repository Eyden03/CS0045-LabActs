#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q08 - Clamped Keyboard Movement
 ------------------------------------
 Objective: Practice keyboard-controlled movement with
 boundary clamping.

 This program uses the 'a' and 'd' keys to move a square
 left and right without allowing it to pass the window edges.
 */

float squareX = 0.0f;
const float squareHalfWidth = 0.1f;
const float moveSpeed = 0.05f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.85f, 0.45f, 0.75f); // soft pink
    glBegin(GL_POLYGON);
        glVertex2f(squareX - squareHalfWidth, -0.1f); // bottom-left
        glVertex2f(squareX - squareHalfWidth, 0.1f); // top-left
        glVertex2f(squareX + squareHalfWidth, 0.1f); // top-right
        glVertex2f(squareX + squareHalfWidth, -0.1f); // bottom-right
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            squareX -= moveSpeed; // move left
            break;

        case 'd':
            squareX += moveSpeed; // move right
            break;
    }

    if (squareX < -0.9f) {
        squareX = -0.9f; // clamp left edge
    }

    if (squareX > 0.9f) {
        squareX = 0.9f; // clamp right edge
    }

    glutPostRedisplay(); // redraw window
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q08 - Clamped Keyboard Movement");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // register keyboard callback
    glutMainLoop();

    return 0;
}