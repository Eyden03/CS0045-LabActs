/*
 Exercise MP2 - Chroma-Shift
 ------------------------------------
 Objective: Create a galaxy-themed color-matching game where the player
 changes between red, green, and blue to match an approaching energy
 barrier while earning points and avoiding a game-over mismatch.
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

int playerColor = 1;
int barrierColor = 1;

float barrierX = 1.10f;
float barrierSpeed = 0.012f;

int barrierDirection = -1;
int score = 0;

bool gameRunning = true;

// Function to draw bitmap text on the screen
void drawBitmapString(void* font, const char* text) {
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Draw a simple circle
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

// Draw the galaxy background
void drawGalaxy() {
    // Draw small stars
    glPointSize(3.0f);
    glColor3f(0.88f, 0.82f, 1.0f);

    glBegin(GL_POINTS);
    glVertex2f(-0.90f, 0.65f);
    glVertex2f(-0.72f, 0.25f);
    glVertex2f(-0.55f, -0.55f);
    glVertex2f(-0.30f, 0.50f);
    glVertex2f(-0.12f, -0.35f);
    glVertex2f(0.15f, 0.62f);
    glVertex2f(0.32f, -0.60f);
    glVertex2f(0.55f, 0.40f);
    glVertex2f(0.72f, -0.40f);
    glVertex2f(0.90f, 0.18f);
    glEnd();

    // Draw bright stars
    glPointSize(5.0f);
    glColor3f(1.0f, 0.82f, 0.30f);

    glBegin(GL_POINTS);
    glVertex2f(-0.62f, 0.72f);
    glVertex2f(-0.40f, -0.18f);
    glVertex2f(0.40f, 0.28f);
    glVertex2f(0.82f, -0.65f);
    glEnd();

    // Draw a crescent moon
    glColor3f(0.90f, 0.88f, 0.72f);
    drawCircle(-0.72f, 0.48f, 0.13f);

    glColor3f(0.04f, 0.02f, 0.12f);
    drawCircle(-0.66f, 0.52f, 0.12f);
}

// Apply the selected RGB color
void setColor(int colorCode) {
    if (colorCode == 1) {
        glColor3f(1.0f, 0.20f, 0.30f);
    }
    else if (colorCode == 2) {
        glColor3f(0.20f, 1.0f, 0.45f);
    }
    else {
        glColor3f(0.20f, 0.55f, 1.0f);
    }
}

// Return the selected color name
const char* getColorName(int colorCode) {
    if (colorCode == 1) {
        return "RED";
    }
    else if (colorCode == 2) {
        return "GREEN";
    }
    else {
        return "BLUE";
    }
}

// Draw the player square
void drawPlayer() {
    setColor(playerColor);

    glBegin(GL_QUADS);
    glVertex2f(-0.13f, -0.23f);
    glVertex2f(0.13f, -0.23f);
    glVertex2f(0.13f, 0.03f);
    glVertex2f(-0.13f, 0.03f);
    glEnd();

    // Draw player outline
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.13f, -0.23f);
    glVertex2f(0.13f, -0.23f);
    glVertex2f(0.13f, 0.03f);
    glVertex2f(-0.13f, 0.03f);
    glEnd();
}

// Draw the approaching energy barrier
void drawBarrier() {
    setColor(barrierColor);

    // Main energy barrier
    glBegin(GL_QUADS);
    glVertex2f(barrierX - 0.06f, -0.48f);
    glVertex2f(barrierX + 0.06f, -0.48f);
    glVertex2f(barrierX + 0.06f, 0.28f);
    glVertex2f(barrierX - 0.06f, 0.28f);
    glEnd();

    // Draw barrier outline
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(barrierX - 0.08f, -0.50f);
    glVertex2f(barrierX + 0.08f, -0.50f);
    glVertex2f(barrierX + 0.08f, 0.30f);
    glVertex2f(barrierX - 0.08f, 0.30f);
    glEnd();
}

// Draw the game dashboard
void drawDashboard() {
    char buffer[80];

    glColor3f(1.0f, 1.0f, 1.0f);

    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    glRasterPos2f(-0.92f, 0.91f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    glRasterPos2f(0.55f, 0.91f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_18,
        "Penalty: GAME OVER"
    );

    snprintf(
        buffer,
        sizeof(buffer),
        "Current Color: %s",
        getColorName(playerColor)
    );
    glRasterPos2f(-0.22f, 0.78f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    glColor3f(0.78f, 0.72f, 0.95f);

    glRasterPos2f(-0.92f, -0.78f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[R] Red | [G] Green | [B] Blue"
    );

    glRasterPos2f(-0.92f, -0.88f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "Correct: +1 Point | Mismatch: Game Over"
    );

    if (barrierDirection == -1) {
        glRasterPos2f(0.47f, -0.78f);
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_12,
            "Direction: RIGHT TO LEFT"
        );
    }
    else {
        glRasterPos2f(0.47f, -0.78f);
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_12,
            "Direction: LEFT TO RIGHT"
        );
    }
}

// Compare the player and barrier colors
bool colorsMatch() {
    return playerColor == barrierColor;
}

// Prepare the next barrier
void spawnNextBarrier() {
    // Alternate the barrier direction
    barrierDirection = -barrierDirection;

    if (barrierDirection == -1) {
        barrierX = 1.10f;
    }
    else {
        barrierX = -1.10f;
    }

    // Select a random barrier color
    int previousColor = barrierColor;

    do {
        barrierColor = rand() % 3 + 1;
    } while (barrierColor == previousColor);
}

// Check the barrier when it reaches the player
void checkGateCollision() {
    if (barrierX > -0.12f && barrierX < 0.12f) {
        if (colorsMatch()) {
            score++;

            // Increase speed after a correct match
            barrierSpeed += 0.002f;

            if (barrierSpeed > 0.035f) {
                barrierSpeed = 0.035f;
            }

            cout << "Correct match! Score: "
                << score << endl;

            spawnNextBarrier();
        }
        else {
            gameRunning = false;

            cout << "Color mismatch! GAME OVER. Final Score: "
                << score << endl;
        }
    }
}

// Reset all game values
void resetGame() {
    playerColor = 1;
    barrierColor = rand() % 3 + 1;

    barrierX = 1.10f;
    barrierSpeed = 0.012f;
    barrierDirection = -1;

    score = 0;
    gameRunning = true;

    cout << "Game restarted." << endl;
    glutPostRedisplay();
}

// Display the game
void display() {
    glClearColor(0.04f, 0.02f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawGalaxy();
    drawDashboard();

    if (gameRunning) {
        drawPlayer();
        drawBarrier();
    }
    else {
        glColor3f(1.0f, 0.42f, 0.70f);
        glRasterPos2f(-0.36f, 0.05f);
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "COLOR MISMATCH - GAME OVER"
        );

        glColor3f(0.88f, 0.82f, 1.0f);
        glRasterPos2f(-0.30f, -0.08f);
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "Press SPACE to Restart"
        );
    }

    glFlush();
}

// Handle keyboard controls
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
    case 'R':
        if (gameRunning) {
            playerColor = 1;
            cout << "Player color: RED" << endl;
        }
        break;

    case 'g':
    case 'G':
        if (gameRunning) {
            playerColor = 2;
            cout << "Player color: GREEN" << endl;
        }
        break;

    case 'b':
    case 'B':
        if (gameRunning) {
            playerColor = 3;
            cout << "Player color: BLUE" << endl;
        }
        break;

    case ' ':
        if (!gameRunning) {
            resetGame();
        }
        break;

    case 27:
        exit(0);
    }

    glutPostRedisplay();
}

// Update the moving barrier
void updateBarrier(int value) {
    if (gameRunning) {
        barrierX += barrierSpeed * barrierDirection;
        checkGateCollision();
    }

    glutPostRedisplay();
    glutTimerFunc(25, updateBarrier, 0);
}

int main(int argc, char** argv) {
    srand(time(0));
    barrierColor = rand() % 3 + 1;

    glutInit(&argc, argv);
    glutInitWindowSize(900, 650); // window size
    glutInitWindowPosition(200, 100); // screen position
    glutCreateWindow("Machine Problem 2 - Chroma-Shift");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, updateBarrier, 0);

    glutMainLoop();
    return 0;
}