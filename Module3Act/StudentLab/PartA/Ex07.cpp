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
 * Example 07 - glutPostRedisplay Basics 
 * ------------------------------------ 
 * Concept: glutPostRedisplay marks the current window as 
needing to be 
 * redrawn. GLUT will call display() again soon after. 
Pressing SPACE 
 * toggles a message and requests a redraw. 
 */ 
 
bool toggled = false; 
 
// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) { 
    for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
}
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRasterPos2f(-0.5f, 0.0f); 
 
    if (toggled) { 
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Toggled ON"); 
    } else { 
        drawBitmapString(GLUT_BITMAP_HELVETICA_18, "Toggled OFF"); 
    } 
 
    glFlush(); 
} 
 
void keyboard(unsigned char key, int x, int y) { 
    if (key == ' ') { 
        toggled = !toggled; 
        glutPostRedisplay();   // ask GLUT to call display() again 
    } 
    if (key == 27) exit(0); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 300); 
    glutCreateWindow("Ex07 - glutPostRedisplay (press SPACE)"); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard);
      glutMainLoop(); 
    return 0; 
} 