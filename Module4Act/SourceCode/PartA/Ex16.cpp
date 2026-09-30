#define GL_SILENCE_DEPRECATION 
#ifdef __APPLE__ 
#include <GLUT/glut.h> 
#else 
#include <GL/glut.h> 
#endif 
#include <iostream> 
using namespace std;

/*
 * Example 16 - Interleaved Arrays and the "stride" Parameter
 * ------------------------------------------------------------
 * Concept: So far, position and color have lived in SEPARATE arrays
 * (stride 0 = tightly packed, one array's own data only). Here they
 * are INTERLEAVED into a single array as [x,y,z,r,g,b, x,y,z,r,g,b,...]
 * and glVertexPointer/glColorPointer use a non-zero stride (the byte
 * offset to the NEXT vertex's data) plus a starting offset pointer to
 * read their own fields out of the same combined array.
 */

void interleavedTriangle() {
    // Each vertex: 3 position floats followed by 3 color floats 
    GLfloat data[] = {
        // x,     y,     z,     r,    g,    b 
        0.0f,  0.75f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.75f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.75f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    GLsizei stride = 6 * sizeof(GLfloat);   // bytes from one vertex to the next

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, stride, data);           // position starts at offset 0 
    glColorPointer(3, GL_FLOAT, stride, data + 3);         // color starts 3 floats in 

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    interleavedTriangle();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Ex16 - Interleaved Array with Stride");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}