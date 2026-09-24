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
 * Example 04 - Multiple Text Labels at Different Positions 
 * ------------------------------------ 
 * Concept: Each glRasterPos2f + drawBitmapString pair is 
independent - 
 * you can place as many labels as you like anywhere in the 
window.
 */ 
 
// Helper function replacing non-standard glutBitmapString with glutBitmapCharacter 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(1.0f, 1.0f, 1.0f); 
 
    glRasterPos2f(-0.9f, 0.8f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "Top-Left"); 
 
    glRasterPos2f(0.5f, 0.8f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "Top-Right"); 
 
    glRasterPos2f(-0.9f, -0.9f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "Bottom-Left"); 
 


    glRasterPos2f(0.5f, -0.9f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_12, "Bottom-Right"); 
 
    glRasterPos2f(-0.35f, 0.0f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Center");
    
    glFlush(); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(700, 500); 
    glutCreateWindow("Ex04 - Multiple Text Labels"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
} 