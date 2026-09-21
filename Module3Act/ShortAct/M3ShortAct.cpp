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
 M3 Short Task - Student Portal Schedule
 */


// helper func to render strings charac
void drawBitmapString(void* font, const char* str) {
    for (const char* c = str; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}


// helper func for drawing text
void drawText(float x, float y, void* font, const char* text) {
    glRasterPos2f(x, y);
    drawBitmapString(font, text);
}


// helper func for drawing filled rectangles
void drawRectangle(float left, float bottom,
                   float right, float top) {
    glBegin(GL_POLYGON);
        glVertex2f(left, bottom);
        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
    glEnd();
}


void display() {
    glClearColor(0.94f, 0.96f, 0.94f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // top header
    glColor3f(0.02f, 0.25f, 0.15f);
    drawRectangle(-1.0f, 0.79f, 1.0f, 1.0f);

    glColor3f(1.0f, 0.78f, 0.10f);
    drawText(-0.94f, 0.90f, GLUT_BITMAP_TIMES_ROMAN_24,
             "SOLAR STUDENT PORTAL");

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.94f, 0.83f, GLUT_BITMAP_HELVETICA_18,
             "Class Schedule and Student Information");


    // student information panel
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(-0.97f, 0.37f, 0.97f, 0.75f);

    // student information panel heading
    glColor3f(0.08f, 0.45f, 0.27f);
    drawRectangle(-0.97f, 0.67f, 0.97f, 0.75f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(-0.94f, 0.70f, GLUT_BITMAP_HELVETICA_18,
             "STUDENT INFORMATION");


    // left-side student information
    glColor3f(0.08f, 0.10f, 0.09f);

    drawText(-0.94f, 0.61f, GLUT_BITMAP_HELVETICA_18,
             "Enrollment Status: ENROLLED");

    drawText(-0.94f, 0.54f, GLUT_BITMAP_HELVETICA_18,
             "Student Number: 202410089");

    drawText(-0.94f, 0.47f, GLUT_BITMAP_HELVETICA_18,
             "Name: POCSIDIO, AIDHEN ANGEL MANDAP");

    drawText(-0.94f, 0.40f, GLUT_BITMAP_HELVETICA_18,
             "Phone: 09612956602     Zip Code: 2016");


    // right-side student information
    drawText(0.02f, 0.61f, GLUT_BITMAP_HELVETICA_18,
             "College: COMPUTER STUDIES");

    drawText(0.54f, 0.61f, GLUT_BITMAP_HELVETICA_18,
             "Program: BSCSSE");

    drawText(0.02f, 0.54f, GLUT_BITMAP_HELVETICA_18,
             "Year Level: 3");

    drawText(0.30f, 0.54f, GLUT_BITMAP_HELVETICA_18,
             "1st Term, SY 26-27");

    drawText(0.02f, 0.47f, GLUT_BITMAP_HELVETICA_18,
             "Address: 883 Quezon Blvd., Sta. Cruz, Manila");

    drawText(0.02f, 0.40f, GLUT_BITMAP_HELVETICA_18,
             "Classification: Regular Student");


    // schedule heading
    glColor3f(0.82f, 0.60f, 0.08f);
    drawRectangle(-0.97f, 0.24f, 0.97f, 0.34f);

    glColor3f(0.05f, 0.12f, 0.08f);
    drawText(-0.94f, 0.275f, GLUT_BITMAP_HELVETICA_18,
             "CLASS SCHEDULE");


    // table column header
    glColor3f(0.02f, 0.25f, 0.15f);
    drawRectangle(-0.97f, 0.13f, 0.97f, 0.23f);

    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(-0.95f, 0.165f, GLUT_BITMAP_HELVETICA_18,
             "Course");

    drawText(-0.79f, 0.165f, GLUT_BITMAP_HELVETICA_18,
             "Title");

    drawText(0.10f, 0.165f, GLUT_BITMAP_HELVETICA_18,
             "Section");

    drawText(0.27f, 0.165f, GLUT_BITMAP_HELVETICA_18,
             "Units");

    drawText(0.38f, 0.165f, GLUT_BITMAP_HELVETICA_18,
             "Days");

    drawText(0.52f, 0.165f, GLUT_BITMAP_HELVETICA_18,
             "Time");

    drawText(0.82f, 0.165f, GLUT_BITMAP_HELVETICA_18,
             "Room");


    // Table rows
    glColor3f(0.10f, 0.12f, 0.11f);

    // Row 1
    drawText(-0.95f, 0.08f, GLUT_BITMAP_HELVETICA_12,
             "CS0011");
    drawText(-0.79f, 0.08f, GLUT_BITMAP_HELVETICA_12,
             "MOBILE PROGRAMMING");
    drawText(0.12f, 0.08f, GLUT_BITMAP_HELVETICA_12,
             "TN35");
    drawText(0.29f, 0.08f, GLUT_BITMAP_HELVETICA_12,
             "3");
    drawText(0.38f, 0.08f, GLUT_BITMAP_HELVETICA_12,
             "M / W");
    drawText(0.51f, 0.08f, GLUT_BITMAP_HELVETICA_12,
             "11:00-12:50");
    drawText(0.82f, 0.08f, GLUT_BITMAP_HELVETICA_12,
             "F608 / F1209");


    // Row 2
    glColor3f(0.88f, 0.92f, 0.88f);
    drawRectangle(-0.97f, -0.03f, 0.97f, 0.04f);

    glColor3f(0.10f, 0.12f, 0.11f);
    drawText(-0.95f, -0.005f, GLUT_BITMAP_HELVETICA_12,
             "CS0016");
    drawText(-0.79f, -0.005f, GLUT_BITMAP_HELVETICA_12,
             "NETWORK AND COMMUNICATIONS 2A");
    drawText(0.12f, -0.005f, GLUT_BITMAP_HELVETICA_12,
             "TN31");
    drawText(0.29f, -0.005f, GLUT_BITMAP_HELVETICA_12,
             "3");
    drawText(0.38f, -0.005f, GLUT_BITMAP_HELVETICA_12,
             "T / TH");
    drawText(0.51f, -0.005f, GLUT_BITMAP_HELVETICA_12,
             "09:00-10:50");
    drawText(0.82f, -0.005f, GLUT_BITMAP_HELVETICA_12,
             "ONLINE / F1101");


    // Row 3
    drawText(-0.95f, -0.09f, GLUT_BITMAP_HELVETICA_12,
             "CS0019");
    drawText(-0.79f, -0.09f, GLUT_BITMAP_HELVETICA_12,
             "MODELING AND SIMULATION");
    drawText(0.12f, -0.09f, GLUT_BITMAP_HELVETICA_12,
             "TN35");
    drawText(0.29f, -0.09f, GLUT_BITMAP_HELVETICA_12,
             "3");
    drawText(0.38f, -0.09f, GLUT_BITMAP_HELVETICA_12,
             "F / T");
    drawText(0.51f, -0.09f, GLUT_BITMAP_HELVETICA_12,
             "11:00-12:50");
    drawText(0.82f, -0.09f, GLUT_BITMAP_HELVETICA_12,
             "ONLINE / ONLINE");


    // Row 4
    glColor3f(0.88f, 0.92f, 0.88f);
    drawRectangle(-0.97f, -0.20f, 0.97f, -0.13f);

    glColor3f(0.10f, 0.12f, 0.11f);
    drawText(-0.95f, -0.175f, GLUT_BITMAP_HELVETICA_12,
             "CS0025");
    drawText(-0.79f, -0.175f, GLUT_BITMAP_HELVETICA_12,
             "SOFTWARE ENGINEERING 1");
    drawText(0.12f, -0.175f, GLUT_BITMAP_HELVETICA_12,
             "TN35");
    drawText(0.29f, -0.175f, GLUT_BITMAP_HELVETICA_12,
             "3");
    drawText(0.38f, -0.175f, GLUT_BITMAP_HELVETICA_12,
             "F / TH");
    drawText(0.51f, -0.175f, GLUT_BITMAP_HELVETICA_12,
             "15:00-16:50");
    drawText(0.82f, -0.175f, GLUT_BITMAP_HELVETICA_12,
             "ONLINE / E609");


    // Row 5
    drawText(-0.95f, -0.26f, GLUT_BITMAP_HELVETICA_12,
             "CS0045");
    drawText(-0.79f, -0.26f, GLUT_BITMAP_HELVETICA_12,
             "CS ELECTIVE - COMPUTER GRAPHICS");
    drawText(0.12f, -0.26f, GLUT_BITMAP_HELVETICA_12,
             "TN35");
    drawText(0.29f, -0.26f, GLUT_BITMAP_HELVETICA_12,
             "3");
    drawText(0.38f, -0.26f, GLUT_BITMAP_HELVETICA_12,
             "M / TH");
    drawText(0.51f, -0.26f, GLUT_BITMAP_HELVETICA_12,
             "13:00-14:50");
    drawText(0.82f, -0.26f, GLUT_BITMAP_HELVETICA_12,
             "E601 / E610");


    // Row 6
    glColor3f(0.88f, 0.92f, 0.88f);
    drawRectangle(-0.97f, -0.37f, 0.97f, -0.30f);

    glColor3f(0.10f, 0.12f, 0.11f);
    drawText(-0.95f, -0.345f, GLUT_BITMAP_HELVETICA_12,
             "CS0053");
    drawText(-0.79f, -0.345f, GLUT_BITMAP_HELVETICA_12,
             "PROGRAMMING TOOLS AND TECHNIQUES");
    drawText(0.12f, -0.345f, GLUT_BITMAP_HELVETICA_12,
             "TN35");
    drawText(0.29f, -0.345f, GLUT_BITMAP_HELVETICA_12,
             "3");
    drawText(0.38f, -0.345f, GLUT_BITMAP_HELVETICA_12,
             "M / TH");
    drawText(0.51f, -0.345f, GLUT_BITMAP_HELVETICA_12,
             "07:00-08:50");
    drawText(0.82f, -0.345f, GLUT_BITMAP_HELVETICA_12,
             "F702 / F609");


    // Row 7
    drawText(-0.95f, -0.43f, GLUT_BITMAP_HELVETICA_12,
             "GED0073");
    drawText(-0.79f, -0.43f, GLUT_BITMAP_HELVETICA_12,
             "GE ELECTIVE 2");
    drawText(0.12f, -0.43f, GLUT_BITMAP_HELVETICA_12,
             "TW43");
    drawText(0.29f, -0.43f, GLUT_BITMAP_HELVETICA_12,
             "3");
    drawText(0.38f, -0.43f, GLUT_BITMAP_HELVETICA_12,
             "S / W");
    drawText(0.51f, -0.43f, GLUT_BITMAP_HELVETICA_12,
             "07:00-08:50");
    drawText(0.82f, -0.43f, GLUT_BITMAP_HELVETICA_12,
             "E601 / E601");


    // total units panel
    glColor3f(0.02f, 0.25f, 0.15f);
    drawRectangle(-0.97f, -0.58f, 0.97f, -0.49f);

    glColor3f(1.0f, 0.78f, 0.10f);
    drawText(-0.94f, -0.55f, GLUT_BITMAP_HELVETICA_18,
             "TOTAL UNITS: 21");


    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("M3 ShortAct - Student Portal");

    glutFullScreen();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}