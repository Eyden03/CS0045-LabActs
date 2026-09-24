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
 * Example 05 - Stroke Font Text 
 * ------------------------------------ 
 * Concept: Unlike bitmap fonts (fixed-size pixel stamps), 
GLUT_STROKE_ROMAN 
 * is a vector font drawn with line segments via 
glutStrokeCharacter. Because 
 * it is made of real geometry, it can be scaled and 
transformed like any 
 * other primitive using glScalef/glTranslatef - useful for 
zoomable or 3D text. 
 */ 
 
void display() { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glColor3f(0.3f, 0.9f, 1.0f); 
     
    // Optional: Set line width so stroke characters are clearly visible 
    glLineWidth(2.0f); 
 
    glPushMatrix(); 
        glTranslatef(-0.8f, -0.1f, 0.0f); 
        glScalef(0.0015f, 0.0015f, 1.0f);  // stroke fonts are defined in large units; scale down 
        const char* msg = "STROKE FONT"; 
        for (const char* c = msg; *c != '\0'; c++) { 
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); 
        } 
    glPopMatrix(); 
 
    glFlush(); 
} 
 
int main(int argc, char** argv) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(600, 300);
glutCreateWindow("Ex05 - Stroke Font (Vector) Text"); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
}
