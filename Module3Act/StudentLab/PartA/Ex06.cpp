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
 * Example 06 - Window Initialization and Configuration 
 * ------------------------------------ 
 * Concept: glutInitWindowSize and glutInitWindowPosition 
configure the 
 * window BEFORE glutCreateWindow actually creates it - 
this is the 
 * "Key Components" sequence from the lecture slides. 
 */
// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void display() { 
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT); 
 
    glColor3f(0.0f, 0.0f, 0.0f); 
    glRasterPos2f(-0.6f, 0.0f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "1024 x 768 window at (400, 100)"); 
 
    glFlush(); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(1024, 768); 
    glutInitWindowPosition(400, 100); 
    glutCreateWindow("Ex06 - Window Init and Configuration"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
} 