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
 Exercise Q04 - Keyboard Background Color Switch
 ------------------------------------
 Objective: Practice using glutKeyboardFunc and
 glutPostRedisplay to change the window background.

 This program changes the background to red, green, or blue
 when the user presses the corresponding keyboard key.
 */

float bgRed = 0.15f;
float bgGreen = 0.15f;
float bgBlue = 0.15f;

void display() {
    glClearColor(bgRed, bgGreen, bgBlue, 1.0f); // background color
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            bgRed = 1.0f;
            bgGreen = 0.0f;
            bgBlue = 0.0f; // red
            break;

        case 'g':
            bgRed = 0.0f;
            bgGreen = 1.0f;
            bgBlue = 0.0f; // green
            break;

        case 'b':
            bgRed = 0.0f;
            bgGreen = 0.0f;
            bgBlue = 1.0f; // blue
            break;
    }

    glutPostRedisplay(); // redraw window
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q04 - Keyboard Background Color Switch");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard); // register keyboard callback
    glutMainLoop();

    return 0;
}