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
 * Example 12 - glutEntryFunc: Mouse Enter/Leave 
 * ------------------------------------ 
 * Concept: glutEntryFunc's callback fires when the mouse 
pointer enters 
 * or leaves the window. state is GLUT_LEFT (the pointer 
left the window) 
 * or GLUT_ENTERED (the pointer re-entered it). 
 */ 
 
float bg[3] = {0.1f, 0.1f, 0.1f}; 
 
void display() { 
    glClearColor(bg[0], bg[1], bg[2], 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT); 
    glFlush(); 
} 
 
void mouseEntryDetector(int state) { 
    if (state == GLUT_LEFT) { 
        cout << "Mouse has left the application " << endl; 
        bg[0] = 0.5f; bg[1] = 0.1f; bg[2] = 0.1f;  // reddish 
    } else { 
        cout << "Mouse has re-entered the application " << 
endl; 
        bg[0] = 0.1f; bg[1] = 0.4f; bg[2] = 0.1f;  // greenish 
} 
    glutPostRedisplay(); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 400); 
    glutCreateWindow("Ex12 - Mouse Enter/Leave Changes Background"); 
    glutDisplayFunc(display); 
    glutEntryFunc(mouseEntryDetector); 
    glutMainLoop(); 
    return 0; 
} 