
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

/*
 * Machine Problem 01 - Campus Traffic Signal Visualizer
 * -----------------------------------------------------
 * This program displays a traffic light where users can
 * select the active signal using the keyboard menu.
 * The signal shapes are drawn using VBOs and glDrawArrays().
 */

GLuint bodyVBO, lightsVBO;

int signalState = 1; // Red light is active at the start

const int CIRCLE_POINTS = 30;
const int VERTICES_PER_CIRCLE = CIRCLE_POINTS + 2;

// Traffic light body vertices: two triangles forming a rectangle.
GLfloat body[] = {
    // First triangle
    -0.35f,  0.85f, 0.0f, // Top-left point
     0.35f,  0.85f, 0.0f, // Top-right point
     0.35f, -0.85f, 0.0f, // Bottom-right point

    // Second triangle
    -0.35f,  0.85f, 0.0f, // Top-left point
     0.35f, -0.85f, 0.0f, // Bottom-right point
    -0.35f, -0.85f, 0.0f  // Bottom-left point
};

// Each circle is a center followed by points around its edge.
GLfloat lights[VERTICES_PER_CIRCLE * 3 * 3];

void createLights() {
    int index = 0;

    for (int light = 0; light < 3; light++) {
        float y = 0.48f - light * 0.48f;

        // Center point of each light
        lights[index++] = 0.0f;
        lights[index++] = y;
        lights[index++] = 0.0f;

        // Points around the circle
        for (int i = 0; i <= CIRCLE_POINTS; i++) {
            float angle = 2.0f * 3.14159265f * i / CIRCLE_POINTS;

            lights[index++] = 0.23f * cosf(angle);
            lights[index++] = y + 0.23f * sinf(angle);
            lights[index++] = 0.0f;
        }
    }
}

void initBuffers() {
    glGenBuffers(1, &bodyVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bodyVBO);

    // The shapes stay the same, so GL_STATIC_DRAW is used.
    glBufferData(GL_ARRAY_BUFFER, sizeof(body), body, GL_STATIC_DRAW);

    glGenBuffers(1, &lightsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lightsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lights), lights, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f);
    glScalef(0.75f, 0.75f, 1.0f);

    // Draw the traffic light housing.
    glBindBuffer(GL_ARRAY_BUFFER, bodyVBO);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.12f, 0.12f, 0.15f); // Dark gray housing
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Draw the three circle-like indicators.
    glBindBuffer(GL_ARRAY_BUFFER, lightsVBO);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    // Set colors
    const GLfloat colors[3][3] = {
        {1.0f, 0.0f, 0.0f}, // Red - Stop
        {1.0f, 0.8f, 0.0f}, // Yellow - Caution
        {0.0f, 1.0f, 0.0f}  // Green - Go
    };

    for (int light = 0; light < 3; light++) {
        if (signalState == light + 1)
            glColor3fv(colors[light]);
        else
            glColor3f(0.18f, 0.18f, 0.18f); // Inactive light

        glDrawArrays(
            GL_TRIANGLE_FAN,
            light * VERTICES_PER_CIRCLE,
            VERTICES_PER_CIRCLE
        );
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glPopMatrix();

    // Menu
    glColor3f(0.0f, 0.0f, 0.0f);

    const char* menu[] = {
        "1: Red   2: Yellow   3: Green",
        "4: All Off   5: Reset   0: Exit"
    };

    for (int row = 0; row < 2; row++) {
        glRasterPos2f(-0.8f, -0.65f - row * 0.12f);

        for (const char* text = menu[row]; *text; text++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
    }

    glFlush();
}



void keyboard(unsigned char key, int, int) {
    if (key == '0' || key == 27) {
        cout << "Exiting Campus Traffic Signal Visualizer." << endl;

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &bodyVBO);
        glDeleteBuffers(1, &lightsVBO);
        exit(0);
    }

    if (key >= '1' && key <= '3') {
        signalState = key - '0';

        if (signalState == 1)
            cout << " [1] Red Light - Stop" << endl;
        else if (signalState == 2)
            cout << " [2] Yellow Light - Caution" << endl;
        else
            cout << " [3] Green Light - Go" << endl;

        glutPostRedisplay();
    }
    else if (key == '4') {
        signalState = 4; // All lights off
        cout << " [4] All traffic lights are now off." << endl;
        glutPostRedisplay();
    }
    else if (key == '5') {
        signalState = 1; // Reset to red light
        cout << " [5] Traffic light reset to Red - Stop." << endl;
        glutPostRedisplay();
    }
    else {
        cout << "Invalid choice. Please select 0 to 5." << endl;
    }
}




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Campus Traffic Signal Visualizer (MP01)");

    glClearColor(0.85f, 0.88f, 0.92f, 1.0f);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    createLights();

#ifndef __APPLE__
    GLenum err = glewInit();
    if (err == GLEW_OK) {
        initBuffers();
        glutMainLoop();
    }
#else
    initBuffers();
    glutMainLoop();
#endif
    return 0;
}
