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
 Exercise Q09 - Active Motion Coordinate Display
 ------------------------------------
 Objective: Practice using glutMotionFunc with
 pixel-to-OpenGL coordinate conversion.

 This program displays the cursor's OpenGL coordinates
 while a mouse button is held and dragged.
 */

float cursorX = 0.0f;
float cursorY = 0.0f;
bool hasDragged = false;

// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Convert pixel coordinates to OpenGL coordinates
void toOpenGLCoords(int x, int y, float& openGLX, float& openGLY) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

    openGLX = (2.0f * x / width) - 1.0f; // convert X
    openGLY = 1.0f - (2.0f * y / height); // convert and flip Y
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (hasDragged) {
        char coordinates[64];

        snprintf(
            coordinates,
            sizeof(coordinates),
            "OpenGL Position: (%.2f, %.2f)",
            cursorX,
            cursorY
        );

        glColor3f(0.95f, 0.65f, 0.85f); // light pink
        glRasterPos2f(-0.48f, 0.0f); // near the center
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, coordinates);
    }
    else {
        glColor3f(0.65f, 0.85f, 1.0f); // light blue
        glRasterPos2f(-0.45f, 0.0f); // near the center
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "Hold a mouse button and drag"
        );
    }

    glFlush();
}

void activeMotion(int x, int y) {
    toOpenGLCoords(x, y, cursorX, cursorY);
    hasDragged = true;

    glutPostRedisplay(); // update coordinates
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q09 - Active Motion Coordinate Display");

    glutDisplayFunc(display);
    glutMotionFunc(activeMotion); // register active motion callback
    glutMainLoop();

    return 0;
}