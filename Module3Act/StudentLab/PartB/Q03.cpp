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
 Exercise Q03 - Custom Window Setup
 ------------------------------------
 Objective: Practice configuring the window size, screen position,
 and title before creating the OpenGL window.

 This program creates an 800x500 window positioned at (150, 150)
 on the screen with the title "My Custom Window".
 */

void display() {
    glClearColor(0.08f, 0.18f, 0.20f, 1.0f);  // dark teal
    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitWindowSize(800, 500); // window size
    glutInitWindowPosition(150, 150); // screen position
    glutCreateWindow("My Custom Window");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}