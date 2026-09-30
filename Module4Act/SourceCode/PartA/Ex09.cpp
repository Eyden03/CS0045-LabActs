#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 09 - glDrawElements(): Indexed Rendering
 * ------------------------------------------------------------
 * Concept: Instead of glDrawArrays() walking the vertex array in
 * order, glDrawElements() reads a separate INDEX array telling it
 * which vertices to use, and in what order. Here the index array
 * simply selects vertices 0,1,2 - equivalent to Example 02, but using
 * the indexed drawing path.
 */

void triangle() {
    GLfloat triangleVertex[] = {
        0.0f, 0.75f, 0.0f,
        -0.75f, 0.0f, 0.0f,
        0.75f, 0.0f, 0.0f
    };
    GLubyte indices[] = { 0, 1, 2 };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleVertex);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);
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
    glutCreateWindow("Ex09 - glDrawElements Basic");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}