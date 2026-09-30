#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

/*
* Example 02 - Same Triangle, Converted to a Vertex Array
* ------------------------------------------------------------
* Concept: The 5-step vertex array pattern:
*   1. Store the vertex coordinates in a plain array (GLfloat[]).
*   2. glEnableClientState(GL_VERTEX_ARRAY) - tell OpenGL a vertex array
*      will be used.
*   3. glVertexPointer(size, type, stride, pointer) - tell OpenGL WHERE
*      the data lives and how it's laid out.
*   4. glDrawArrays(mode, first, count) - draw using the array data.
*   5. glDisableClientState(GL_VERTEX_ARRAY) - turn the feature back off.
*/

void triangle() {
    // 1. initialize an array holding vertex coordinates
    GLfloat triangleVertex[] = {
        0.0f, 0.75f, 0.0f,   // z is always 0.0 for 2D primitives
        -0.75f, 0.0f, 0.0f,
        0.75f, 0.0f, 0.0f
    };

    // 2. activate the vertex array feature
    glEnableClientState(GL_VERTEX_ARRAY);

    // 3. tell OpenGL where the vertex data is
    glVertexPointer(3, GL_FLOAT, 0, triangleVertex);

    // 4. draw using the array
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // 5. deactivate the vertex array feature
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.16f, 0.72f, 0.08f);
    triangle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex02 - Vertex Array Triangle");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}