#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 18 - glDrawElements() Across Multiple Shapes
 * ------------------------------------------------------------
 * Concept: A single unique-vertex pool feeding TWO separate indexed
 * draws - a triangle pair (quad) built with one index list, and a
 * standalone triangle built from three OTHER vertices in the same
 * pool, using a second glDrawElements call.
 */

GLfloat pool[] = {
    -0.9f, -0.5f, 0.0f,  // 0 
    -0.3f, -0.5f, 0.0f,  // 1 
    -0.3f,  0.5f, 0.0f,  // 2 
    -0.9f,  0.5f, 0.0f,  // 3 
     0.3f, -0.5f, 0.0f,  // 4 
     0.9f, -0.5f, 0.0f,  // 5 
     0.6f,  0.5f, 0.0f   // 6 
};

GLubyte quadIndices[] = { 0, 1, 2, 0, 2, 3 };
GLubyte triIndices[] = { 4, 5, 6 };

void drawShapes() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, pool);

    glColor3f(0.9f, 0.6f, 0.1f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, quadIndices);

    glColor3f(0.1f, 0.6f, 0.9f);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triIndices);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawShapes();
    glFlush();
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(700, 400);
    glutCreateWindow("Ex18 - glDrawElements, Multiple Shapes");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}