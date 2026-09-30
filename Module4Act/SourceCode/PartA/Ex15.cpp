#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream>

using namespace std;

/*
 * Example 15 - Indexed Pinwheel: Sharing the Center Vertex
 * ------------------------------------------------------------
 * Concept: All four pinwheel triangles share the exact same center
 * point (0,0,0). Using glDrawElements, that shared vertex only needs
 * to be stored ONCE, and every triangle's index list simply points
 * back to it - reducing the unique vertex count from 12 to 9.
 */

GLfloat pinwheelVertices[] = {
    0.0f, 0.0f, 0.0f,       // 0: shared center 
    -0.5f, 0.10f, 0.0f,     // 1: left-top 
    -0.5f, -0.10f, 0.0f,    // 2: left-bottom 
     0.5f, 0.10f, 0.0f,     // 3: right-top 
     0.5f, -0.10f, 0.0f,    // 4: right-bottom 
    -0.10f, 0.50f, 0.0f,    // 5: up-left 
     0.10f, 0.50f, 0.0f,    // 6: up-right 
    -0.10f, -0.50f, 0.0f,   // 7: down-left 
     0.10f, -0.50f, 0.0f    // 8: down-right 
};

GLfloat pinwheelColors[] = {
    1.0f, 1.0f, 1.0f,   // center - white 
    1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // left triangle outer colors 
    0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,   // right triangle outer colors 
    1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // up triangle outer colors 
    1.0f, 0.5f, 0.0f, 0.5f, 0.0f, 1.0f    // down triangle outer colors 
};

GLubyte pinwheelIndices[] = {
    0, 1, 2,   // left triangle (reuses shared center = index 0) 
    0, 3, 4,   // right triangle 
    0, 5, 6,   // up triangle 
    0, 7, 8    // down triangle 
};

void indexedPinwheel() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pinwheelVertices);
    glColorPointer(3, GL_FLOAT, 0, pinwheelColors);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, pinwheelIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    indexedPinwheel();
    glFlush();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex15 - Indexed Pinwheel (Shared Center)");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}