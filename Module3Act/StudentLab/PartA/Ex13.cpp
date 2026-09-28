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
* Example 13 - glutIdleFunc: Continuously Animate a Text
Label
 * ------------------------------------
 * Concept: glutIdleFunc sets the global idle callback,
which GLUT calls
 * repeatedly whenever no other events are pending - the
classic way to
 * drive continuous animation.
 */

float px = -0.8f;
float speed = 0.01f;

// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(px, 0.0f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Sliding Label");
    glFlush();
}

void animateText() {
    px += speed;
    if (px > 0.6f || px < -0.9f) {
        speed = -speed;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Ex13 - glutIdleFunc Animated Label");
    glutDisplayFunc(display);
    glutIdleFunc(animateText);
    glutMainLoop();
    return 0;
}