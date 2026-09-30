#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std; 
  
/* 
 * Example 20 - Capstone: An Efficient Composite Scene 
 * ------------------------------------------------------------ 
 * Concept: Combines everything from this module into one program: 
 *   - A star-like GL_TRIANGLE_FAN built with glDrawElements, sharing 
 *     one center vertex across all its slices (indexed rendering). 
 *   - A colored quad rendered with a combined vertex array + color 
 *     array in a single glDrawArrays call. 
 *   - A plain ground rectangle rendered from its own small vertex array. 
 * Every shape in the scene is drawn from array data - there is not a 
 * single glVertex2f call left in this program. 
 */ 
  
 // ---- Star (triangle fan sharing a center vertex) ----
GLfloat starVertices[] = { 
    0.0f, 0.35f, 0.0f,      // 0: shared center 
    0.0f, 0.75f, 0.0f,      // 1 
    0.15f, 0.45f, 0.0f,     // 2 
    0.5f, 0.45f, 0.0f,      // 3 
    0.2f, 0.25f, 0.0f,      // 4 
    0.3f, -0.05f, 0.0f,     // 5 
    0.0f, 0.15f, 0.0f,      // 6 
    -0.3f, -0.05f, 0.0f,    // 7 
    -0.2f, 0.25f, 0.0f,     // 8 
    -0.5f, 0.45f, 0.0f,     // 9 
    -0.15f, 0.45f, 0.0f,    // 10 
    0.0f, 0.75f, 0.0f       // 11 (repeat of vertex 1 to close the fan) 
}; 
  
GLubyte starIndices[] = { 0,1,2,3,4,5,6,7,8,9,10,11 }; 
  
// ---- Colored quad ---- 
GLfloat quadVertices[] = { 
    -0.8f, -0.55f, 0.0f, 
    -0.3f, -0.55f, 0.0f, 
    -0.3f, -0.15f, 0.0f, 
    -0.8f, -0.15f, 0.0f 
}; 
GLfloat quadColors[] = { 
    1.0f, 0.4f, 0.0f, 
    0.0f, 0.8f, 1.0f, 
    0.6f, 0.0f, 1.0f, 
    1.0f, 1.0f, 0.0f 
}; 
  
// ---- Ground rectangle ---- 
GLfloat groundVertices[] = { 
    -0.9f, -0.8f, 0.0f, 
     0.9f, -0.8f, 0.0f, 
     0.9f, -0.95f, 0.0f, 
    -0.9f, -0.95f, 0.0f 
}; 
  
void star() { 
    glColor3f(1.0f, 0.85f, 0.1f); 
    glEnableClientState(GL_VERTEX_ARRAY); 
    glVertexPointer(3, GL_FLOAT, 0, starVertices); 
    glDrawElements(GL_TRIANGLE_FAN, 12, GL_UNSIGNED_BYTE, starIndices); 
    glDisableClientState(GL_VERTEX_ARRAY); 
} 
  
void coloredQuad() { 
    glEnableClientState(GL_VERTEX_ARRAY); 
    glEnableClientState(GL_COLOR_ARRAY); 
    glVertexPointer(3, GL_FLOAT, 0, quadVertices); 
    glColorPointer(3, GL_FLOAT, 0, quadColors); 
 glDrawArrays(GL_QUADS, 0, 4); 
    glDisableClientState(GL_VERTEX_ARRAY); 
    glDisableClientState(GL_COLOR_ARRAY); 
} 
  
void ground() { 
    glColor3f(0.25f, 0.6f, 0.25f); 
    glEnableClientState(GL_VERTEX_ARRAY); 
    glVertexPointer(3, GL_FLOAT, 0, groundVertices); 
    glDrawArrays(GL_QUADS, 0, 4); 
    glDisableClientState(GL_VERTEX_ARRAY); 
} 
  
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    star(); 
    coloredQuad(); 
    ground(); 
    glFlush(); 
} 
  
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(800, 600); 
    glutCreateWindow("Ex20 - Capstone: Efficient Array-Based Scene"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
} 