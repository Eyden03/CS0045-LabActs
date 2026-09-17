#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/*
Exercise Q19 - Keyboard Color Picker
  ------------------------------------
 Objective: Practice arrays, keyboard input, and console output with OpenGL rendering.
 This program changes the background between six preset colors using keys 1 through 6.
 */

float colors[6][3] =
{
    {0.70f, 0.50f, 1.00f}, // lavender
    {1.00f, 0.35f, 0.25f}, // coral
    {0.25f, 0.90f, 0.60f}, // mint green
    {1.00f, 0.70f, 0.10f}, // golden yellow
    {0.35f, 0.75f, 1.00f}, // sky blue
    {1.00f, 0.25f, 0.50f}  // rose pink
};

string colorNames[6] =
{
    "Lavender",
    "Coral",
    "Mint Green",
    "Golden Yellow",
    "Sky Blue",
    "Rose Pink"
};

int selectedColor = 0;

void display()
{
    glClearColor(colors[selectedColor][0],
                 colors[selectedColor][1],
                 colors[selectedColor][2],
                 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key >= '1' && key <= '6')
    {
        selectedColor = key - '1';

        cout << "Selected color: "
             << colorNames[selectedColor] << endl;

        glutPostRedisplay();
    }

    if (key == 27)
        {
            exit(0); // ESC key quits
        }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q19 - Keyboard Color Picker");

    cout << "Press keys 1 through 6 to change the background color." << endl;
    cout << "Press ESC to quit." << endl;

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}