/*
 Exercise MP1 - The Cosmic Dodger
 ------------------------------------
 Objective: Create an astronomy-themed survival game where the player
 controls a spaceship, avoids falling asteroids, earns points,
 and protects three lives.
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
#include <cmath>
using namespace std;

const float PI = 3.14159f;

float shipX = 0.0f;
float shipY = -0.65f;
float shipSpeed = 0.18f;


float asteroid1X = -0.50f;
float asteroid1Y = 1.0f;
float asteroid1Speed = 0.012f;

float asteroid2X = 0.45f;
float asteroid2Y = 1.35f;
float asteroid2Speed = 0.020f;

int score = 0;
int lives = 3;
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

// Draw the moon and its craters
void drawMoon() {
    // Moon
    glColor3f(0.90f, 0.88f, 0.72f);
    drawCircle(0.68f, 0.55f, 0.18f);

    // Moon craters
    glColor3f(0.70f, 0.68f, 0.58f);
    drawCircle(0.62f, 0.61f, 0.035f);
    drawCircle(0.73f, 0.50f, 0.045f);
    drawCircle(0.72f, 0.65f, 0.025f);
}

// Draw the galaxy stars
void drawStars() {
    glPointSize(3.0f);

    glColor3f(0.90f, 0.85f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2f(-0.88f, 0.68f);
    glVertex2f(-0.70f, 0.30f);
    glVertex2f(-0.52f, 0.58f);
    glVertex2f(-0.30f, 0.22f);
    glVertex2f(-0.08f, 0.65f);
    glVertex2f(0.15f, 0.38f);
    glVertex2f(0.38f, 0.70f);
    glVertex2f(0.88f, 0.15f);
    glVertex2f(-0.78f, -0.30f);
    glVertex2f(-0.40f, -0.55f);
    glVertex2f(0.30f, -0.40f);
    glVertex2f(0.75f, -0.30f);
    glEnd();

    glPointSize(5.0f);

    glColor3f(1.0f, 0.85f, 0.40f);
    glBegin(GL_POINTS);
    glVertex2f(-0.62f, 0.75f);
    glVertex2f(-0.18f, 0.42f);
    glVertex2f(0.42f, 0.12f);
    glVertex2f(0.82f, -0.58f);
    glEnd();
}

// Draw the player's spaceship
void drawShip() {
    // Ship wings
    glColor3f(0.55f, 0.30f, 0.90f);
    glBegin(GL_QUADS);
    glVertex2f(shipX - 0.18f, shipY - 0.07f);
    glVertex2f(shipX - 0.06f, shipY + 0.02f);
    glVertex2f(shipX + 0.06f, shipY + 0.02f);
    glVertex2f(shipX + 0.18f, shipY - 0.07f);
    glEnd();

    // Ship body
    glColor3f(0.25f, 0.90f, 0.75f);
    glBegin(GL_TRIANGLES);
    glVertex2f(shipX, shipY + 0.16f);
    glVertex2f(shipX - 0.10f, shipY - 0.11f);
    glVertex2f(shipX + 0.10f, shipY - 0.11f);
    glEnd();

    // Ship window
    glColor3f(1.0f, 0.82f, 0.30f);
    glPointSize(13.0f);
    glBegin(GL_POINTS);
    glVertex2f(shipX, shipY + 0.04f);
    glEnd();

    // Ship flame
    glColor3f(1.0f, 0.35f, 0.55f);
    glBegin(GL_TRIANGLES);
    glVertex2f(shipX - 0.04f, shipY - 0.10f);
    glVertex2f(shipX + 0.04f, shipY - 0.10f);
    glVertex2f(shipX, shipY - 0.20f);
    glEnd();
}

// Draw one asteroid
void drawAsteroid(
    float x,
    float y,
    float red,
    float green,
    float blue
) {
    glColor3f(red, green, blue);

    glBegin(GL_POLYGON);
    glVertex2f(x - 0.08f, y);
    glVertex2f(x - 0.05f, y + 0.07f);
    glVertex2f(x + 0.03f, y + 0.09f);
    glVertex2f(x + 0.08f, y + 0.03f);
    glVertex2f(x + 0.06f, y - 0.06f);
    glVertex2f(x - 0.02f, y - 0.09f);
    glVertex2f(x - 0.07f, y - 0.05f);
    glEnd();
}

// Draw score, lives, and controls
void drawHUD() {
    char buffer[50];

    glColor3f(1.0f, 1.0f, 1.0f);

    snprintf(buffer, sizeof(buffer), "Score: %d", score);
    glRasterPos2f(-0.92f, 0.91f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    snprintf(buffer, sizeof(buffer), "Lives: %d", lives);
    glRasterPos2f(0.60f, 0.91f);
    drawBitmapString(GLUT_BITMAP_HELVETICA_18, buffer);

    glColor3f(0.78f, 0.72f, 0.95f);
    glRasterPos2f(-0.92f, 0.81f);
    drawBitmapString(
        GLUT_BITMAP_HELVETICA_12,
        "[W][A][S][D] Move | [R] Restart | [ESC] Exit"
    );
}

// Check if an asteroid touches the spaceship
bool checkCollision(float asteroidX, float asteroidY) {
    float distanceX = shipX - asteroidX;
    float distanceY = shipY - asteroidY;

    if (distanceX < 0) distanceX = -distanceX;
    if (distanceY < 0) distanceY = -distanceY;

    return distanceX < 0.16f && distanceY < 0.18f;
}

// Reset the first asteroid
void resetAsteroid1() {
    asteroid1Y = 1.05f;
    asteroid1X += 0.55f;

    if (asteroid1X > 0.75f) {
        asteroid1X = -0.70f;
    }
}

// Reset the second asteroid
void resetAsteroid2() {
    asteroid2Y = 1.30f;
    asteroid2X -= 0.60f;

    if (asteroid2X < -0.75f) {
        asteroid2X = 0.70f;
    }
}

// Restore the starting game state
void resetGame() {
    shipX = 0.0f;
    shipY = -0.65f;

    asteroid1X = -0.50f;
    asteroid1Y = 1.0f;

    asteroid2X = 0.45f;
    asteroid2Y = 1.35f;

    score = 0;
    lives = 3;
    gameRunning = true;

    cout << "Game restarted." << endl;
    glutPostRedisplay();
}

// Display the game
void display() {
    glClearColor(0.04f, 0.02f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawStars();
    drawMoon();
    drawHUD();

    if (gameRunning) {
        drawShip();

        drawAsteroid(
            asteroid1X,
            asteroid1Y,
            0.95f,
            0.38f,
            0.30f
        );

        drawAsteroid(
            asteroid2X,
            asteroid2Y,
            0.85f,
            0.55f,
            0.20f
        );
    }
    else {
        glColor3f(1.0f, 0.42f, 0.70f);
        glRasterPos2f(-0.38f, 0.02f);
        drawBitmapString(
            GLUT_BITMAP_HELVETICA_18,
            "GAME OVER - Press R to Restart"
        );
    }

    glFlush();
}

// Handle keyboard controls
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
    case 'W':
        if (gameRunning) shipY += shipSpeed;
        break;

    case 's':
    case 'S':
        if (gameRunning) shipY -= shipSpeed;
        break;

    case 'a':
    case 'A':
        if (gameRunning) shipX -= shipSpeed;
        break;

    case 'd':
    case 'D':
        if (gameRunning) shipX += shipSpeed;
        break;

    case 'r':
    case 'R':
        resetGame();
        break;

    case 27:
        exit(0);
    }

    // Keep the spaceship inside the play area
    if (shipX > 0.82f) shipX = 0.82f;
    if (shipX < -0.82f) shipX = -0.82f;
    if (shipY > 0.62f) shipY = 0.62f;
    if (shipY < -0.78f) shipY = -0.78f;

    glutPostRedisplay();
}

// Update the falling asteroids
void updateGame(int value) {
    if (gameRunning) {
        asteroid1Y -= asteroid1Speed;
        asteroid2Y -= asteroid2Speed;

        // Award points for avoided asteroids
        if (asteroid1Y < -1.10f) {
            score++;
            resetAsteroid1();
        }

        if (asteroid2Y < -1.10f) {
            score++;
            resetAsteroid2();
        }

        // Check the first asteroid
        if (checkCollision(asteroid1X, asteroid1Y)) {
            lives--;
            cout << "Spaceship hit! Lives remaining: "
                << lives << endl;
            resetAsteroid1();
        }

        // Check the second asteroid
        else if (checkCollision(asteroid2X, asteroid2Y)) {
            lives--;
            cout << "Spaceship hit! Lives remaining: "
                << lives << endl;
            resetAsteroid2();
        }

        if (lives <= 0) {
            lives = 0;
            gameRunning = false;
            cout << "GAME OVER" << endl;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(25, updateGame, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 700); // window size
    glutInitWindowPosition(200, 100); // screen position
    glutCreateWindow("Machine Problem 1 - The Cosmic Dodger");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, updateGame, 0);

    glutMainLoop();
    return 0;
}