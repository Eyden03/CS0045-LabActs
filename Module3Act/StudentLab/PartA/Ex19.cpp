#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#include <GL/freeglut_ext.h> 
#endif 
#include <cstdio> 
#include <iostream> 
using namespace std; 

/* 
 * Example 19 - HUD-Style Overlay 
 * ------------------------------------ 
 * Concept: Many games overlay 2D text (a "HUD" - heads-up 
display) on 
 * top of a scene. Here, clicking increases a score counter 
shown as 
 * bitmap text above a simple shape "scene". 
 */ 
 
int score = 0; 
 
// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
 
    // "scene" 
    glColor3f(0.2f, 0.7f, 0.3f); 
    glBegin(GL_POLYGON); 
        glVertex2f(-0.3f, -0.3f); 
        glVertex2f(-0.3f,  0.3f); 
        glVertex2f( 0.3f,  0.3f); 
        glVertex2f( 0.3f, -0.3f); 
    glEnd(); 

     // HUD text 
    char buffer[32]; 
    snprintf(buffer, sizeof(buffer), "Score: %d", score); 
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f(-0.9f, 0.85f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer); 
 
    glFlush(); 
} 
 
void onClick(int button, int state, int x, int y) { 
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
        score += 10; 
        glutPostRedisplay(); 
    } 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 600); 
    glutCreateWindow("Ex19 - HUD Overlay (click to score)"); 
    glutDisplayFunc(display); 
    glutMouseFunc(onClick); 
    glutMainLoop(); 
    return 0; 
} 