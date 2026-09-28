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
 Exercise Q02 - Font Size Comparison
 ------------------------------------
 Objective: Practice using different GLUT bitmap font constants
 to display the same phrase in different font sizes.

 This program displays the phrase "Computer Graphics" three times
 using three different bitmap fonts and colors.
 */

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Small font
    glColor3f(0.6f, 0.8f, 1.0f);  // light blue
    glRasterPos2f(-0.35f, 0.45f);  // top
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_10,
        "Computer Graphics"
    );

    // Medium font
    glColor3f(0.8f, 0.5f, 1.0f);  // light purple
    glRasterPos2f(-0.35f, 0.0f);   // center
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        "Computer Graphics"
    );

    // Large font
    glColor3f(1.0f, 0.6f, 0.4f);   // soft orange
    glRasterPos2f(-0.35f, -0.45f); // bottom
    drawBitmapString(
        GLUT_BITMAP_TIMES_ROMAN_24,
        "Computer Graphics"
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q02 - Font Size Comparison");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}