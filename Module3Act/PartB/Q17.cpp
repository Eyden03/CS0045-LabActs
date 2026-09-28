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
 Exercise Q17 - Mouse-Controlled Stopwatch
 ------------------------------------
 Objective: Practice combining mouse controls with a
 self-rescheduling timer and running state.

 This program uses the left mouse button to start or resume
 the stopwatch and the right mouse button to pause it.
 */

int elapsedSeconds = 0;
bool running = false;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    char stopwatchText[40];

    snprintf(
        stopwatchText,
        sizeof(stopwatchText),
        "Elapsed time: %d seconds",
        elapsedSeconds
    );

    if (running) {
        glColor3f(0.45f, 1.0f, 0.65f); // mint green
    } else {
        glColor3f(1.0f, 0.60f, 0.75f); // soft pink
    }

    glRasterPos2f(-0.35f, 0.0f); // near the center
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, stopwatchText);

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            running = true; // start or resume
        } else if (button == GLUT_RIGHT_BUTTON) {
            running = false; // pause
        }

        glutPostRedisplay(); // update text color
    }
}

void updateStopwatch(int value) {
    if (running) {
        elapsedSeconds++; // count while running
        glutPostRedisplay();
    }

    glutTimerFunc(1000, updateStopwatch, 0); // keep timer active
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 400);
    glutCreateWindow("Q17 - Mouse-Controlled Stopwatch");

    glutDisplayFunc(display);
    glutMouseFunc(mouse); // register mouse controls
    glutTimerFunc(1000, updateStopwatch, 0); // start timer cycle
    glutMainLoop();

    return 0;
}