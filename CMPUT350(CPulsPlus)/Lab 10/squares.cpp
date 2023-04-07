/* draw object copies using transformations
   based on ex2.c

   keys: u d l r q
*/

#include <GL/gl.h>
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

float x_angle = 0, y_angle = 0;

void init()
{
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST); // ... added
  glLoadIdentity();
  glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0); // view box
}


// don't change
void draw_shape()
{
  glBegin(GL_QUADS);
  glColor3f(0.0, 0.0, 1.0);    // blue center square
  glVertex3f(-3.0, -3.0, 0.0);
  glVertex3f(3.0, -3.0, 0.0);
  glVertex3f(3.0, 3.0, 0.0);
  glVertex3f(-3.0, 3.0, 0.0);
  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3f(1.0, 0.0, 0.0);  // now draw the four triangles
  glVertex3f(0.0, 6.5, 0.0); // with color gradient
  glColor3f(0.0, 0.0, 0.9);
  glVertex3f(-3.0, 3.0, 0.0);
  glVertex3f(3.0, 3.0, 0.0);

  glColor3f(0.0, 0.0, 0.9);
  glVertex3f(-3.0, -3.0, 0.0);
  glVertex3f(-3.0, 3.0, 0.0);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(-6.5, 0.0, 0.0);

  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, -6.5, 0.0);
  glColor3f(0.0, 0.0, 0.9);
  glVertex3f(3.0, -3.0, 0.0);
  glVertex3f(-3.0, -3.0, 0.0);

  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(6.5, 0.0, 0.0);
  glColor3f(0.0, 0.0, 0.9);
  glVertex3f(3.0, 3.0, 0.0);
  glVertex3f(3.0, -3.0, 0.0);
  glEnd();
}

/* changes to implement:

   step 1: call draw_shape 3 times [ consider using glPushMatrix() and glPopMatrix() ]
   step 2: honour x_angle, y_angle
   step 3: enable depth test in init() and clear depth buffer in display() 
   step 4: color background yellow in display()
*/
void display()
{
  // ... change and implemented
  
  glClearColor(1.0, 1.0, 0.0, 0.0); // ... yellow
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ... added
  glMatrixMode(GL_MODELVIEW);

  // save modelwview matrix
  glPushMatrix();
  // centered
  // apply rotations
  glRotatef(x_angle, 1.0, 0.0, 0.0);
  glRotatef(y_angle, 0.0, 1.0, 0.0);
  draw_shape();
  // restore it
  glPopMatrix();

  glPushMatrix();
  // then move left
  glTranslatef(-8.0, 0.0, 0.0);
  // first apply rotations  
  glRotatef(x_angle, 1.0, 0.0, 0.0);
  glRotatef(y_angle, 0.0, 1.0, 0.0);
  draw_shape();
  glPopMatrix();

  glPushMatrix();
  // then move right
  glTranslatef(+8.0, 0.0, 0.0);
  // first apply rotations  
  glRotatef(x_angle, 1.0, 0.0, 0.0);
  glRotatef(y_angle, 0.0, 1.0, 0.0);
  draw_shape();
  glPopMatrix();

  glutSwapBuffers(); // double buffered
}


/* this is the keyboard event handler the x and y parameters are the mouse
   coordintes when the key was struck
 
   adjust angle and redraw
*/
void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  switch (key) {
  case 'u':
  case 'U':
    // ... implemented
    x_angle += 3.0; // rotate up
  break;
  case 'd':
  case 'D':
    x_angle -= 3.0; // rotate down
  break;
  case 'l':
  case 'L':
    y_angle += 3.0; // rotate left
  break;
  case 'r':
  case 'R':
    y_angle += -3.0; // rotate right
  break;
  case 'q':
    exit(0); // quit program
  }
  display(); // repaint the window
}

int main (int argc, char **argv)
{
  cout << "keys: u d l r q" << endl;
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(50, 50);
  glutCreateWindow("Object Copies");
  init();
  glutDisplayFunc(display);    // screen refresh function
  glutKeyboardFunc(keyboard);  // set keyboard handler
  glutMainLoop();
  return 0;
}
