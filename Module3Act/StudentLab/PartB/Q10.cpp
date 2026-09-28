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
 Exercise Q10 - Passive Motion Pixel Readout
 ------------------------------------
 Objective: Practice using glutPassiveMotionFunc to
 track the mouse without pressing any button.

 This program displays the mouse position using raw
 pixel coordinates as the pointer moves over the window.
 */

int mouseX = 0;
int mouseY = 0;
bool hasMoved = false;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (hasMoved) {
        char coordinates[64];

        snprintf(
            coordinates,
            sizeof(coordinates),
            "Mouse at (%d, %d)",
            mouseX,
            mouseY
        );

        glColor3f(0.55f, 1.0f, 0.75f); // mint green
        glRasterPos2f(-0.25f, 0.0f); // near the center
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, coordinates);
    } else {
        glColor3f(0.75f, 0.65f, 1.0f); // light purple
        glRasterPos2f(-0.38f, 0.0f); // near the center
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "Move the mouse inside the window"
        );
    }

    glFlush();
}

void passiveMotion(int x, int y) {
    mouseX = x; // raw pixel X
    mouseY = y; // raw pixel Y
    hasMoved = true;

    glutPostRedisplay(); // update coordinates
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q10 - Passive Motion Pixel Readout");

    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMotion); // register passive motion
    glutMainLoop();

    return 0;
}