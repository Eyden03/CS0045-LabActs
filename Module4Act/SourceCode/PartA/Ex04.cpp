#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 04 - GL_LINES Drawn From a Vertex Array
 * ------------------------------------------------------------
 * Concept: A two-vertex array rendered with GL_LINES via the vertex
 * array pipeline.
 */

void line() {
    GLfloat lineVertex[] = {
        -0.8f, 0.0f, 0.0f,
         0.8f, 0.0f, 0.0f
    };
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, lineVertex);
    glLineWidth(4.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);
    line();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex04 - Vertex Array Line");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}