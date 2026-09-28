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
 * Example 20 - Capstone: Interactive Text Placer 
 * ------------------------------------ 
 * Concept: Combines glutMouseFunc, pixel-to-OpenGL 
coordinate conversion 
 * (using glutGet(GLUT_WINDOW_WIDTH/HEIGHT)), and 
glRasterPos2f: clicking 
 * anywhere in the window moves the text label to that 
exact spot. 
 */ 
 
float labelX = -0.3f, labelY = 0.0f; 
 
// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void toOpenGLCoords(int x, int y, float &outX, float &outY) 
{ 
    int w = glutGet(GLUT_WINDOW_WIDTH); 
    int h = glutGet(GLUT_WINDOW_HEIGHT); 
    outX = (2.0f * x / w) - 1.0f; 
    outY = 1.0f - (2.0f * y / h); 
} 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(1.0f, 0.85f, 0.2f); 
    glRasterPos2f(labelX, labelY); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Click anywhere!"); 
    glFlush(); 
} 
 
void onClick(int button, int state, int x, int y) { 
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
        toOpenGLCoords(x, y, labelX, labelY); 
        glutPostRedisplay(); 
    } 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(700, 500); 
    glutCreateWindow("Ex20 - Interactive Text Placer"); 
    glutDisplayFunc(display); 
    glutMouseFunc(onClick); 
    glutMainLoop(); 
return 0; 
} 