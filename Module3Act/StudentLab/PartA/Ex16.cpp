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
 * Example 16 - Combining Text and a Shape 
* ------------------------------------ 
 * Concept: A shape and a text label are just two different 
sets of 
 * drawing calls in the same display() function - order 
does not matter 
 * for 2D flat rendering like this. 
 */ 
 
// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
 
    glColor3f(0.2f, 0.6f, 1.0f); 
    glBegin(GL_TRIANGLES); 
        glVertex2f(-0.3f, -0.3f); 
        glVertex2f( 0.3f, -0.3f); 
        glVertex2f( 0.0f,  0.3f); 
    glEnd(); 
 
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f(-0.35f, -0.6f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Figure 1: A Triangle"); 
 
    glFlush(); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 500); 
    glutCreateWindow("Ex16 - Shape with a Caption"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
} 