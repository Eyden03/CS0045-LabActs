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
* Example 03 - Text Color 
 * ------------------------------------ 
 * Concept: glColor3f affects text exactly like it affects 
any other 
 * primitive. IMPORTANT: set the color BEFORE calling 
glRasterPos2f, as 
 * shown on the lecture slides ("Note: Set the color before 
the position"). 
 */ 
 
// Portable helper function using standard GLUT glutBitmapCharacter 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
 
    glColor3f(1.0f, 0.2f, 0.2f);           // red 
    glRasterPos2f(-0.6f, 0.3f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Warning Message"); 
 
    glColor3f(0.2f, 1.0f, 0.4f);           // green 
    glRasterPos2f(-0.6f, -0.1f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Success Message"); 
 
    glFlush(); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 400); 
    glutCreateWindow("Ex03 - Text Color"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
} 