
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
 * Exercise Q19 - Keyboard-Triggered Color Change via glMapBuffer
  --------------------------------------------------------------
 Objective: Practice changing VBO colors using keyboard input.
 This program draws a colored triangle and changes its vertex
 colors whenever C is pressed by updating the color VBO.
 */

GLuint posVBO, colorVBO;
int colorScheme = 0;

void buildTriangle() {
    GLfloat positions[] = {
         0.0f,  0.75f, 0.0f,  // Top
        -0.75f, -0.5f, 0.0f,  // Bottom left
         0.75f, -0.5f, 0.0f   // Bottom right
    };

    GLfloat colors[] = {
        1.0f, 0.4f, 0.7f,  // Pink
        0.4f, 0.9f, 0.8f,  // Turquoise
        1.0f, 0.8f, 0.4f   // Yellow
    };

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions),
                 positions, GL_STATIC_DRAW);

    glGenBuffers(1, &colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors),
                 colors, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void coloredTriangle() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    coloredTriangle();
    glFlush();
}

void monitorKeyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        colorScheme = (colorScheme + 1) % 3;

        GLfloat newColors[9];

        if (colorScheme == 0) {
            GLfloat colors[] = {
                1.0f, 0.4f, 0.7f,  // Pink
                0.4f, 0.9f, 0.8f,  // Turquoise
                1.0f, 0.8f, 0.4f   // Yellow
            };
            for (int i = 0; i < 9; i++) newColors[i] = colors[i];
        }
        else if (colorScheme == 1) {
            GLfloat colors[] = {
                0.65f, 0.4f, 1.0f, // Violet
                1.0f, 0.4f, 0.6f,  // Pink
                0.4f, 0.7f, 1.0f   // Blue
            };
            for (int i = 0; i < 9; i++) newColors[i] = colors[i];
        }
        else {
            GLfloat colors[] = {
                1.0f, 0.9f, 0.4f,  // Yellow
                0.6f, 1.0f, 0.6f,  // Green
                1.0f, 0.6f, 0.4f   // Orange
            };
            for (int i = 0; i < 9; i++) newColors[i] = colors[i];
        }

        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        GLfloat* mapped = (GLfloat*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

        if (mapped != nullptr) {
            for (int i = 0; i < 9; i++) {
                mapped[i] = newColors[i];
            }
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glutPostRedisplay();
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Q19 - Keyboard Color Change");

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        buildTriangle();
        glutMainLoop();
    }
#else
    buildTriangle();
    glutMainLoop();
#endif

    return 0;
}
