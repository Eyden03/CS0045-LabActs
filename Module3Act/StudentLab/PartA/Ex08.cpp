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
 * Example 08 - glutKeyboardFunc: Move Text with 'a' / 'd' 
 * ------------------------------------ 
 * Concept: Mirrors the lecture's keyboardMonitor() sample - pressing 'a' 
 * moves the label left, 'd' moves it right, and any other 
key resets it. 
 */ 
 
float px = 0.0f, py = 0.0f; 
 
// Portable helper function replacing FreeGLUT's glutBitmapString 
void drawBitmapString(void* font, const char* str) { 
 for (const char* c = str; *c != '\0'; c++) { 
        glutBitmapCharacter(font, *c); 
    } 
} 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(0.0f, 0.4f, 1.0f); 
    glRasterPos2f(px, py); 
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, "FEU-TECH"); 
    glFlush(); 
} 
 
void keyboardMonitor(unsigned char key, int x, int y) { 
    cout << key << endl; 
    switch (key) { 
        case 'a': 
            px -= 0.02f; 
            break; 
        case 'd': 
            px += 0.02f; 
            break; 
        default: 
            px = 0.0f; 
    } 
    glutPostRedisplay(); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(1024, 768); 
    glutInitWindowPosition(200, 50);
    glutCreateWindow("Ex08 - Move Text (a = left, d = right)"); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboardMonitor); 
    glutMainLoop(); 
    return 0; 
}