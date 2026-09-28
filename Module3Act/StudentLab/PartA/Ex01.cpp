#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif
#include <iostream>
using namespace std;
// Helper function to render strings character-by-character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-0.4f, 0.0f);
    // Draw string using standard GLUT function
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Hello, OpenGL!");
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 300);
    glutCreateWindow("Ex01 - Basic Bitmap Text");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}