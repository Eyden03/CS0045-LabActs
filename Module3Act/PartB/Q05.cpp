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
 Exercise Q05 - Mouse Button Text Color
 ------------------------------------
 Objective: Practice using glutMouseFunc with conditional
 bitmap text and color changes.

 This program displays green text after a left click and
 red text after a right click.
 */

int selectedButton = 0;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (selectedButton == 1) {
        glColor3f(0.0f, 1.0f, 0.0f); // green
        glRasterPos2f(-0.25f, 0.0f); // near the center
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "Left button text"
        );
    } else if (selectedButton == 2) {
        glColor3f(1.0f, 0.0f, 0.0f); // red
        glRasterPos2f(-0.28f, 0.0f); // near the center
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "Right button text"
        );
    } else {
        glColor3f(0.8f, 0.7f, 1.0f); // light purple
        glRasterPos2f(-0.38f, 0.0f); // near the center
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "Click the left or right mouse button"
        );
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            selectedButton = 1; // left click
        } else if (button == GLUT_RIGHT_BUTTON) {
            selectedButton = 2; // right click
        }

        glutPostRedisplay(); // redraw window
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(650, 350);
    glutCreateWindow("Q05 - Mouse Button Text Color");

    glutDisplayFunc(display);
    glutMouseFunc(mouse); // register mouse callback
    glutMainLoop();

    return 0;
}