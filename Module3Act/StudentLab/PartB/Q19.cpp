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
 Exercise Q19 - HUD Score with Color Milestones
 ------------------------------------
 Objective: Practice combining click counting, HUD-style
 text, and conditional color changes.

 This program adds one point for every left click and
 changes the shape's color at every multiple of five.
 */

int score = 0;
float shapeRed = 0.75f;
float shapeGreen = 0.50f;
float shapeBlue = 1.0f;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the shape
    glColor3f(shapeRed, shapeGreen, shapeBlue);
    glBegin(GL_POLYGON);
        glVertex2f(-0.30f, -0.30f); // bottom-left
        glVertex2f(-0.30f, 0.30f); // top-left
        glVertex2f(0.30f, 0.30f); // top-right
        glVertex2f(0.30f, -0.30f); // bottom-right
    glEnd();

    // Draw the HUD score
    char scoreText[32];
    snprintf(
        scoreText,
        sizeof(scoreText),
        "Score: %d",
        score
    );

    glColor3f(0.75f, 0.90f, 1.0f); // light blue
    glRasterPos2f(-0.90f, 0.85f); // top-left
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, scoreText);

    glFlush();
}

void updateColor() {
    int colorStage = (score / 5) % 4;

    switch (colorStage) {
        case 0:
            shapeRed = 0.75f;
            shapeGreen = 0.50f;
            shapeBlue = 1.0f; // light purple
            break;

        case 1:
            shapeRed = 0.40f;
            shapeGreen = 0.90f;
            shapeBlue = 0.65f; // mint green
            break;

        case 2:
            shapeRed = 1.0f;
            shapeGreen = 0.45f;
            shapeBlue = 0.35f; // coral
            break;

        case 3:
            shapeRed = 1.0f;
            shapeGreen = 0.80f;
            shapeBlue = 0.30f; // golden yellow
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        score++; // add one point

        if (score % 5 == 0) {
            updateColor(); // change at each milestone
        }

        glutPostRedisplay(); // update score and shape
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - HUD Score with Color Milestones");

    glutDisplayFunc(display);
    glutMouseFunc(mouse); // register mouse callback
    glutMainLoop();

    return 0;
}