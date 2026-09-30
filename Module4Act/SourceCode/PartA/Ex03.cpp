#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 03 - GL_POINTS Drawn From a Vertex Array
 * ------------------------------------------------------------
 * Concept: Applying the same 5-step vertex array pattern to GL_POINTS
 * instead of GL_TRIANGLES - only the array contents and glDrawArrays
 * mode change.
 */

void points() {
    glPointSize(20.0f);

    GLfloat pointVertex[] = {
        -0.75f, -0.75f, 0.0f,
        -0.75f,  0.75f, 0.0f,
         0.75f,  0.75f, 0.0f,
         0.75f, -0.75f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pointVertex);
    glDrawArrays(GL_POINTS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    points();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex03 - Vertex Array Points");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}