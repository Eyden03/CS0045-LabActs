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
 * Example 09 - glutMouseFunc: Log Clicks and Change Color
 * ------------------------------------
 * Concept: glutMouseFunc's callback fires on every press
AND release.
 * button is one of
GLUT_LEFT_BUTTON/GLUT_MIDDLE_BUTTON/GLUT_RIGHT_BUTTON;
 * state is either GLUT_DOWN or GLUT_UP.
 */
float sqColor[3] = { 1.0f, 1.0f, 1.0f };

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(sqColor[0], sqColor[1], sqColor[2]);
    glBegin(GL_POLYGON);
    glVertex2f(-0.3f, -0.3f);
    glVertex2f(-0.3f, 0.3f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.3f, -0.3f);
    glEnd();
    glFlush();
}

void mouseMonitor(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cout << "Left button was clicked..." << endl;
        sqColor[0] = 1.0f; sqColor[1] = 0.0f; sqColor[2] =
            0.0f;  // red 
    }
    else if (button == GLUT_RIGHT_BUTTON && state ==
        GLUT_DOWN) {
        cout << "Right button was clicked..." << endl;
        sqColor[0] = 0.0f; sqColor[1] = 0.4f; sqColor[2] =
            1.0f;  // blue 
    }
    else if (button == GLUT_MIDDLE_BUTTON && state ==
        GLUT_DOWN) {
        cout << "Middle button was clicked..." << endl;
        sqColor[0] = 0.0f; sqColor[1] = 1.0f; sqColor[2] =
            0.0f;  // green 
    }
    cout << x << " " << y << endl;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex09 - Mouse Clicks Change Square Color"); 
        glutDisplayFunc(display);
    glutMouseFunc(mouseMonitor);
    glutMainLoop();
    return 0;
}