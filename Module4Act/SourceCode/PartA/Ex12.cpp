#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 12 - Gradient Line Using a Color Array
 * ------------------------------------------------------------
 * Concept: Per-vertex colors from a color array interpolate smoothly
 *
 * across a primitive, exactly like per-vertex glColor3f calls inside
 * glBegin/glEnd - only now the colors come from an array.
 */

void gradientLine() {
    GLfloat vertices[] = {
        -0.8f, 0.0f, 0.0f,
         0.8f, 0.0f, 0.0f
    };
    GLfloat colors[] = {
        1.0f, 1.0f, 0.0f,   // yellow 
        0.6f, 0.0f, 0.8f    // purple 
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glLineWidth(6.0f);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    gradientLine();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex12 - Gradient Line via Color Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}