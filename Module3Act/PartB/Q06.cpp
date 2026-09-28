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
 Exercise Q06 - Shape with Caption
 ------------------------------------
 Objective: Practice combining ordinary geometry with
 a bitmap-text caption.

 This program draws a filled golden triangle and displays
 a short caption below it.
 */

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangle
    glColor3f(1.0f, 0.65f, 0.20f); // golden orange
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, -0.15f); // bottom-left
        glVertex2f(0.35f, -0.15f); // bottom-right
        glVertex2f(0.0f, 0.50f); // top
    glEnd();

    // Draw the caption
    glColor3f(0.75f, 0.85f, 1.0f); // light blue
    glRasterPos2f(-0.28f, -0.45f); // below the triangle
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        "A Golden Triangle"
    );

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Q06 - Shape with Caption");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}