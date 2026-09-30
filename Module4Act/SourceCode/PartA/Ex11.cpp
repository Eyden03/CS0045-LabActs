#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 11 - Combining a Vertex Array With a Color Array
 * ------------------------------------------------------------
 * Concept: glColorPointer works exactly like glVertexPointer, but
 * feeds per-vertex COLOR data instead of position data. Both arrays
 * are enabled and bound together, so glDrawArrays picks up matching
 * position[i] / color[i] pairs automatically.
 */

void triangle() {
    GLfloat vertices[] = {
        0.0f, 0.75f, 0.0f,
        -0.75f, 0.0f, 0.0f,
        0.75f, 0.0f, 0.0f
    };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,   // red   - top vertex 
        0.0f, 1.0f, 0.0f,   // green - bottom-left vertex 
        0.0f, 0.0f, 1.0f    // blue  - bottom-right vertex 
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    triangle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex11 - Vertex Array + Color Array");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}