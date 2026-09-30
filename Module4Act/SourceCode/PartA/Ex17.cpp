#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std; 
  
/* 
 * Example 17 - One Big Array, Multiple glDrawArrays "first" Offsets 
 * ------------------------------------------------------------ 
 * Concept: A single vertex array can be reused across SEVERAL 
 * glDrawArrays calls, each reading a different slice via the "first" 
 * parameter - here, drawing three separate triangles stored back to
* back in one array, one glDrawArrays call per triangle, each with a 
 * different color and a different "first" starting index. 
 */ 
  
GLfloat rowVertices[] = { 
    -0.9f, -0.3f, 0.0f,  -0.7f, 0.3f, 0.0f,  -0.5f, -0.3f, 0.0f,   // triangle 0 (indices 0-2) 
    -0.15f, -0.3f, 0.0f,  0.05f, 0.3f, 0.0f,  0.25f, -0.3f, 0.0f,  // triangle 1 (indices 3-5) 
     0.5f, -0.3f, 0.0f,   0.7f, 0.3f, 0.0f,   0.9f, -0.3f, 0.0f    // triangle 2 (indices 6-8) 
}; 
  
void drawRow() { 
    glEnableClientState(GL_VERTEX_ARRAY); 
    glVertexPointer(3, GL_FLOAT, 0, rowVertices); 
  
    glColor3f(1.0f, 0.2f, 0.2f); 
    glDrawArrays(GL_TRIANGLES, 0, 3);   // first = 0 
  
    glColor3f(0.2f, 1.0f, 0.2f); 
    glDrawArrays(GL_TRIANGLES, 3, 3);   // first = 3 
  
    glColor3f(0.2f, 0.4f, 1.0f); 
    glDrawArrays(GL_TRIANGLES, 6, 3);   // first = 6 
  
    glDisableClientState(GL_VERTEX_ARRAY); 
} 
  
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    drawRow(); 
    glFlush(); 
} 
  
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(700, 400); 
    glutCreateWindow("Ex17 - One Array, Multiple Draw Calls"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
} 