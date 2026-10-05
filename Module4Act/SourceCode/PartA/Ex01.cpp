#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std; 
/*
* Example 01 - Immediate Mode Baseline (Before Conversion)
*
* Concept: A plain glBegin()/glEnd() triangle, drawn in "immediate mode"
* (one glVertex2f call issued at a time). This is the STARTING POINT that
* Example 02 converts into a vertex array, so you can compare both
* approaches side by side.
*/

void triangle() { 
  glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.75f); 
    glVertex2f(-0.75f, 0.0f); 
    glVertex2f(0.75f, 0.0f);
  glEnd();
}

void display() { 
  glClear(GL_COLOR_BUFFER_BIT); 
  glColor3f(0.16f, 0.72f, 0.08f); 
  triangle();
glFlush();
}

int main(int argc, char** argv) { 
  glutInit(&argc, argv); 
  glutInitWindowSize(600, 500);
  glutCreateWindow("Ex01 - Immediate Mode Triangle"); 
  glutDisplayFunc(display);
glutMainLoop(); return 0;
}
 
