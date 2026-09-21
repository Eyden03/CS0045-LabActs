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
 * Example 02 - Comparing GLUT Bitmap Font Constants
 * ------------------------------------
 * Concept: GLUT provides several fixed-size bitmap fonts.
This example
 * stacks the same word in four different fonts so students
can compare
 * their size and style directly.
 */

 // Portable helper function to render string character-by character
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(-0.8f, 0.6f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_10, "Helvetica 10 - FEU TECH");

    glRasterPos2f(-0.8f, 0.3f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Helvetica 18 - FEU TECH");

    glRasterPos2f(-0.8f, 0.0f);
    drawBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, "Times Roman 10 - FEU TECH");

    glRasterPos2f(-0.8f, -0.3f);
    drawBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Times Roman 24 - FEU TECH");
    glRasterPos2f(-0.8f, -0.6f);
    drawBitmapString(GLUT_BITMAP_9_BY_15, "9 by 15 - FEU TECH");

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Ex02 - GLUT Bitmap Font Comparison");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}