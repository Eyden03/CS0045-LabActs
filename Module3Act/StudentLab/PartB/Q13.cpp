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
 Exercise Q13 - Timer-Driven Counter
 ------------------------------------
 Objective: Practice using a self-rescheduling
 glutTimerFunc callback.

 This program increments and displays an on-screen
 counter once every second.
 */

int counter = 0;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    char counterText[32];
    snprintf(
        counterText,
        sizeof(counterText),
        "Counter: %d",
        counter
    );

    glColor3f(1.0f, 0.80f, 0.35f); // warm yellow
    glRasterPos2f(-0.18f, 0.0f); // near the center
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, counterText);

    glFlush();
}

void updateCounter(int value) {
    counter++; // add one every second

    glutPostRedisplay(); // update displayed counter
    glutTimerFunc(1000, updateCounter, 0); // schedule next update
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 350);
    glutCreateWindow("Q13 - Timer-Driven Counter");

    glutDisplayFunc(display);
    glutTimerFunc(1000, updateCounter, 0); // start timer
    glutMainLoop();

    return 0;
}