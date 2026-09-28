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
 * Example 14 - glutTimerFunc: Move a Shape Every Second
 * ------------------------------------
 * Concept: glutTimerFunc(msecs, func, value) schedules
func to be called
 * ONCE after msecs milliseconds, passing it value. To
repeat, the timer
 * callback must call glutTimerFunc again itself - this is
called a
 * "self-rescheduling" timer.
 */

float px = -0.6f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.6f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(px - 0.1f, -0.1f);
    glVertex2f(px - 0.1f, 0.1f);
    glVertex2f(px + 0.1f, 0.1f);
    glVertex2f(px + 0.1f, -0.1f);
    glEnd();
    glFlush();
}

void animateStep(int value) {
    px += 0.1f;
    if (px > 0.6f) px = -0.6f;

    glutPostRedisplay();
    glutTimerFunc(1000, animateStep, value);  // reschedule itself every 1000ms 
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Ex14 - glutTimerFunc Moves a Square Every Second");
    glutDisplayFunc(display);
    glutTimerFunc(1000, animateStep, 0);
    glutMainLoop();
    return 0;
}