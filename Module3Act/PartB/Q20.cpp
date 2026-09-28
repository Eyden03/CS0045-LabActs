#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
using namespace std;

/*
 Exercise Q20 - Interactive Text Placer
 ------------------------------------
 Objective: Practice integrating coordinate conversion,
 mouse clicks, passive motion, and idle animation.

 This program moves a pulsing shape and its text label to
 the clicked position while displaying live mouse coordinates.
 */

float markerX = 0.0f;
float markerY = 0.0f;
float mouseX = 0.0f;
float mouseY = 0.0f;
float pulseAngle = 0.0f;
float markerSize = 0.10f;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Convert pixel coordinates to OpenGL coordinates
void toGL(int x, int y, float& openGLX, float& openGLY) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    openGLX = (2.0f * x / width) - 1.0f; // convert X
    openGLY = 1.0f - (2.0f * y / height); // convert and flip Y
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the pulsing marker
    glColor3f(0.85f, 0.45f, 0.80f); // soft pink
    glBegin(GL_POLYGON);
        glVertex2f(markerX - markerSize, markerY - markerSize); // bottom-left
        glVertex2f(markerX - markerSize, markerY + markerSize); // top-left
        glVertex2f(markerX + markerSize, markerY + markerSize); // top-right
        glVertex2f(markerX + markerSize, markerY - markerSize); // bottom-right
    glEnd();

    // Draw the marker label
    glColor3f(1.0f, 0.85f, 0.45f); // soft yellow
    glRasterPos2f(
        markerX + markerSize + 0.03f,
        markerY
    );
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        "My Marker"
    );

    // Draw the live coordinate readout
    char coordinateText[64];

    snprintf(
        coordinateText,
        sizeof(coordinateText),
        "Mouse: (%.2f, %.2f)",
        mouseX,
        mouseY
    );

    glColor3f(0.55f, 0.90f, 1.0f); // light cyan
    glRasterPos2f(-0.95f, 0.90f); // top-left
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        coordinateText
    );

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        toGL(x, y, markerX, markerY); // move marker
        glutPostRedisplay();
    }
}

void passiveMotion(int x, int y) {
    toGL(x, y, mouseX, mouseY); // update live coordinates
    glutPostRedisplay();
}

void animatePulse() {
    pulseAngle += 0.05f; // advance pulse

    markerSize = 0.10f + 0.02f * sin(pulseAngle);

    glutPostRedisplay(); // redraw pulse
    this_thread::sleep_for(chrono::milliseconds(8)); // control idle speed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(750, 550);
    glutCreateWindow("Q20 - Interactive Text Placer");

    glutDisplayFunc(display);
    glutMouseFunc(mouse); // move marker on click
    glutPassiveMotionFunc(passiveMotion); // track mouse
    glutIdleFunc(animatePulse); // animate marker
    glutMainLoop();

    return 0;
}