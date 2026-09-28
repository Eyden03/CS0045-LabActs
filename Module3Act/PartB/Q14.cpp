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
 Exercise Q14 - Keyboard and Mouse Combo
 ------------------------------------
 Objective: Practice combining keyboard and mouse
 callbacks that modify the same shared position.

 This program uses the 'w' and 's' keys to move a square
 vertically, while a mouse click resets it to the center.
 */

float squareY = 0.0f;
const float moveSpeed = 0.05f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.40f, 0.80f, 1.0f); // sky blue
    glBegin(GL_POLYGON);
        glVertex2f(-0.12f, squareY - 0.12f); // bottom-left
        glVertex2f(-0.12f, squareY + 0.12f); // top-left
        glVertex2f(0.12f, squareY + 0.12f); // top-right
        glVertex2f(0.12f, squareY - 0.12f); // bottom-right
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            squareY += moveSpeed; // move up
            break;

        case 's':
            squareY -= moveSpeed; // move down
            break;
    }

    glutPostRedisplay(); // redraw after key press
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        squareY = 0.0f; // reset to center
        glutPostRedisplay(); // redraw after click
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q14 - Keyboard and Mouse Combo");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // register keyboard callback
    glutMouseFunc(mouse); // register mouse callback
    glutMainLoop();

    return 0;
}