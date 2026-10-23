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
 * Machine Problem 03 - Warehouse Navigator Robot Route Simulator
 * -------------------------------------------------------------
 * This program shows a warehouse with three storage zones.
 * Users can move the robot, change its step size, or run an auto demo.
 * The robot moves by editing its VBO using glMapBuffer().
 */

GLuint robotVBO, warehouseVBO, warehouseIndexVBO;

const int ROBOT_VERTICES = 3;
const float MIN_X = -0.89f, MAX_X = 0.89f;
const float MIN_Y = -0.89f, MAX_Y = 0.89f;
const float ROBOT_HALF_WIDTH = 0.045f;
const float ROBOT_HEIGHT = 0.09f;
const float START_X = -0.67f, START_Y = -0.68f;

GLfloat startVertices[] = {
    -0.045f, 0.00f, 0.0f, // Bottom-left point
     0.045f, 0.00f, 0.0f, // Bottom-right point
     0.000f, 0.09f, 0.0f  // Top point
};

float robotX = START_X, robotY = START_Y;
float stepSize = 0.10f;
bool autoMove = false;
bool enteringStep = false;
int autoStage = 0;
int timerVersion = 0;
char stepInput[24] = "";
int stepLength = 0;
const char* message = "Welcome! Use keys 0 to 7.";

// Zone A, Zone B, Zone C, then back to the starting position.
const float routeX[] = { -0.65f, 0.65f, 0.65f, START_X };
const float routeY[] = { 0.52f, 0.52f,-0.55f, START_Y };

void drawText(float x, float y, const char* words, void* font = GLUT_BITMAP_HELVETICA_12) {
    glRasterPos2f(x, y);
    for (const char* p = words; *p != '\0'; p++)
        glutBitmapCharacter(font, *p);
}

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void initWarehouse() {
    GLfloat rectangle[] = {
        0.0f, 0.0f, 0.0f, // Bottom-left point
        1.0f, 0.0f, 0.0f, // Bottom-right point
        1.0f, 1.0f, 0.0f, // Top-right point
        0.0f, 1.0f, 0.0f  // Top-left point
    };
    GLubyte indices[] = { 0, 1, 2, 0, 2, 3 };

    glGenBuffers(1, &warehouseVBO);
    glBindBuffer(GL_ARRAY_BUFFER, warehouseVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    glGenBuffers(1, &warehouseIndexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, warehouseIndexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawRectangle(float x, float y, float w, float h, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(w, h, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, warehouseVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, warehouseIndexVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(r, g, b);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glPopMatrix();
}

void drawWarehouse() {
    drawRectangle(-0.95f, -0.95f, 1.90f, 1.90f, 0.13f, 0.21f, 0.27f); // Warehouse boundary
    drawRectangle(-0.89f, -0.89f, 1.78f, 1.78f, 0.25f, 0.32f, 0.37f); // Warehouse floor

    // Floor guide lines
    for (int i = -7; i <= 7; i += 2) {
        float v = i * 0.10f;
        drawLine(v, -0.88f, v, 0.88f, 0.31f, 0.38f, 0.42f);
        drawLine(-0.88f, v, 0.88f, v, 0.31f, 0.38f, 0.42f);
    }

    // Three color-coded destination zones
    drawRectangle(-0.84f, 0.36f, 0.39f, 0.40f, 0.19f, 0.55f, 0.44f); // Zone A - green
    drawRectangle(0.45f, 0.36f, 0.39f, 0.40f, 0.76f, 0.54f, 0.24f); // Zone B - gold
    drawRectangle(0.45f, -0.75f, 0.39f, 0.40f, 0.47f, 0.38f, 0.70f); // Zone C - purple

    // Storage shelves
    for (int i = 0; i < 3; i++) {
        drawRectangle(-0.80f + i * 0.115f, 0.42f, 0.07f, 0.14f, 0.10f, 0.33f, 0.28f);
        drawRectangle(0.49f + i * 0.115f, 0.42f, 0.07f, 0.14f, 0.51f, 0.33f, 0.15f);
        drawRectangle(0.49f + i * 0.115f, -0.68f, 0.07f, 0.14f, 0.30f, 0.23f, 0.47f);
    }

    glColor3f(1.0f, 1.0f, 0.95f);
    drawText(-0.78f, 0.66f, "ZONE A");
    drawText(0.51f, 0.66f, "ZONE B");
    drawText(0.51f, -0.44f, "ZONE C");

    // Starting area and center aisle
    drawRectangle(-0.82f, -0.83f, 0.31f, 0.07f, 0.12f, 0.40f, 0.52f);
    glColor3f(0.95f, 0.97f, 1.0f);
    drawText(-0.79f, -0.81f, "START");
    drawLine(-0.05f, -0.83f, -0.05f, 0.83f, 0.88f, 0.75f, 0.40f);
    drawLine(0.05f, -0.83f, 0.05f, 0.83f, 0.88f, 0.75f, 0.40f);
}

// robot
void initRobot() {
    GLfloat vertices[9];
    for (int i = 0; i < ROBOT_VERTICES; i++) {
        vertices[i * 3] = startVertices[i * 3] + START_X;
        vertices[i * 3 + 1] = startVertices[i * 3 + 1] + START_Y;
        vertices[i * 3 + 2] = 0.0f;
    }
    glGenBuffers(1, &robotVBO);
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    // The robot moves often, so its vertex data uses GL_DYNAMIC_DRAW.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool updateRobotPosition(float newX, float newY) {
    // Check the entire triangle before moving it.
    if (!isfinite(newX) || !isfinite(newY) ||
        newX - ROBOT_HALF_WIDTH < MIN_X || newX + ROBOT_HALF_WIDTH > MAX_X ||
        newY < MIN_Y || newY + ROBOT_HEIGHT > MAX_Y) {
        cout << "Movement blocked: warehouse boundary." << endl;
        message = "Movement blocked at boundary.";
        glutPostRedisplay();
        return false;
    }

    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    GLfloat* vertices = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    if (vertices == NULL) {
        cout << "Could not map the robot VBO." << endl;
        message = "Robot buffer mapping failed.";
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glutPostRedisplay();
        return false;
    }

    // Change the X and Y positions of all three vertices.
    for (int i = 0; i < ROBOT_VERTICES; i++) {
        vertices[i * 3] = startVertices[i * 3] + newX;
        vertices[i * 3 + 1] = startVertices[i * 3 + 1] + newY;
        vertices[i * 3 + 2] = startVertices[i * 3 + 2];
    }
    GLboolean success = glUnmapBuffer(GL_ARRAY_BUFFER);
    if (success != GL_TRUE) {
        // An unsuccessful unmap means the old buffer contents cannot be trusted.
        GLfloat resetVertices[9];
        for (int i = 0; i < ROBOT_VERTICES; i++) {
            resetVertices[i * 3] = startVertices[i * 3] + robotX;
            resetVertices[i * 3 + 1] = startVertices[i * 3 + 1] + robotY;
            resetVertices[i * 3 + 2] = 0.0f;
        }
        glBufferData(GL_ARRAY_BUFFER, sizeof(resetVertices), resetVertices, GL_DYNAMIC_DRAW);
        cout << "Robot buffer was restored after an unmap error." << endl;
        message = "Robot buffer restored.";
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glutPostRedisplay();
        return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    robotX = newX;
    robotY = newY;
    glutPostRedisplay();
    return true;
}

void drawRobot() {
    glBindBuffer(GL_ARRAY_BUFFER, robotVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glColor3f(0.25f, 0.83f, 0.96f); // Blue robot triangle
    glDrawArrays(GL_TRIANGLES, 0, ROBOT_VERTICES);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawPanel() {
    drawRectangle(0.99f, -1.0f, 0.72f, 2.0f, 0.08f, 0.16f, 0.22f);
    drawRectangle(1.04f, 0.73f, 0.61f, 0.20f, 0.12f, 0.29f, 0.36f);
    glColor3f(0.96f, 0.92f, 0.73f);
    drawText(1.09f, 0.85f, "WAREHOUSE NAVIGATOR");
    drawText(1.09f, 0.77f, "Robot Route Simulator");

    glColor3f(0.87f, 0.94f, 0.96f);
    drawText(1.09f, 0.62f, "KEYBOARD MENU");
    drawText(1.09f, 0.51f, "1 - Move Left");
    drawText(1.09f, 0.41f, "2 - Move Right");
    drawText(1.09f, 0.31f, "3 - Move Up");
    drawText(1.09f, 0.21f, "4 - Move Down");
    drawText(1.09f, 0.11f, "5 - Set Step Size [Recommended: 0.01 - 0.20]");
    drawText(1.09f, 0.01f, "6 - Return to Start");
    drawText(1.09f, -0.09f, "7 - Auto-Move Demo");
    drawText(1.09f, -0.19f, "0 - Exit");

    glColor3f(0.96f, 0.92f, 0.73f);
    drawText(1.09f, -0.34f, "STEP SIZE: Press 5 to set");
    drawText(1.09f, -0.44f, "ROBOT: Triangle VBO");

    glColor3f(0.87f, 0.94f, 0.96f);
    drawText(1.09f, -0.57f, "STORAGE ZONES");
    drawRectangle(1.09f, -0.68f, 0.04f, 0.04f, 0.19f, 0.55f, 0.44f);
    drawRectangle(1.09f, -0.77f, 0.04f, 0.04f, 0.76f, 0.54f, 0.24f);
    drawRectangle(1.09f, -0.86f, 0.04f, 0.04f, 0.47f, 0.38f, 0.70f);
    glColor3f(0.95f, 0.96f, 0.98f);
    drawText(1.17f, -0.66f, "Zone A");
    drawText(1.17f, -0.75f, "Zone B");
    drawText(1.17f, -0.84f, "Zone C");

    // Input and status are shown in the warehouse window too.
    drawRectangle(-0.95f, -1.12f, 2.66f, 0.13f, 0.08f, 0.16f, 0.22f);
    glColor3f(0.96f, 0.92f, 0.73f);

    if (enteringStep) {
        drawText(-0.88f, -1.075f, "Step size:");
        drawText(-0.63f, -1.075f, stepInput);
        drawText(-0.22f, -1.075f, "ENTER = Save    ESC = Cancel");

        // Show invalid input feedback above the step-size prompt
        if (message == "Invalid step size. Enter a positive number.") {
            glColor3f(1.0f, 0.45f, 0.40f);
            drawText(-0.88f, -0.96f, message);
        }
    }
    else {
        drawText(-0.88f, -1.075f, message);
    }

}

void display() {
    glClearColor(0.06f, 0.11f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawWarehouse();
    drawRobot();
    drawPanel();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height <= 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.71, -1.14, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void stopAutoMove() {
    autoMove = false;
    timerVersion++; // Old timer callbacks will no longer move the robot.
}

void autoMoveTimer(int version) {
    if (!autoMove || version != timerVersion) return;
    if (autoStage >= 4) {
        stopAutoMove();
        message = "Auto-Move Demo completed.";
        cout << message << endl;
        glutPostRedisplay();
        return;
    }

    float dx = routeX[autoStage] - robotX;
    float dy = routeY[autoStage] - robotY;
    const float AUTO_STEP = 0.04f;
    float nextX = robotX, nextY = robotY;

    // Move along one axis at a time so the route is easy to follow.
    if (fabsf(dx) > 0.001f) {
        float move = AUTO_STEP;
        if (fabsf(dx) < move) move = fabsf(dx);
        if (dx < 0.0f) move = -move;
        nextX += move;
    }
    else if (fabsf(dy) > 0.001f) {
        float move = AUTO_STEP;
        if (fabsf(dy) < move) move = fabsf(dy);
        if (dy < 0.0f) move = -move;
        nextY += move;
    }
    else {
        if (autoStage < 3)
            cout << "Auto-Move: Arrived at Zone " << char('A' + autoStage) << "." << endl;
        else
            cout << "Auto-Move: Returned to start." << endl;

        autoStage++;

        if (autoStage >= 4) {
            stopAutoMove();
            message = "Auto-Move Demo completed.";
            cout << message << endl;
            glutPostRedisplay();
            return;
        }

        glutTimerFunc(60, autoMoveTimer, version);
        return;
    }

    if (autoStage < 4 && !updateRobotPosition(nextX, nextY)) {
        stopAutoMove();
        cout << "Auto-Move stopped because the robot could not move." << endl;
        return;
    }
    if (autoMove && version == timerVersion)
        glutTimerFunc(60, autoMoveTimer, version);
}

void startAutoMove() {
    stopAutoMove();
    autoMove = true;
    autoStage = 0;
    message = "Auto-Move: A -> B -> C -> Start";
    cout << "[7] Auto-Move Demo started: A -> B -> C -> Start." << endl;
    glutPostRedisplay();
    glutTimerFunc(60, autoMoveTimer, timerVersion);
}

void cleanup() {
    stopAutoMove();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &robotVBO);
    glDeleteBuffers(1, &warehouseVBO);
    glDeleteBuffers(1, &warehouseIndexVBO);
}

void keyboard(unsigned char key, int x, int y) {
    (void)x; (void)y;

    if (enteringStep) {
        if (key == 27) {
            enteringStep = false;
            message = "Step size change cancelled.";
            cout << message << endl;
        }
        else if (key == 13) {
            bool valid = (stepLength > 0);
            int dots = 0;
            int digits = 0;
            for (int i = 0; i < stepLength; i++) {
                if (stepInput[i] == '.') dots++;
                else if (stepInput[i] >= '0' && stepInput[i] <= '9') digits++;
                else valid = false;
            }
            if (dots > 1 || digits == 0) valid = false;
            float value = (float)atof(stepInput);
            if (valid && isfinite(value) && value > 0.0f) {
                stepSize = value;
                message = "[5] Step size updated.";
                cout << "[5] Step size updated to " << stepSize << "." << endl;
                enteringStep = false;
            }
            else {
                cout << "Invalid step size. Enter a positive number." << endl;
                message = "Invalid step size. Enter a positive number.";
            }
        }
        else if (key == 8 || key == 127) {
            if (stepLength > 0) stepInput[--stepLength] = '\0';
        }
        else if (stepLength < 20 &&
            ((key >= '0' && key <= '9') || key == '.')) {
            stepInput[stepLength++] = key;
            stepInput[stepLength] = '\0';
        }
        else {
            message = "Invalid step-size character.";
            cout << message << endl;
        }
        glutPostRedisplay();
        return;
    }

    if (key == '0' || key == 27) {
        cout << "[0] Exiting Warehouse Navigator." << endl;
        cleanup();
        exit(0);
    }
    if (key == '5') {
        stopAutoMove();
        enteringStep = true;
        message = "Type a positive step size, then press Enter.";
        stepLength = 0;
        stepInput[0] = '\0';
        cout << "[5] Enter a positive step size in the window, then press Enter." << endl;
        glutPostRedisplay();
        return;
    }
    if (key == '7') {
        if (autoMove) {
            stopAutoMove();
            message = "Auto-Move Demo stopped.";
            cout << message << endl;
            glutPostRedisplay();
        }
        else startAutoMove();
        return;
    }

    if (key >= '1' && key <= '4') {
        stopAutoMove();
        float nextX = robotX, nextY = robotY;
        if (key == '1') nextX -= stepSize;
        if (key == '2') nextX += stepSize;
        if (key == '3') nextY += stepSize;
        if (key == '4') nextY -= stepSize;
        if (updateRobotPosition(nextX, nextY)) {
            if (key == '1') message = "[1] Robot moved left.";
            if (key == '2') message = "[2] Robot moved right.";
            if (key == '3') message = "[3] Robot moved up.";
            if (key == '4') message = "[4] Robot moved down.";
            cout << message << endl;
            glutPostRedisplay();
        }
    }
    else if (key == '6') {
        stopAutoMove();
        if (updateRobotPosition(START_X, START_Y)) {
            message = "[6] Robot returned to start.";
            cout << message << endl;
            glutPostRedisplay();
        }
    }
    else {
        message = "Invalid choice. Use keys 0 to 7.";
        cout << message << endl;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Warehouse Navigator - Robot Route Simulator (MP03)");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "GLEW initialization failed." << endl;
        return 1;
    }
#endif
    initWarehouse();
    initRobot();
    cout << "Warehouse Navigator: Use keys 0 to 7 in the OpenGL window." << endl;
    glutMainLoop();
    return 0;
}
