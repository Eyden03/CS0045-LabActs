
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
 * Exercise Q16 - Three-Shape VBO Scene: Sun, Indexed Ground, Tree
  ---------------------------------------------------------------
 Objective: Practice drawing multiple shapes using separate VBOs.
 This program draws a sun, an indexed ground, and a tree using
 glDrawArrays and glDrawElements with GPU-stored vertex data.
 */

GLuint sunVBO, groundVBO, groundIndexVBO;
GLuint trunkVBO, leavesVBO;

void initSun() {
    GLfloat sunVertices[] = {
         0.65f, 0.65f, 0.0f,  // Center
         0.65f, 0.83f, 0.0f,  // Top
         0.82f, 0.72f, 0.0f,
         0.76f, 0.51f, 0.0f,
         0.54f, 0.51f, 0.0f,
         0.48f, 0.72f, 0.0f,
         0.65f, 0.83f, 0.0f   // Close the fan
    };

    glGenBuffers(1, &sunVBO);
    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sunVertices),
                 sunVertices, GL_STATIC_DRAW);
}

void initGround() {
    GLfloat groundVertices[] = {
        -0.9f, -0.9f, 0.0f,  // Bottom left
         0.9f, -0.9f, 0.0f,  // Bottom right
         0.9f, -0.5f, 0.0f,  // Top right
        -0.9f, -0.5f, 0.0f   // Top left
    };

    GLubyte indices[] = { 0, 1, 2, 0, 2, 3 };

    glGenBuffers(1, &groundVBO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices),
                 groundVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &groundIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
                 indices, GL_STATIC_DRAW);
}

void initTree() {
    GLfloat trunkVertices[] = {
        -0.58f, -0.5f, 0.0f,  // Bottom left
        -0.42f, -0.5f, 0.0f,  // Bottom right
        -0.42f, -0.1f, 0.0f,  // Top right
        -0.58f, -0.1f, 0.0f   // Top left
    };

    GLfloat leavesVertices[] = {
        -0.5f,  0.55f, 0.0f,  // Top
        -0.85f, -0.15f, 0.0f, // Bottom left
        -0.15f, -0.15f, 0.0f  // Bottom right
    };

    glGenBuffers(1, &trunkVBO);
    glBindBuffer(GL_ARRAY_BUFFER, trunkVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(trunkVertices),
                 trunkVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &leavesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, leavesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(leavesVertices),
                 leavesVertices, GL_STATIC_DRAW);
}

void sun() {
    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(1.0f, 0.75f, 0.25f);  // Golden yellow
    glDrawArrays(GL_TRIANGLE_FAN, 0, 7);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ground() {
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, groundIndexVBO);

    glColor3f(0.15f, 0.65f, 0.55f);  // Teal
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void tree() {
    glBindBuffer(GL_ARRAY_BUFFER, trunkVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.65f, 0.4f, 0.3f);  // Brown trunk
    glDrawArrays(GL_QUADS, 0, 4);

    glBindBuffer(GL_ARRAY_BUFFER, leavesVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.55f, 0.8f, 0.45f);  // Sage green leaves
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    ground();
    tree();
    sun();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q16 - Three-Shape VBO Scene");

    glutDisplayFunc(display);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        initSun();
        initGround();
        initTree();
        glutMainLoop();
    }
#else
    initSun();
    initGround();
    initTree();
    glutMainLoop();
#endif

    return 0;
}
