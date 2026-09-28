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
 Exercise Q11 - Entry-Driven Background
 ------------------------------------
 Objective: Practice using glutEntryFunc to detect when
 the mouse pointer enters or leaves the window.

 This program changes the background to light gray when
 the pointer enters and dark gray when it leaves.
 */

float bgColor = 0.15f;

void display() {
    glClearColor(bgColor, bgColor, bgColor, 1.0f); // background color
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

void mouseEntry(int state) {
    if (state == GLUT_ENTERED) {
        bgColor = 0.75f; // light gray
    } else if (state == GLUT_LEFT) {
        bgColor = 0.15f; // dark gray
    }

    glutPostRedisplay(); // redraw window
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 400);
    glutCreateWindow("Q11 - Entry-Driven Background");

    glutDisplayFunc(display);
    glutEntryFunc(mouseEntry); // register entry callback
    glutMainLoop();

    return 0;
}