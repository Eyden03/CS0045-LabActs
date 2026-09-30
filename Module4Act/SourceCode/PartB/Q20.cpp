#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

const int petals = 8;
const int segments = 24;

GLfloat petalVertices[petals * 9];
GLfloat petalColors[petals * 9];

GLfloat centerVertices[(segments + 2) * 3];
GLubyte centerIndices[segments + 2];

GLfloat groundVertices[] = {
    -0.95f, -0.75f, 0.0f,
     0.95f, -0.75f, 0.0f,
     0.95f, -0.95f, 0.0f,
    -0.95f, -0.95f, 0.0f
};

/*
 Exercise Q20 - Procedural Flower Scene
 ---------------------------------------
 Objective: Practice combining procedural generation, arrays, and indexing.
 */

void createFlower()
{
    const float PI = 3.14159f;

    GLfloat petalPalette[petals][3] = {
        { 1.0f, 0.25f, 0.35f },
        { 1.0f, 0.55f, 0.15f },
        { 1.0f, 0.85f, 0.15f },
        { 0.35f, 0.85f, 0.30f },
        { 0.20f, 0.75f, 0.95f },
        { 0.30f, 0.40f, 1.0f },
        { 0.70f, 0.30f, 1.0f },
        { 0.95f, 0.30f, 0.70f }
    };

    for (int i = 0; i < petals; i++)
    {
        float angle = (2.0f * PI * i) / petals;
        float leftAngle = angle - 0.22f;
        float rightAngle = angle + 0.22f;
        int vertexIndex = i * 9;

        petalVertices[vertexIndex] = 0.0f;
        petalVertices[vertexIndex + 1] = 0.0f;
        petalVertices[vertexIndex + 2] = 0.0f;

        petalVertices[vertexIndex + 3] = 0.82f * cos(leftAngle);
        petalVertices[vertexIndex + 4] = 0.82f * sin(leftAngle);
        petalVertices[vertexIndex + 5] = 0.0f;

        petalVertices[vertexIndex + 6] = 0.82f * cos(rightAngle);
        petalVertices[vertexIndex + 7] = 0.82f * sin(rightAngle);
        petalVertices[vertexIndex + 8] = 0.0f;

        for (int j = 0; j < 3; j++)
        {
            petalColors[vertexIndex + j * 3] = petalPalette[i][0];
            petalColors[vertexIndex + j * 3 + 1] = petalPalette[i][1];
            petalColors[vertexIndex + j * 3 + 2] = petalPalette[i][2];
        }
    }

    centerVertices[0] = 0.0f;
    centerVertices[1] = 0.0f;
    centerVertices[2] = 0.0f;

    centerIndices[0] = 0;

    for (int i = 0; i <= segments; i++)
    {
        float angle = (2.0f * PI * i) / segments;
        int vertexIndex = (i + 1) * 3;

        centerVertices[vertexIndex] = 0.25f * cos(angle);
        centerVertices[vertexIndex + 1] = 0.25f * sin(angle);
        centerVertices[vertexIndex + 2] = 0.0f;

        centerIndices[i + 1] = i + 1;
    }
}

void ground()
{
    glColor3f(0.20f, 0.65f, 0.30f); // green

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, groundVertices);
    glDrawArrays(GL_QUADS, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void flowerPetals()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, petalVertices);
    glColorPointer(3, GL_FLOAT, 0, petalColors);

    glDrawArrays(GL_TRIANGLES, 0, petals * 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void flowerCenter()
{
    glColor3f(1.0f, 0.80f, 0.10f); // yellow

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, centerVertices);
    glDrawElements(GL_TRIANGLE_FAN, segments + 2,
        GL_UNSIGNED_BYTE, centerIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    ground();
    flowerPetals();
    flowerCenter();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Q20 - Procedural Flower Scene");
    glutDisplayFunc(display);

    createFlower();

    glutMainLoop();

    return 0;
}