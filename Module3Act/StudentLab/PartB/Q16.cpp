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
 Exercise Q16 - Click-and-Drag Square
 ------------------------------------
 Objective: Practice tracking a dragging state across
 mouse and active-motion callbacks.

 This program allows the user to hold the left mouse
 button and drag a square around the window.
 */

float squareX = 0.0f;
float squareY = 0.0f;
bool dragging = false;

// Convert pixel coordinates to OpenGL coordinates
void toOpenGLCoords(int x, int y, float& openGLX, float& openGLY) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    openGLX = (2.0f * x / width) - 1.0f; // convert X
    openGLY = 1.0f - (2.0f * y / height); // convert and flip Y
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.55f, 0.30f); // soft orange
    glBegin(GL_POLYGON);
        glVertex2f(squareX - 0.12f, squareY - 0.12f); // bottom-left
        glVertex2f(squareX - 0.12f, squareY + 0.12f); // top-left
        glVertex2f(squareX + 0.12f, squareY + 0.12f); // top-right
        glVertex2f(squareX + 0.12f, squareY - 0.12f); // bottom-right
    glEnd();

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            dragging = true; // start dragging
            toOpenGLCoords(x, y, squareX, squareY);
            glutPostRedisplay();
        } else if (state == GLUT_UP) {
            dragging = false; // stop dragging
        }
    }
}

void activeMotion(int x, int y) {
    if (dragging) {
        toOpenGLCoords(x, y, squareX, squareY);
        glutPostRedisplay(); // follow the cursor
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Q16 - Click-and-Drag Square");

    glutDisplayFunc(display);
    glutMouseFunc(mouse); // track button state
    glutMotionFunc(activeMotion); // track active dragging
    glutMainLoop();

    return 0;
}