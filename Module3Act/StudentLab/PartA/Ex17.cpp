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
 * Example 17 - glutFullScreen: Toggle Fullscreen on Click
 * ------------------------------------
 * Concept: glutFullScreen() requests that the CURRENT
window be made
 * full screen. There is no built-in "un-fullscreen" call
in classic
 * GLUT, so this example uses glutReshapeWindow to manually
restore the
 * original size.
 */

bool isFullscreen = false;

// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.5f, 0.0f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Click to toggle fullscreen");
    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!isFullscreen) {
            glutFullScreen();
        }
        else {
            glutReshapeWindow(600, 400);
        }
        isFullscreen = !isFullscreen;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Ex17 - glutFullScreen (click to toggle)");
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}