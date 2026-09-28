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
 Exercise Q15 - 30-Second Countdown Timer
 ------------------------------------
 Objective: Practice using a self-rescheduling timer
 with a terminating condition.

 This program displays a 30-second countdown. When the
 timer reaches zero, it displays "Time's up!" and stops.
 */

int secondsLeft = 30;
bool timeUp = false;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (timeUp) {
        glColor3f(1.0f, 0.45f, 0.35f); // coral
        glRasterPos2f(-0.15f, 0.0f); // near the center
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "Time's up!"
        );
    } else {
        char timerText[32];

        snprintf(
            timerText,
            sizeof(timerText),
            "Time left: %d",
            secondsLeft
        );

        glColor3f(0.45f, 0.90f, 1.0f); // light cyan
        glRasterPos2f(-0.18f, 0.0f); // near the center
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, timerText);
    }

    glFlush();
}

void updateTimer(int value) {
    if (secondsLeft > 0) {
        secondsLeft--; // decrease by one
    }

    if (secondsLeft == 0) {
        timeUp = true; // countdown finished
    }

    glutPostRedisplay(); // update displayed time

    if (secondsLeft > 0) {
        glutTimerFunc(1000, updateTimer, 0); // schedule next tick
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 350);
    glutCreateWindow("Q15 - 30-Second Countdown Timer");

    glutDisplayFunc(display);
    glutTimerFunc(1000, updateTimer, 0); // start timer
    glutMainLoop();

    return 0;
}