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
 * Example 10 - glutMotionFunc: Active Motion (Dragging)
 * ------------------------------------
* Concept: The active motion callback fires only while a
mouse button IS
 * held down and the mouse moves. This example draws a
point wherever the
 * mouse is dragged, converting pixel coordinates to
OpenGL's -1..1 range.
 */

float lastX = 0.0f, lastY = 0.0f;
bool hasPoint = false;

void toOpenGLCoords(int x, int y, float& outX, float& outY)
{
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    outX = (2.0f * x / w) - 1.0f;
    outY = 1.0f - (2.0f * y / h);   // pixel Y grows downward; OpenGL Y grows upward
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (hasPoint) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        glVertex2f(lastX, lastY);
        glEnd();
    }
    glFlush();
}
void detectMotion(int x, int y) {
    toOpenGLCoords(x, y, lastX, lastY);
    hasPoint = true;
    cout << x << " " << y << endl;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ex10 - Drag the Mouse to Place a Point"); 
        glutDisplayFunc(display);
    glutMotionFunc(detectMotion);
    glutMainLoop();
    return 0;
}