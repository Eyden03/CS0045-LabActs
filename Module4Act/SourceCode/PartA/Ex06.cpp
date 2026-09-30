#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 06 - GL_POLYGON Drawn From a Vertex Array
 * ------------------------------------------------------------
 * Concept: A five-sided convex polygon (pentagon), built from a vertex
 * array and rendered with GL_POLYGON, using ALL specified vertices.
 */

void pentagon() {
    GLfloat pentagonVertex[] = {
           0.0f,  0.75f, 0.0f,
          -0.71f, 0.23f, 0.0f,
          -0.44f, -0.61f, 0.0f,
           0.44f, -0.61f, 0.0f,
           0.71f, 0.23f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pentagonVertex);
    glDrawArrays(GL_POLYGON, 0, 5);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.6f, 0.0f);
    pentagon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex06 - Vertex Array Polygon");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}