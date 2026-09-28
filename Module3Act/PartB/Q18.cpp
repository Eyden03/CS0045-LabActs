#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

/*
 Exercise Q18 - Entry and Idle Freeze Combo
 ------------------------------------
 Objective: Practice controlling an idle animation using
 state provided by glutEntryFunc.

 This program moves a square only while the mouse pointer
 is inside the window and freezes it when the pointer leaves.
 */

float squareX = 0.0f;
float speed = 0.005f;
bool inside = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.75f, 0.50f, 1.0f); // light purple
    glBegin(GL_POLYGON);
        glVertex2f(squareX - 0.10f, -0.10f); // bottom-left
        glVertex2f(squareX - 0.10f, 0.10f); // top-left
        glVertex2f(squareX + 0.10f, 0.10f); // top-right
        glVertex2f(squareX + 0.10f, -0.10f); // bottom-right
    glEnd();

    glFlush();
}

void mouseEntry(int state) {
    if (state == GLUT_ENTERED) {
        inside = true; // continue animation
    } else if (state == GLUT_LEFT) {
        inside = false; // freeze animation
    }
}


void animateSquare() {
    if (inside) {
        squareX += speed; // move horizontally

        if (squareX >= 0.90f || squareX <= -0.90f) {
            speed = -speed; // reverse direction
        }

        glutPostRedisplay(); // redraw while inside

      
    }

      // to limit idle speed so Windows can process mouse events properly.
        this_thread::sleep_for(chrono::milliseconds(8)); 
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(700, 450);
    glutCreateWindow("Q18 - Entry and Idle Freeze Combo");

    glutDisplayFunc(display);
    glutEntryFunc(mouseEntry); // detect enter and leave
    glutIdleFunc(animateSquare); // control animation
    glutMainLoop();

    return 0;
}
