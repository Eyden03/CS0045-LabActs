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
 Exercise Q01 - Display Your Name
 ------------------------------------
 Objective: Practice displaying bitmap text using glColor3f,
 glRasterPos2f, and the GLUT_BITMAP_HELVETICA_18 font.

 This program displays my full name as white bitmap text near
 the center of the window.
 */

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);  // white
    glRasterPos2f(-0.42f, 0.0f);   // near the center

    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        "Aidhen Angel Pocsidio"
    );

    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Q01 - Display Your Name");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}