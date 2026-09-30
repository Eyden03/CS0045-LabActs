#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h>

#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 13 - Four-Triangle Pinwheel, One Array, One Draw Call
 * ------------------------------------------------------------
 * Concept: Recreates the lecture's colored pinwheel (left/right/up/
 * down triangles, each fading red->green->blue) using a SINGLE vertex
 * array + SINGLE color array + ONE glDrawArrays(GL_TRIANGLES, 0, 12)
 * call, instead of four separate immediate-mode glBegin/glEnd blocks.
 */

GLfloat triangleVertices[] = {
    0.0f, 0.0f, 0.0f,    -0.5f, 0.10f, 0.0f,   -0.5f, -0.10f, 0.0f,   // left 
    0.0f, 0.0f, 0.0f,     0.5f, 0.10f, 0.0f,    0.5f, -0.10f, 0.0f,   // right 
    0.0f, 0.0f, 0.0f,    -0.10f, 0.50f, 0.0f,   0.10f,  0.50f, 0.0f,  // up 
    0.0f, 0.0f, 0.0f,    -0.10f, -0.50f, 0.0f,  0.10f, -0.50f, 0.0f   // down 
};

GLfloat triangleColors[] = {
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f,
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f,
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f,
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f
};

void pinwheel() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
    glColorPointer(3, GL_FLOAT, 0, triangleColors);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    pinwheel();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex13 - Pinwheel: One Array, One Draw Call");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;

}