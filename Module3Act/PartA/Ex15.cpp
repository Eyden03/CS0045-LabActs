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
 * Example 15 - glutTimerFunc: Countdown Timer as Text 
 * ------------------------------------ 
* Concept: Combines glutTimerFunc with drawBitmapString to 
build a 
 * simple countdown display, decrementing once per second 
until it 
 * reaches zero. 
 */ 
 
int secondsLeft = 10; 
 
// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(1.0f, 1.0f, 1.0f); 
 
    char buffer[32]; 
    snprintf(buffer, sizeof(buffer), "Time left: %d", secondsLeft); 
    glRasterPos2f(-0.3f, 0.0f); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer); 
 
    glFlush(); 
} 
 
void tick(int value) { 
    if (secondsLeft > 0) { 
 secondsLeft--; 
        glutPostRedisplay(); 
        glutTimerFunc(1000, tick, 0); 
    } 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 300); 
    glutCreateWindow("Ex15 - Countdown Timer"); 
    glutDisplayFunc(display); 
    glutTimerFunc(1000, tick, 0); 
    glutMainLoop(); 
    return 0; 
} 