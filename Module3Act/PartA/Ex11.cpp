#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#include <GL/freeglut_ext.h> 
#endif 
#include <cstdio> 
#include <iostream>
using namespace std;

/*
 * Example 11 - glutPassiveMotionFunc: Track Mouse Without
Clicking
 * ------------------------------------
 * Concept: The passive motion callback fires when the
mouse moves within
 * the window while NO button is pressed - useful for hover
effects and
 * live coordinate readouts.
 */

int mouseX = 0, mouseY = 0;

// Portable helper function replacing FreeGLUT's glutBitmapString
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Mouse at (%d, %d)",
        mouseX, mouseY);
    glRasterPos2f(-0.4f, 0.0f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);
    glFlush();
}

void detectPassiveMotion(int x, int y) {
    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Ex11 - Passive Motion (Move Mouse, No Click)"); 
        glutDisplayFunc(display);
    glutPassiveMotionFunc(detectPassiveMotion);
    glutMainLoop();
    return 0;
}