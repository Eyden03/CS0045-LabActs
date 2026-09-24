/*
 Exercise MP3 - Dynamic Fireworks and Shape Burst Studio
 ------------------------------------
 Objective: Create an interactive galaxy celebration where different
 geometric fireworks expand and fade over time while allowing
 multiple animated bursts to appear together.
*/

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const float PI = 3.14159f;
const int MAX_BURSTS = 10;

struct Burst {
    bool active;
    int type;
    float x;
    float y;
    float size;
    float brightness;
    float red;
    float green;
    float blue;
};

Burst bursts[MAX_BURSTS];

int currentMode = 1;

// Function to draw bitmap text on the screen
void drawBitmapString(void* font, const char* text) {
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Return the name of the selected pattern
const char* getModeName(int type) {
    if (type == 1) {
        return "Concentric Squares";
    }
    else if (type == 2) {
        return "Diamond Lattice";
    }
    else {
        return "Starburst Triangles";
    }
}

// Count all active bursts
int countActiveBursts() {
    int count = 0;

    for (int i = 0; i < MAX_BURSTS; i++) {
        if (bursts[i].active) {
            count++;
        }
    }

    return count;
}

// Draw a simple filled circle
void drawCircle(float centerX, float centerY, float radius) {
    glBegin(GL_POLYGON);

    for (int angle = 0; angle < 360; angle += 10) {
        float radians = angle * PI / 180.0f;

        glVertex2f(
            centerX + cos(radians) * radius,
            centerY + sin(radians) * radius
        );
    }

    glEnd();
}

// Draw a ring around a planet
void drawPlanetRing(float centerX, float centerY) {
    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);

    for (int angle = 0; angle < 360; angle += 10) {
        float radians = angle * PI / 180.0f;

        glVertex2f(
            centerX + cos(radians) * 0.17f,
            centerY + sin(radians) * 0.06f
        );
    }

    glEnd();
}

// Draw the galaxy background
void drawGalaxy() {
    // Small lavender stars
    glPointSize(3.0f);
    glColor3f(0.82f, 0.78f, 1.0f);

    glBegin(GL_POINTS);
    glVertex2f(-0.94f, 0.84f);
    glVertex2f(-0.82f, 0.20f);
    glVertex2f(-0.68f, -0.50f);
    glVertex2f(-0.52f, 0.72f);
    glVertex2f(-0.38f, -0.76f);
    glVertex2f(-0.20f, 0.58f);
    glVertex2f(-0.02f, -0.55f);
    glVertex2f(0.15f, 0.76f);
    glVertex2f(0.32f, -0.68f);
    glVertex2f(0.45f, 0.42f);
    glEnd();

    // Bright golden stars
    glPointSize(5.0f);
    glColor3f(1.0f, 0.82f, 0.30f);

    glBegin(GL_POINTS);
    glVertex2f(-0.88f, -0.18f);
    glVertex2f(-0.62f, 0.38f);
    glVertex2f(-0.42f, -0.30f);
    glVertex2f(0.05f, 0.30f);
    glVertex2f(0.38f, -0.22f);
    glEnd();

    // Spiral galaxy arms
    glPointSize(4.0f);

    glBegin(GL_POINTS);

    for (int i = 0; i < 70; i++) {
        float angle = i * 0.28f;
        float radius = i * 0.005f;

        float galaxyX =
            -0.18f + cos(angle) * radius;

        float galaxyY =
            0.02f + sin(angle) * radius * 0.55f;

        if (i % 2 == 0) {
            glColor3f(0.55f, 0.40f, 1.0f);
        }
        else {
            glColor3f(0.35f, 0.75f, 1.0f);
        }

        glVertex2f(galaxyX, galaxyY);
        glVertex2f(
            -0.18f - cos(angle) * radius,
            0.02f - sin(angle) * radius * 0.55f
        );
    }

    glEnd();

    // Bright galaxy center
    glColor3f(1.0f, 0.75f, 0.95f);
    drawCircle(-0.18f, 0.02f, 0.035f);

    // Ringed planet
    glColor3f(0.65f, 0.38f, 0.90f);
    drawCircle(-0.76f, 0.62f, 0.10f);

    glColor3f(0.95f, 0.65f, 1.0f);
    drawPlanetRing(-0.76f, 0.62f);

    // Shooting stars
    glLineWidth(2.0f);
    glColor3f(0.75f, 0.90f, 1.0f);

    glBegin(GL_LINES);
    glVertex2f(-0.88f, 0.48f);
    glVertex2f(-0.72f, 0.38f);

    glVertex2f(0.22f, 0.68f);
    glVertex2f(0.38f, 0.58f);
    glEnd();

    glPointSize(6.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    glVertex2f(-0.72f, 0.38f);
    glVertex2f(0.38f, 0.58f);
    glEnd();
}

// Select one random galaxy color
void selectRandomColor(
    float& red,
    float& green,
    float& blue
) {
    int color = rand() % 5;

    if (color == 0) {
        red = 1.0f;
        green = 0.35f;
        blue = 0.70f;
    }
    else if (color == 1) {
        red = 0.45f;
        green = 0.85f;
        blue = 1.0f;
    }
    else if (color == 2) {
        red = 0.70f;
        green = 0.40f;
        blue = 1.0f;
    }
    else if (color == 3) {
        red = 0.35f;
        green = 1.0f;
        blue = 0.75f;
    }
    else {
        red = 1.0f;
        green = 0.75f;
        blue = 0.25f;
    }
}

// Create a new burst in an available slot
void spawnBurst(int type) {
    for (int i = 0; i < MAX_BURSTS; i++) {
        if (!bursts[i].active) {
            bursts[i].active = true;
            bursts[i].type = type;

            bursts[i].x =
                -0.75f + (rand() % 110) / 100.0f;

            bursts[i].y =
                -0.60f + (rand() % 125) / 100.0f;

            bursts[i].size = 0.04f;
            bursts[i].brightness = 1.0f;

            selectRandomColor(
                bursts[i].red,
                bursts[i].green,
                bursts[i].blue
            );

            cout << "Burst created: "
                << getModeName(type) << endl;
            return;
        }
    }

    cout << "Maximum active bursts reached." << endl;
}

// Draw one square outline
void drawSquareOutline(float x, float y, float size) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
    glEnd();
}

// Draw expanding concentric squares
void drawConcentricSquares(Burst burst) {
    glLineWidth(3.0f);

    drawSquareOutline(
        burst.x,
        burst.y,
        burst.size
    );

    drawSquareOutline(
        burst.x,
        burst.y,
        burst.size * 0.70f
    );

    drawSquareOutline(
        burst.x,
        burst.y,
        burst.size * 0.40f
    );
}

// Draw one diamond outline
void drawDiamondOutline(float x, float y, float size) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y + size);
    glVertex2f(x + size, y);
    glVertex2f(x, y - size);
    glVertex2f(x - size, y);
    glEnd();
}

// Draw an expanding diamond lattice
void drawDiamondLattice(Burst burst) {
    glLineWidth(3.0f);

    drawDiamondOutline(
        burst.x,
        burst.y,
        burst.size
    );

    drawDiamondOutline(
        burst.x - burst.size * 0.65f,
        burst.y,
        burst.size * 0.45f
    );

    drawDiamondOutline(
        burst.x + burst.size * 0.65f,
        burst.y,
        burst.size * 0.45f
    );

    drawDiamondOutline(
        burst.x,
        burst.y + burst.size * 0.65f,
        burst.size * 0.45f
    );

    drawDiamondOutline(
        burst.x,
        burst.y - burst.size * 0.65f,
        burst.size * 0.45f
    );
}

// Draw expanding starburst triangles
void drawStarburstTriangles(Burst burst) {
    for (int i = 0; i < 8; i++) {
        float angle = i * PI / 4.0f;
        float leftAngle = angle - 0.14f;
        float rightAngle = angle + 0.14f;

        float innerSize = burst.size * 0.30f;
        float outerSize = burst.size;

        glBegin(GL_TRIANGLES);

        glVertex2f(
            burst.x + cos(leftAngle) * innerSize,
            burst.y + sin(leftAngle) * innerSize
        );

        glVertex2f(
            burst.x + cos(angle) * outerSize,
            burst.y + sin(angle) * outerSize
        );

        glVertex2f(
            burst.x + cos(rightAngle) * innerSize,
            burst.y + sin(rightAngle) * innerSize
        );

        glEnd();
    }
}

// Draw all active bursts
void drawBursts() {
    for (int i = 0; i < MAX_BURSTS; i++) {
        if (bursts[i].active) {
            glColor3f(
                bursts[i].red * bursts[i].brightness,
                bursts[i].green * bursts[i].brightness,
                bursts[i].blue * bursts[i].brightness
            );

            if (bursts[i].type == 1) {
                drawConcentricSquares(bursts[i]);
            }
            else if (bursts[i].type == 2) {
                drawDiamondLattice(bursts[i]);
            }
            else {
                drawStarburstTriangles(bursts[i]);
            }
        }
    }
}

// Draw the information sidebar
void drawSidebar() {
    char buffer[80];

    // Sidebar background
    glColor3f(0.10f, 0.05f, 0.20f);

    glBegin(GL_QUADS);
    glVertex2f(0.52f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(0.52f, 1.0f);
    glEnd();

    glColor3f(0.88f, 0.78f, 1.0f);
    glRasterPos2f(0.58f, 0.82f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        "COSMIC BURST STUDIO"
    );

    glColor3f(1.0f, 1.0f, 1.0f);

    snprintf(
        buffer,
        sizeof(buffer),
        "Mode: %s",
        getModeName(currentMode)
    );
    glRasterPos2f(0.58f, 0.62f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        buffer
    );

    snprintf(
        buffer,
        sizeof(buffer),
        "Active Bursts: %d",
        countActiveBursts()
    );
    glRasterPos2f(0.58f, 0.48f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        buffer
    );

    glColor3f(0.75f, 0.85f, 1.0f);

    glRasterPos2f(0.58f, 0.25f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[1] Concentric Squares"
    );

    glRasterPos2f(0.58f, 0.10f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[2] Diamond Lattice"
    );

    glRasterPos2f(0.58f, -0.05f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[3] Starburst Triangles"
    );

    glRasterPos2f(0.58f, -0.20f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[SPACE] Repeat Mode"
    );

    glRasterPos2f(0.58f, -0.35f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[C] Clear Bursts"
    );

    glRasterPos2f(0.58f, -0.50f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[ESC] Exit"
    );
}

// Clear all active bursts
void clearBursts() {
    for (int i = 0; i < MAX_BURSTS; i++) {
        bursts[i].active = false;
    }

    cout << "All bursts cleared." << endl;
}

// Display the studio
void display() {
    glClearColor(0.03f, 0.01f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawGalaxy();
    drawBursts();
    drawSidebar();

    glFlush();
}

// Handle keyboard controls
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '1':
        currentMode = 1;
        spawnBurst(1);
        break;

    case '2':
        currentMode = 2;
        spawnBurst(2);
        break;

    case '3':
        currentMode = 3;
        spawnBurst(3);
        break;

    case ' ':
        spawnBurst(currentMode);
        break;

    case 'c':
    case 'C':
        clearBursts();
        break;

    case 27:
        exit(0);
    }

    glutPostRedisplay();
}

// Update the size and brightness of each burst
void updateBursts(int value) {
    for (int i = 0; i < MAX_BURSTS; i++) {
        if (bursts[i].active) {
            bursts[i].size += 0.012f;
            bursts[i].brightness -= 0.025f;

            if (bursts[i].brightness <= 0.05f) {
                bursts[i].active = false;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updateBursts, 0);
}

int main(int argc, char** argv) {
    srand(time(0));

    for (int i = 0; i < MAX_BURSTS; i++) {
        bursts[i].active = false;
    }

    glutInit(&argc, argv);
    glutInitWindowSize(1000, 700); // window size
    glutInitWindowPosition(150, 100); // screen position
    glutCreateWindow(
        "Machine Problem 3 - Cosmic Burst Studio"
    );

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, updateBursts, 0);

    glutMainLoop();
    return 0;
}