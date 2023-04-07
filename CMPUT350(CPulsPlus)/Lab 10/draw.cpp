// draw 6 bouncing cubes with changing background color

#include <GL/glut.h>    
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <unistd.h>

extern void draw_cube();

double max_size = 2.0, min_size = -2.0, roation_st = 3.0;

// return uniform random number in [0,1)
double rnd01()
{
  return (double) rand() / (double(RAND_MAX));
}

double col_1 = rnd01(), col_2 = rnd01(), col_3 = rnd01();

void create_new_colors() //create new calues in the range of 0 to 1 to use as arguments for the clear color function
{
  col_1 = rnd01();
  col_2 = rnd01();
  col_3 = rnd01();
  while (col_2 == col_1 || col_2 == col_3)
  {
    col_2 = rnd01();
  }

  while (col_3 == col_1 || col_3 == col_2)
  {
    col_3 = rnd01();
  }
}

double cycle_size(float range)
{
  return (1.0-range)*min_size + (range*max_size);
}

// main drawing function
void draw_scene()
{
  // ... implement

  // if the cube is too big try to move it further away
  // by say glTranslatef(..., ..., -5.0f)
  create_new_colors();
  glClearColor(col_1, col_2, col_3, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ... added
  glMatrixMode(GL_MODELVIEW);
  load_textures();

  //cube 1 middle top
  glPushMatrix();
  glTranslatef(0.0, -3.0, cycle_size(0.4f));
  glRotatef(roation_st, 0.9, 0.8, 1.0);
  draw_cube();
  glPopMatrix();
  
  //cube 2 left top
  glPushMatrix();
  glTranslatef(-6.0, -3.0, cycle_size(0.4f));
  glRotatef(roation_st, 0.9, 0.8, 1.0);
  draw_cube();
  glPopMatrix();
  
  //cube 3 right top
  glPushMatrix();
  glTranslatef(6.0, -3.0, cycle_size(0.4f));
  glRotatef(roation_st, 0.9, 0.8, 1.0);
  draw_cube();
  glPopMatrix();
  
  //cube 4 middle bottom
  glPushMatrix();
  glTranslatef(0.0, 3.0, cycle_size(0.4f));
  glRotatef(roation_st, 0.9, 0.8, 1.0);
  draw_cube();
  glPopMatrix();

  //cube 5 left bottom
  glPushMatrix();
  glTranslatef(-6.0, 3.0, cycle_size(0.4f));
  glRotatef(roation_st, 0.9, 0.8, 1.0);
  draw_cube();
  glPopMatrix();

  //cube 6 right bottom
  glPushMatrix();
  glTranslatef(6.0, 3.0, cycle_size(0.4f));
  glRotatef(roation_st, 0.9, 0.8, 1.0);
  draw_cube();
  glPopMatrix();

  glutSwapBuffers();

  usleep(20*1000); // to make x2go happy which doesn't swap on vsync ... don't remove!
}
