#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 19 - Smoothly Shaded Quad Using a Color Array
 * ------------------------------------------------------------
 * Concept: Four vertices, four different colors, one color array -
 * OpenGL interpolates all four across the quad's interior, exactly as
 * it would with four separate glColor3f calls inside glBegin/glEnd.
 */

void shadedQuad() {
    GLfloat vertices[] = {
        -0.6f, -0.6f, 0.0f,
         0.6f, -0.6f, 0.0f,
         0.6f,  0.6f, 0.0f,
        -0.6f,  0.6f, 0.0f
    };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    shadedQuad();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex19 - Smoothly Shaded Quad (Color Array)");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}