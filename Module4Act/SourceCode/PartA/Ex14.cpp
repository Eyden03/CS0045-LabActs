#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 14 - Full Scene: Pinwheel + Rectangle (Two Draw Calls)
 * ------------------------------------------------------------
 * Concept: A complete scene composed of TWO separate vertex-array draw
 * calls: the colored pinwheel (vertex array + color array), and a
 * solid green rectangle underneath (vertex array only, flat color).
 * Mirrors the lecture's final combined sample program.
 */

GLfloat triangleVertices[] = {
    0.0f, 0.0f, 0.0f,    -0.5f, 0.10f, 0.0f,   -0.5f, -0.10f, 0.0f,
    0.0f, 0.0f, 0.0f,     0.5f, 0.10f, 0.0f,    0.5f, -0.10f, 0.0f,
    0.0f, 0.0f, 0.0f,    -0.10f, 0.50f, 0.0f,   0.10f,  0.50f, 0.0f,
    0.0f, 0.0f, 0.0f,    -0.10f, -0.50f, 0.0f,  0.10f, -0.50f, 0.0f
};

GLfloat triangleColors[] = {
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f,
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f,
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f,
    1.0f,0.0f,0.0f,  0.0f,1.0f,0.0f,  0.0f,0.0f,1.0f
};

GLfloat quadVertices[] = {
    -0.5f, -0.7f, 0.0f,
     0.5f, -0.7f, 0.0f,
     0.5f, -0.9f, 0.0f,
    -0.5f, -0.9f, 0.0f
};

void pinwheel() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
    glColorPointer(3, GL_FLOAT, 0, triangleColors);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void rectangle() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, quadVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    pinwheel();
    rectangle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(200, 50);
    glutCreateWindow("My First OpenGL");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}