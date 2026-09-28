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
 Exercise Q12 - Idle-Driven Bouncing Label
 ------------------------------------
 Objective: Practice using glutIdleFunc for continuous
 text animation.

 This program continuously moves a text label horizontally
 and reverses its direction at the window edges.
 */

float labelX = -0.9f;
float speed = 0.002f;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.75f, 0.55f, 1.0f); // light purple
    glRasterPos2f(labelX, 0.0f); // moving position
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        "Bouncing Label"
    );

    glFlush();
}

void animateLabel() {
    labelX += speed; // move horizontally

    if (labelX >= 0.45f || labelX <= -0.9f) {
        speed = -speed; // reverse direction
    }

    glutPostRedisplay(); // redraw every idle tick
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 400);
    glutCreateWindow("Q12 - Idle-Driven Bouncing Label");

    glutDisplayFunc(display);
    glutIdleFunc(animateLabel); // register idle callback
    glutMainLoop();

    return 0;
}