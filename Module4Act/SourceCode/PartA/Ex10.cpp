#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 10 - glDrawElements(): Reusing Shared Vertices
 * ------------------------------------------------------------
 * Concept: The real payoff of indexed rendering. A quad built from two
 * triangles normally needs 6 vertices with glDrawArrays (2 of them
 * duplicated). With glDrawElements, only the 4 UNIQUE corner
 * positions are stored once, and the index array tells OpenGL how to
 * reuse them to form both triangles - saving memory.
 */

void quadFromTriangles() {
    // Only 4 UNIQUE vertices needed, not 6 
    GLfloat quadVertex[] = {
        -0.5f, -0.5f, 0.0f,  // 0: bottom-left 
         0.5f, -0.5f, 0.0f,  // 1: bottom-right 
         0.5f,  0.5f, 0.0f,  // 2: top-right 
        -0.5f,  0.5f, 0.0f   // 3: top-left 
    };

    // Triangle 1: 0,1,2   Triangle 2: 0,2,3  (vertices 0 and 2 are SHARED) 
    GLubyte indices[] = { 0, 1, 2, 0, 2, 3 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, quadVertex);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.9f, 0.5f, 0.1f);
    quadFromTriangles();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex10 - glDrawElements Shared Vertices");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}