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
 * Example 18 - Full Callback Integration
 * ------------------------------------
 * Concept: Mirrors the lecture's complete sample program,
wiring up
 * EVERY major GLUT callback in one application: display,
keyboard,
 * mouse, motion, passive motion, and entry.
 */

float px = 0.0f, py = 0.0f;

// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void keyboardMonitor(unsigned char key, int x, int y) {
    cout << key << endl;
    switch (key) {
    case 'a': px -= 0.02f; break;
    case 'd': px += 0.02f; break;
    default:  px = 0.0f;
    }
    glutPostRedisplay();
}

void mouseMonitor(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) cout << "Left button was clicked..." << endl;
        else cout << "Left button was released..." << endl;
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        cout << "Right button was clicked..." << endl;
    }
    else {
        cout << "Middle button was clicked..." << endl;
    }
    cout << x << " " << y << endl;
}

void detectMotion(int x, int y) {
    cout << x << " " << y << endl;
}

void detectPassiveMotion(int x, int y) {
    cout << x << "P " << y << endl;
}

void mouseEntryDetector(int state) {
    if (state == GLUT_LEFT) cout << "Mouse has left the application " << endl;
    else cout << "Mouse has re-entered the application " <<
        endl;
}

void defaultDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2f(px, py);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "FEU-TECH");

    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(200, 50);

    glutCreateWindow("Ex18 - Full Callback Integration");
    glutDisplayFunc(defaultDisplay);
    glutKeyboardFunc(keyboardMonitor);
    glutMouseFunc(mouseMonitor);
    glutMotionFunc(detectMotion);
    glutPassiveMotionFunc(detectPassiveMotion);
    glutEntryFunc(mouseEntryDetector);
    glutMainLoop();

    return 0;
}