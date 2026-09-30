#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;
 
/*
* Example 08 - OpenGL Data Type Suffixes in Practice
* ------------------------------------------------------------
* Concept: glVertexPointer's "type" parameter is not limited to
* GL_FLOAT. This example stores vertex coordinates as GLshort (16-bit
* integer) instead of GLfloat, matching the "s" suffix from the OpenGL
* data type table, to show the array-based pipeline works with several
* underlying C types as long as `type` matches the array's declared type.
*/
 
void trianglesShort() {
    GLshort triangleVertex[] = {
        0, 75,
        -75, 0,
        75, 0
    };
 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_SHORT, 0, triangleVertex);   // note: GL_SHORT, not GL_FLOAT
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);
}
 
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.9f, 0.2f, 0.6f);
 
    // GLshort coordinates above are scaled to fit within (-1,1) via glScalef
    glPushMatrix();
    glScalef(0.01f, 0.01f, 1.0f);
    trianglesShort();
    glPopMatrix();
 
    glFlush();
}
 
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex08 - GLshort Vertex Data Type");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
 