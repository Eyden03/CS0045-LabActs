
#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

/*
 * Exercise Q17 - Procedural 30-Dash Ring in One VBO
  --------------------------------------------------
 Objective: Practice generating multiple line segments using one VBO.
 This program creates 30 short pink dashes arranged in a ring
 using sinf and cosf, then draws them with one glDrawArrays call.
 */

const int DASH_COUNT = 30;
GLuint VBOid;

void ring() {
    GLfloat verts[DASH_COUNT * 2 * 3];

    const float PI = 3.14159265f;
    const float innerRadius = 0.55f;
    const float outerRadius = 0.65f;

    for (int i = 0; i < DASH_COUNT; i++) {
        float angle = (i * 360.0f / DASH_COUNT) * PI / 180.0f;
        int b = i * 6;

        // Inner point
        verts[b + 0] = innerRadius * cosf(angle);
        verts[b + 1] = innerRadius * sinf(angle);
        verts[b + 2] = 0.0f;

        // Outer point
        verts[b + 3] = outerRadius * cosf(angle);
        verts[b + 4] = outerRadius * sinf(angle);
        verts[b + 5] = 0.0f;
    }

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glLineWidth(4.0f);
    glDrawArrays(GL_LINES, 0, DASH_COUNT * 2);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBOid);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.45f, 0.7f);  // Soft pink
    ring();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q17 - Procedural 30-Dash Ring");

    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        glutMainLoop();
    }
#else
    glutMainLoop();
#endif

    return 0;
}
