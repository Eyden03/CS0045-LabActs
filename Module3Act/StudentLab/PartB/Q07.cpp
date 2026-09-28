#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
using namespace std;

/*
 Exercise Q07 - Stroke Font Practice
 ------------------------------------
 Objective: Practice using glutStrokeCharacter with
 glTranslatef and glScalef.

 This program draws the letters "HI" using the
 GLUT_STROKE_ROMAN vector font.
 */

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.35f, 0.90f, 0.85f); // turquoise
    glLineWidth(4.0f); // thicker stroke

    glPushMatrix();
        glTranslatef(-0.30f, -0.18f, 0.0f); // center the text
        glScalef(0.003f, 0.003f, 1.0f); // scale down stroke font

        const char* text = "HI";

        for (const char* c = text; *c != '\0'; c++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
        }
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Q07 - Stroke Font Practice");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}