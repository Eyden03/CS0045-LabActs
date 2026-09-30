#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 07 - Two Triangles From ONE Array, ONE Draw Call
 * ------------------------------------------------------------
 * Concept: Extending the vertex array with MORE vertices lets a single
 * glDrawArrays() call render multiple separate primitives at once -
 * here, two independent triangles (6 vertices, GL_TRIANGLES groups
 * them 3 at a time).
 */

void triangles() {
    GLfloat triangleVertex[] = {
        // triangle 1 (upper) 
        0.0f, 0.75f, 0.0f,
        -0.75f, 0.15f, 0.0f,
        0.75f, 0.15f, 0.0f,

        // triangle 2 (lower) - additional vertices for the 2nd triangle 
        0.0f, -0.15f, 0.0f,
        -0.75f, -0.75f, 0.0f,
        0.75f, -0.75f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleVertex);
    glDrawArrays(GL_TRIANGLES, 0, 6);   // 6 vertices to be rendered 
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2f, 0.8f, 0.3f);
    triangles();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex07 - Multiple Primitives, One Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}