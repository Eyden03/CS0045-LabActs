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

// Park layout and decoration buffers.
GLuint parkVBO[2], parkIndexVBO;
GLuint decorationVBO, decorationIndexVBO;
GLuint circleVBO, triangleVBO;

// Current facility visibility and selected layout.
bool showPlayground = true;
bool showGarden = true;
bool showSeating = true;
int currentLayout = 0;

// Window dimensions and shared display text.
int windowWidth = 1280, windowHeight = 800;
const float PI = 3.14159265f;
const char* message = "Welcome to Nature Haven!";

/*
 * Machine Problem 02 - Nature Haven Community Park Planner
  ---------------------------------------------------------
 Objective: Create an interactive park layout using indexed VBOs.
 This program displays a nature-themed community park where users
 can toggle facilities and switch between two park layouts.
 */

 // Upload the two layouts and their shared rectangle indices.
void initPark() {
    // Park boundary, paths, and four activity areas
    GLfloat layoutA[] = {
        // Park boundary
        -0.95f,-0.95f,0.0f, // Bottom-left point
         0.95f,-0.95f,0.0f, // Bottom-right point
         0.95f, 0.95f,0.0f, // Top-right point
        -0.95f, 0.95f,0.0f, // Top-left point

        // Vertical walking path
        -0.10f,-0.90f,0.0f, // Bottom-left point
         0.10f,-0.90f,0.0f, // Bottom-right point
         0.10f, 0.90f,0.0f, // Top-right point
        -0.10f, 0.90f,0.0f, // Top-left point

        // Horizontal walking path
        -0.90f,-0.10f,0.0f, // Bottom-left point
         0.90f,-0.10f,0.0f, // Bottom-right point
         0.90f, 0.10f,0.0f, // Top-right point
        -0.90f, 0.10f,0.0f, // Top-left point

        // Playground - upper left
        -0.85f, 0.20f,0.0f, // Bottom-left point
        -0.20f, 0.20f,0.0f, // Bottom-right point
        -0.20f, 0.80f,0.0f, // Top-right point
        -0.85f, 0.80f,0.0f, // Top-left point

        // Garden - upper right
         0.20f, 0.20f,0.0f, // Bottom-left point
         0.85f, 0.20f,0.0f, // Bottom-right point
         0.85f, 0.80f,0.0f, // Top-right point
         0.20f, 0.80f,0.0f, // Top-left point

         // Skating area - lower left
         -0.85f,-0.80f,0.0f, // Bottom-left point
         -0.20f,-0.80f,0.0f, // Bottom-right point
         -0.20f,-0.20f,0.0f, // Top-right point
         -0.85f,-0.20f,0.0f, // Top-left point

         // Seating area - lower right
          0.20f,-0.80f,0.0f, // Bottom-left point
          0.85f,-0.80f,0.0f, // Bottom-right point
          0.85f,-0.20f,0.0f, // Top-right point
          0.20f,-0.20f,0.0f  // Top-left point

    };

    GLfloat layoutB[] = {
        // Park boundary
        -0.95f,-0.95f,0.0f, // Bottom-left point
         0.95f,-0.95f,0.0f, // Bottom-right point
         0.95f, 0.95f,0.0f, // Top-right point
        -0.95f, 0.95f,0.0f, // Top-left point

        // Vertical walking path
        -0.10f,-0.90f,0.0f, // Bottom-left point
         0.10f,-0.90f,0.0f, // Bottom-right point
         0.10f, 0.90f,0.0f, // Top-right point
        -0.10f, 0.90f,0.0f, // Top-left point

        // Horizontal walking path
        -0.90f,-0.10f,0.0f, // Bottom-left point
         0.90f,-0.10f,0.0f, // Bottom-right point
         0.90f, 0.10f,0.0f, // Top-right point
        -0.90f, 0.10f,0.0f, // Top-left point

        // Playground - lower right
         0.20f,-0.80f,0.0f, // Bottom-left point
         0.85f,-0.80f,0.0f, // Bottom-right point
         0.85f,-0.20f,0.0f, // Top-right point
         0.20f,-0.20f,0.0f, // Top-left point

         // Garden - lower left
         -0.85f,-0.80f,0.0f, // Bottom-left point
         -0.20f,-0.80f,0.0f, // Bottom-right point
         -0.20f,-0.20f,0.0f, // Top-right point
         -0.85f,-0.20f,0.0f, // Top-left point

         // Skating area - upper right
          0.20f, 0.20f,0.0f, // Bottom-left point
          0.85f, 0.20f,0.0f, // Bottom-right point
          0.85f, 0.80f,0.0f, // Top-right point
          0.20f, 0.80f,0.0f, // Top-left point

          // Seating area - upper left
          -0.85f, 0.20f,0.0f, // Bottom-left point
          -0.20f, 0.20f,0.0f, // Bottom-right point
          -0.20f, 0.80f,0.0f, // Top-right point
          -0.85f, 0.80f,0.0f  // Top-left point

    };

    // Two triangles for every rectangle; each pair shares two vertices
    GLubyte indices[] = {
         0, 1, 2,  0, 2, 3, // Park boundary
         4, 5, 6,  4, 6, 7, // Vertical walking path
         8, 9,10,  8,10,11, // Horizontal walking path
        12,13,14, 12,14,15, // Playground
        16,17,18, 16,18,19, // Garden
        20,21,22, 20,22,23, // Skating area
        24,25,26, 24,26,27 // Seating area
    };
    // Create and upload the two layout vertex buffers.
    glGenBuffers(2, parkVBO);
    glBindBuffer(GL_ARRAY_BUFFER, parkVBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(layoutA), layoutA, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, parkVBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(layoutB), layoutB, GL_STATIC_DRAW);

    // Create and upload the shared shape indices.
    glGenBuffers(1, &parkIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, parkIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Unbind buffers after setup.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Build reusable vertex buffers for drawing decorations.
void initDecorations() {
    GLfloat rectangle[] = {
        0.0f,0.0f,0.0f, // Bottom-left point
        1.0f,0.0f,0.0f, // Bottom-right point
        1.0f,1.0f,0.0f, // Top-right point
        0.0f,1.0f,0.0f  // Top-left point
    };

    GLubyte indices[] = { 0,1,2,0,2,3 };
    GLfloat triangle[] = {
        0.0f,0.0f,0.0f, // Bottom-left point
        1.0f,0.0f,0.0f, // Bottom-right point
        0.5f,1.0f,0.0f }; // Top point

    const int segments = 32;
    GLfloat circle[(segments + 2) * 3];
    circle[0] = 0.0f; circle[1] = 0.0f; circle[2] = 0.0f;
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        circle[(i + 1) * 3] = cosf(angle);
        circle[(i + 1) * 3 + 1] = sinf(angle);
        circle[(i + 1) * 3 + 2] = 0.0f;
    }

    // Rectangle vertex data
    glGenBuffers(1, &decorationVBO);
    glBindBuffer(GL_ARRAY_BUFFER, decorationVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    // Rectangle index data
    glGenBuffers(1, &decorationIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, decorationIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Circle vertex data
    glGenBuffers(1, &circleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

    // Triangle vertex data
    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    // Clear buffer bindings after setup
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Draw one indexed area from the active park layout.
void drawArea(int area, float r, float g, float b) {
    glBindBuffer(GL_ARRAY_BUFFER, parkVBO[currentLayout]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, parkIndexVBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(r, g, b);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE,
        (void*)(area * 6 * sizeof(GLubyte)));
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Primitive helpers used to compose the park scene.
void drawRectangle(float x, float y, float w, float h, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(w, h, 1.0f);

    glBindBuffer(GL_ARRAY_BUFFER, decorationVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, decorationIndexVBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(r, g, b);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopMatrix();
}

void drawCircle(float x, float y, float rx, float ry, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(rx, ry, 1.0f);

    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 34);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glPopMatrix();
}

void drawTriangle(float x, float y, float w, float h, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(w, h, 1.0f);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(r, g, b);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glPopMatrix();
}

void drawLine(float x1, float y1, float x2, float y2, float width, float r, float g, float b) {
    glColor3f(r, g, b);
    glLineWidth(width);

    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    glLineWidth(1.0f);
}

void drawBorder(float x, float y, float w, float h, float width, float r, float g, float b) {
    glColor3f(r, g, b);
    glLineWidth(width);

    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();

    glLineWidth(1.0f);
}

void drawText(float x, float y, const char* words, void* font = GLUT_BITMAP_HELVETICA_12) {
    glRasterPos2f(x, y);
    for (const char* p = words; *p != '\0'; p++) glutBitmapCharacter(font, *p);
}

// Small reusable park decorations.
void drawTree(float x, float y, float size) {
    drawRectangle(x - 0.009f * size, y - 0.035f * size, 0.018f * size, 0.055f * size, 0.47f, 0.29f, 0.15f); // Brown trunk
    drawCircle(x, y + 0.025f * size, 0.047f * size, 0.052f * size, 0.13f, 0.40f, 0.22f); // Dark leaves
    drawCircle(x - 0.013f * size, y + 0.042f * size, 0.028f * size, 0.030f * size, 0.26f, 0.60f, 0.31f); // Light leaves
}

void drawFlower(float x, float y, float size) {
    drawCircle(x, y, size * 1.9f, size * 1.9f, 0.97f, 0.62f, 0.72f); // Pink petals
    drawCircle(x, y, size, size, 0.98f, 0.84f, 0.29f); // Yellow center
}

void drawLamp(float x, float y) {
    drawRectangle(x - 0.007f, y - 0.035f, 0.014f, 0.070f, 0.20f, 0.25f, 0.23f);
    drawCircle(x, y + 0.045f, 0.025f, 0.025f, 1.00f, 0.88f, 0.48f);
    drawCircle(x, y + 0.045f, 0.013f, 0.013f, 1.00f, 0.97f, 0.76f);
}

// Return a facility's bottom-left position in the active layout.
void getAreaPosition(int area, float& x, float& y) {
    static const float positions[2][4][2] = { // Positions for each area in the two layouts
        { { -0.85f,0.20f },{ 0.20f,0.20f },{ -0.85f,-0.80f },{ 0.20f,-0.80f } },
        { { 0.20f,-0.80f },{ -0.85f,-0.80f },{ 0.20f,0.20f },{ -0.85f,0.20f } }
    };
    x = positions[currentLayout][area][0];
    y = positions[currentLayout][area][1];
}

// Facility illustrations, positioned according to the active layout.
void drawPlayground() {
    float x, y; getAreaPosition(0, x, y);
    drawBorder(x + 0.012f, y + 0.012f, 0.626f, 0.576f, 3.0f, 0.76f, 0.42f, 0.20f);
    drawRectangle(x + 0.20f, y + 0.515f, 0.25f, 0.055f, 0.76f, 0.42f, 0.20f);

    // Sandbox
    drawRectangle(x + 0.06f, y + 0.07f, 0.23f, 0.18f, 0.72f, 0.39f, 0.23f);
    drawRectangle(x + 0.075f, y + 0.085f, 0.20f, 0.15f, 0.96f, 0.85f, 0.56f);

    // Slide and ladder
    drawRectangle(x + 0.38f, y + 0.17f, 0.09f, 0.22f, 0.85f, 0.33f, 0.29f);
    drawTriangle(x + 0.34f, y + 0.35f, 0.17f, 0.16f, 0.98f, 0.73f, 0.25f);

    drawRectangle(x + 0.47f, y + 0.11f, 0.11f, 0.07f, 0.36f, 0.72f, 0.91f);
    drawLine(x + 0.395f, y + 0.20f, x + 0.455f, y + 0.20f, 2.0f, 0.96f, 0.90f, 0.70f);
    drawLine(x + 0.395f, y + 0.245f, x + 0.455f, y + 0.245f, 2.0f, 0.96f, 0.90f, 0.70f);
    drawLine(x + 0.395f, y + 0.29f, x + 0.455f, y + 0.29f, 2.0f, 0.96f, 0.90f, 0.70f);
    drawLine(x + 0.395f, y + 0.335f, x + 0.455f, y + 0.335f, 2.0f, 0.96f, 0.90f, 0.70f);

    // Swing frame and two seats
    drawRectangle(x + 0.07f, y + 0.42f, 0.26f, 0.025f, 0.23f, 0.44f, 0.67f);
    drawLine(x + 0.09f, y + 0.31f, x + 0.11f, y + 0.43f, 3.0f, 0.23f, 0.44f, 0.67f);
    drawLine(x + 0.31f, y + 0.31f, x + 0.29f, y + 0.43f, 3.0f, 0.23f, 0.44f, 0.67f);
    drawLine(x + 0.145f, y + 0.35f, x + 0.145f, y + 0.42f, 1.5f, 0.25f, 0.27f, 0.25f);
    drawLine(x + 0.185f, y + 0.35f, x + 0.185f, y + 0.42f, 1.5f, 0.25f, 0.27f, 0.25f);
    drawLine(x + 0.235f, y + 0.35f, x + 0.235f, y + 0.42f, 1.5f, 0.25f, 0.27f, 0.25f);
    drawLine(x + 0.265f, y + 0.35f, x + 0.265f, y + 0.42f, 1.5f, 0.25f, 0.27f, 0.25f);

    drawRectangle(x + 0.13f, y + 0.33f, 0.07f, 0.025f, 0.98f, 0.54f, 0.32f);
    drawRectangle(x + 0.22f, y + 0.33f, 0.06f, 0.025f, 0.98f, 0.54f, 0.32f);
    glColor3f(1.0f, 0.96f, 0.82f); drawText(x + 0.252f, y + 0.535f, "PLAYGROUND");
}

void drawGarden() {
    float x, y; getAreaPosition(1, x, y);

    // Garden boundary and sign
    drawBorder(x + 0.012f, y + 0.012f, 0.626f, 0.576f, 3.0f, 0.20f, 0.48f, 0.24f);
    drawRectangle(x + 0.23f, y + 0.515f, 0.19f, 0.055f, 0.20f, 0.48f, 0.24f);

    // Planting beds
    drawRectangle(x + 0.06f, y + 0.10f, 0.23f, 0.15f, 0.29f, 0.55f, 0.29f);
    drawRectangle(x + 0.36f, y + 0.10f, 0.23f, 0.15f, 0.29f, 0.55f, 0.29f);
    drawRectangle(x + 0.20f, y + 0.33f, 0.25f, 0.13f, 0.29f, 0.55f, 0.29f);

    // Flowers in the beds
    drawFlower(x + 0.10f, y + 0.17f, 0.011f);
    drawFlower(x + 0.175f, y + 0.17f, 0.011f);
    drawFlower(x + 0.25f, y + 0.17f, 0.011f);
    drawFlower(x + 0.40f, y + 0.17f, 0.011f);
    drawFlower(x + 0.475f, y + 0.17f, 0.011f);
    drawFlower(x + 0.55f, y + 0.17f, 0.011f);
    drawFlower(x + 0.24f, y + 0.39f, 0.011f);
    drawFlower(x + 0.315f, y + 0.39f, 0.011f);
    drawFlower(x + 0.39f, y + 0.39f, 0.011f);

    // Trees and stepping stones
    drawTree(x + 0.10f, y + 0.48f, 0.8f);
    drawTree(x + 0.55f, y + 0.46f, 0.8f);
    drawCircle(x + 0.08f, y + 0.29f, 0.025f, 0.018f, 0.18f, 0.48f, 0.23f);
    drawCircle(x + 0.24f, y + 0.29f, 0.025f, 0.018f, 0.18f, 0.48f, 0.23f);
    drawCircle(x + 0.40f, y + 0.29f, 0.025f, 0.018f, 0.18f, 0.48f, 0.23f);
    drawCircle(x + 0.56f, y + 0.29f, 0.025f, 0.018f, 0.18f, 0.48f, 0.23f);

    // Garden label
    glColor3f(0.94f, 1.0f, 0.90f); drawText(x + 0.283f, y + 0.535f, "GARDEN");
}

void drawSkating() {
    float x, y; getAreaPosition(2, x, y);

    // Skatepark border and title backing
    drawBorder(x + 0.012f, y + 0.012f, 0.626f, 0.576f, 3.0f, 0.36f, 0.47f, 0.55f);
    drawRectangle(x + 0.23f, y + 0.515f, 0.19f, 0.055f, 0.36f, 0.47f, 0.55f);

    // Ramps and center rail
    drawTriangle(x + 0.06f, y + 0.11f, 0.21f, 0.24f, 0.36f, 0.47f, 0.55f);
    drawTriangle(x + 0.38f, y + 0.11f, 0.21f, 0.24f, 0.36f, 0.47f, 0.55f);
    drawRectangle(x + 0.25f, y + 0.17f, 0.16f, 0.026f, 0.96f, 0.78f, 0.42f);
    drawRectangle(x + 0.28f, y + 0.13f, 0.015f, 0.09f, 0.23f, 0.30f, 0.35f);
    drawRectangle(x + 0.38f, y + 0.13f, 0.015f, 0.09f, 0.23f, 0.30f, 0.35f);

    // Upper ledge and safety markings
    drawRectangle(x + 0.07f, y + 0.42f, 0.51f, 0.025f, 0.90f, 0.91f, 0.84f);
    drawRectangle(x + 0.10f, y + 0.43f, 0.055f, 0.008f, 0.97f, 0.83f, 0.30f);
    drawRectangle(x + 0.20f, y + 0.43f, 0.055f, 0.008f, 0.97f, 0.83f, 0.30f);
    drawRectangle(x + 0.30f, y + 0.43f, 0.055f, 0.008f, 0.97f, 0.83f, 0.30f);
    drawRectangle(x + 0.40f, y + 0.43f, 0.055f, 0.008f, 0.97f, 0.83f, 0.30f);
    drawRectangle(x + 0.50f, y + 0.43f, 0.055f, 0.008f, 0.97f, 0.83f, 0.30f);

    // Area label
    glColor3f(0.94f, 0.98f, 1.0f); drawText(x + 0.28f, y + 0.535f, "SKATING");
}

void drawSeating() {
    float x, y; getAreaPosition(3, x, y);
    drawBorder(x + 0.012f, y + 0.012f, 0.626f, 0.576f, 3.0f, 0.37f, 0.52f, 0.32f);
    drawRectangle(x + 0.23f, y + 0.515f, 0.19f, 0.055f, 0.37f, 0.52f, 0.32f);

    // Gazebo roof and support
    drawCircle(x + 0.34f, y + 0.32f, 0.16f, 0.14f, 0.84f, 0.69f, 0.44f);
    drawTriangle(x + 0.16f, y + 0.31f, 0.36f, 0.20f, 0.55f, 0.31f, 0.21f);
    drawRectangle(x + 0.23f, y + 0.24f, 0.022f, 0.16f, 0.47f, 0.30f, 0.19f);
    drawRectangle(x + 0.43f, y + 0.24f, 0.022f, 0.16f, 0.47f, 0.30f, 0.19f);

    // Benches
    drawRectangle(x + 0.07f, y + 0.11f, 0.20f, 0.045f, 0.49f, 0.31f, 0.20f);
    drawRectangle(x + 0.39f, y + 0.11f, 0.20f, 0.045f, 0.49f, 0.31f, 0.20f);

    // Picnic table
    drawRectangle(x + 0.27f, y + 0.16f, 0.14f, 0.035f, 0.55f, 0.35f, 0.20f);
    drawRectangle(x + 0.29f, y + 0.13f, 0.018f, 0.045f, 0.35f, 0.24f, 0.16f);
    drawRectangle(x + 0.37f, y + 0.13f, 0.018f, 0.045f, 0.35f, 0.24f, 0.16f);
    drawCircle(x + 0.34f, y + 0.19f, 0.065f, 0.045f, 0.96f, 0.86f, 0.67f);
    drawCircle(x + 0.10f, y + 0.29f, 0.035f, 0.025f, 0.20f, 0.53f, 0.25f);
    drawCircle(x + 0.57f, y + 0.29f, 0.035f, 0.025f, 0.20f, 0.53f, 0.25f);
    glColor3f(0.95f, 1.0f, 0.91f); drawText(x + 0.28f, y + 0.535f, "SEATING");
}

// Centerpiece fountain and surrounding flowers.
void drawFountain() {
    // Circular stone pathway and fountain border
    drawCircle(0.0f, 0.0f, 0.205f, 0.205f, 0.89f, 0.79f, 0.62f); // Outer stone path
    drawCircle(0.0f, 0.0f, 0.145f, 0.145f, 0.33f, 0.49f, 0.43f); // Dark fountain rim
    drawCircle(0.0f, 0.0f, 0.123f, 0.123f, 0.66f, 0.72f, 0.69f); // Inner basin
    drawCircle(0.0f, 0.0f, 0.108f, 0.108f, 0.17f, 0.66f, 0.84f); // Blue water

    drawCircle(0.0f, 0.0f, 0.045f, 0.045f, 0.32f, 0.83f, 0.97f); // Fountain jet base
    drawCircle(0.0f, 0.0f, 0.021f, 0.021f, 0.87f, 0.96f, 0.99f); // Water spray highlight
    drawFlower(-0.16f, 0.00f, 0.008f); // Left flower
    drawFlower(0.16f, 0.00f, 0.008f); // Right flower
    drawFlower(0.00f, 0.16f, 0.008f); // Top flower
    drawFlower(0.00f, -0.16f, 0.008f); // Bottom flower
    drawFlower(-0.115f, 0.115f, 0.008f); // Upper-left flower
    drawFlower(0.115f, 0.115f, 0.008f); // Upper-right flower
    drawFlower(-0.115f, -0.115f, 0.008f); // Lower-left flower
    drawFlower(0.115f, -0.115f, 0.008f); // Lower-right flower
}

// Add edging to the connected walking paths.
void drawWalkingPaths() {
    // Dark edging makes the connected paths easier to read
    drawRectangle(-0.10f, -0.90f, 0.012f, 1.80f, 0.67f, 0.57f, 0.42f);
    drawRectangle(0.088f, -0.90f, 0.012f, 1.80f, 0.67f, 0.57f, 0.42f);
    drawRectangle(-0.90f, -0.10f, 1.80f, 0.012f, 0.67f, 0.57f, 0.42f);
    drawRectangle(-0.90f, 0.088f, 1.80f, 0.012f, 0.67f, 0.57f, 0.42f);
}

// Draw boundary trees, the entrance, and path lamps.
void drawParkSurroundings() {
    // Trees along the top boundary
    drawTree(-0.88f, 0.89f, 0.65f);
    drawTree(-0.53f, 0.89f, 0.65f);
    drawTree(-0.18f, 0.89f, 0.65f);
    drawTree(0.17f, 0.89f, 0.65f);
    drawTree(0.52f, 0.89f, 0.65f);
    drawTree(0.87f, 0.89f, 0.65f);
    // Trees along the bottom boundary, leaving space for the entrance
    drawTree(-0.88f, -0.88f, 0.65f);
    drawTree(-0.53f, -0.88f, 0.65f);
    drawTree(0.52f, -0.88f, 0.65f);
    drawTree(0.87f, -0.88f, 0.65f);
    // Trees along the left boundary
    drawTree(-0.91f, -0.65f, 0.65f);
    drawTree(-0.91f, -0.22f, 0.65f);
    drawTree(-0.91f, 0.21f, 0.65f);
    drawTree(-0.91f, 0.64f, 0.65f);
    // Trees along the right boundary
    drawTree(0.91f, -0.65f, 0.65f);
    drawTree(0.91f, -0.22f, 0.65f);
    drawTree(0.91f, 0.21f, 0.65f);
    drawTree(0.91f, 0.64f, 0.65f);

    // Light-colored entrance sign/base
    drawRectangle(-0.12f, -0.95f, 0.24f, 0.065f, 0.88f, 0.78f, 0.60f);
    // Two brown entrance posts
    drawRectangle(-0.15f, -0.95f, 0.035f, 0.095f, 0.47f, 0.30f, 0.18f);
    drawRectangle(0.115f, -0.95f, 0.035f, 0.095f, 0.47f, 0.30f, 0.18f);
    // Signboard and its welcome label
    drawRectangle(-0.13f, -0.86f, 0.26f, 0.055f, 0.16f, 0.38f, 0.24f);
    glColor3f(0.98f, 0.89f, 0.65f);
    drawText(-0.050f, -0.842f, "WELCOME");
    // Lamps beside the paths at the four garden corners
    drawLamp(-0.15f, 0.14f);
    drawLamp(0.15f, 0.14f);
    drawLamp(-0.15f, -0.14f);
    drawLamp(0.15f, -0.14f);
}

// Draw controls, layout status, and legend.
void drawPanel() {
    // Panel backgrounds
    drawRectangle(0.99f, -1.0f, 0.68f, 2.0f, 0.07f, 0.21f, 0.18f);
    drawRectangle(1.03f, 0.69f, 0.60f, 0.23f, 0.10f, 0.29f, 0.23f);
    drawRectangle(1.03f, -0.14f, 0.60f, 0.75f, 0.09f, 0.25f, 0.21f);
    drawRectangle(1.03f, -0.86f, 0.60f, 0.62f, 0.09f, 0.25f, 0.21f);

    // Title and subtitle
    drawBorder(1.03f, 0.69f, 0.60f, 0.23f, 2.0f, 0.20f, 0.45f, 0.34f);
    glColor3f(0.98f, 0.89f, 0.65f);
    drawText(1.10f, 0.85f, "NATURE HAVEN", GLUT_BITMAP_HELVETICA_18);
    drawText(1.10f, 0.76f, "Community Park Layout Planner");

    // Keyboard controls
    glColor3f(0.83f, 0.94f, 0.85f);
    drawText(1.10f, 0.58f, "KEYBOARD MENU");
    drawText(1.10f, 0.50f, "1 - Show All");
    drawText(1.10f, 0.40f, "2 - Toggle Playground");
    drawText(1.10f, 0.30f, "3 - Toggle Garden");
    drawText(1.10f, 0.20f, "4 - Toggle Seating");
    drawText(1.10f, 0.10f, "5 - Layout A");
    drawText(1.10f, 0.00f, "6 - Layout B");
    drawText(1.10f, -0.10f, "0 - Exit");

    // Active layout indicator
    glColor3f(0.98f, 0.89f, 0.65f);
    drawRectangle(1.08f, -0.22f, 0.50f, 0.075f, 0.16f, 0.38f, 0.28f);
    drawText(1.14f, -0.195f, currentLayout == 0 ? "CURRENT: LAYOUT A" : "CURRENT: LAYOUT B");

    // Feature color legend
    glColor3f(0.83f, 0.94f, 0.85f);
    drawText(1.10f, -0.39f, "COLOR LEGEND");
    drawRectangle(1.10f, -0.50f, 0.045f, 0.045f, 0.95f, 0.75f, 0.42f);
    drawRectangle(1.10f, -0.60f, 0.045f, 0.045f, 0.55f, 0.78f, 0.48f);
    drawRectangle(1.10f, -0.70f, 0.045f, 0.045f, 0.60f, 0.67f, 0.67f);
    drawRectangle(1.10f, -0.80f, 0.045f, 0.045f, 0.68f, 0.78f, 0.65f);
    glColor3f(0.95f, 0.95f, 0.88f);
    drawText(1.17f, -0.48f, "Playground");
    drawText(1.17f, -0.58f, "Garden");
    drawText(1.17f, -0.68f, "Skating");
    drawText(1.17f, -0.78f, "Seating");

    // Current status message
    glColor3f(0.98f, 0.89f, 0.65f);
    drawRectangle(1.03f, -0.96f, 0.60f, 0.075f, 0.16f, 0.38f, 0.28f);
    drawText(1.08f, -0.935f, message);
}

// Draw the park and menu.
void display() {
    glClearColor(0.08f, 0.15f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Park ground and path areas
    drawArea(0, 0.30f, 0.52f, 0.32f); // Base layer: green park lawn
    drawArea(1, 0.85f, 0.77f, 0.62f); // North-south walkway
    drawArea(2, 0.85f, 0.77f, 0.62f); // East-west walkway

    // Activity zones
    if (showPlayground) drawArea(3, 0.95f, 0.75f, 0.42f); // Warm-colored playground
    if (showGarden) drawArea(4, 0.55f, 0.78f, 0.48f); // Green garden plot
    drawArea(5, 0.60f, 0.67f, 0.67f); // Gray skating zone
    if (showSeating) drawArea(6, 0.68f, 0.78f, 0.65f); // Light-green seating zone

    // Park details and visible features
    drawWalkingPaths();
    drawParkSurroundings();
    if (showPlayground) drawPlayground();
    if (showGarden) drawGarden();
    drawSkating();
    if (showSeating) drawSeating();
    drawFountain();

    // On-screen control panel
    drawPanel();
    glFlush();
}

// Update the viewport.
void reshape(int width, int height) {
    windowWidth = width; windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Park uses about 75% of the window and the menu uses about 25%
    glOrtho(-1.0, 1.67, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

// Delete OpenGL buffers.
void cleanup() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, parkVBO);
    glDeleteBuffers(1, &parkIndexVBO);
    glDeleteBuffers(1, &decorationVBO);
    glDeleteBuffers(1, &decorationIndexVBO);
    glDeleteBuffers(1, &circleVBO);
    glDeleteBuffers(1, &triangleVBO);
}

// Handle keyboard input.
void monitorKeyboard(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    switch (key) {
    case '1':
        showPlayground = true; showGarden = true; showSeating = true;
        message = " [1] All features are visible."; break;
    case '2':
        showPlayground = !showPlayground;
        message = showPlayground ? " [2] Playground shown." : " [2] Playground hidden."; break;
    case '3':
        showGarden = !showGarden;
        message = showGarden ? " [3] Garden shown." : " [3] Garden hidden."; break;
    case '4':
        showSeating = !showSeating;
        message = showSeating ? " [4] Seating shown." : " [4] Seating hidden."; break;
    case '5':
        currentLayout = 0; message = " [5] Switched to Layout A."; break;
    case '6':
        currentLayout = 1; message = " [6] Switched to Layout B."; break;
    case '0':
        message = " [0] Exiting program.";
        cout << message << endl;
        cleanup(); exit(0);
    default:
        message = "Invalid choice. Use keys 0 to 6.";
        cout << message << endl;
        glutPostRedisplay(); return;
    }
    cout << message << endl;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    if (screenWidth > 0 && screenHeight > 0) {
        windowWidth = screenWidth - 30;
        windowHeight = screenHeight - 80;
    }
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Nature Haven - Community Park Planner");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(monitorKeyboard);
#ifndef __APPLE__
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "GLEW initialization failed." << endl;
        return 1;
    }
#endif
    initPark();
    initDecorations();
    glutMainLoop();
    return 0;
}
