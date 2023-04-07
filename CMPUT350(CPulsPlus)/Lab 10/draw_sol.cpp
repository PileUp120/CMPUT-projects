#include <GL/glut.h>    
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <unistd.h>

extern void draw_cube();

float rot_speed = 10;

// size scaling
float scale_min = 0.2;
float scale_max = 0.41;
float scale = scale_max;
// 60 steps to go from max to min
float dscale = (scale_max - scale_min) / 60;
  
// floats for x rotation, y rotation, z rotation
float xrot, yrot, zrot;

// current background color target
float red, green, blue;
// color deltas
float d_red, d_green, d_blue;
// current step
int cstep = 0;
// number of steps until next color is reached
int csteps = 100;

// return uniform random number in [0,1]
double rnd01()
{
  return (double) rand() / (double(RAND_MAX));
}

// main drawing function
void draw_scene()
{
  // background color
  
  if (cstep-- > 0) {

    red   += d_red;
    green += d_green;
    blue  += d_blue;

  } else {

    // new color
    // set up linear interpolation
    cstep = csteps;

    float new_red   = rnd01();
    float new_green = rnd01();
    float new_blue  = rnd01();

    d_red   = (new_red   - red)  /csteps;
    d_green = (new_green - green)/csteps;
    d_blue  = (new_blue  - blue) /csteps;
  }

  // clear The Screen And The Depth Buffer

  glClearColor(red, green, blue, 0.0f);	// Clear The Background Color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Reset The View

  // draw 6 cubes with varying angles and sizes
  
  float X0 = -1.5, X1 = 1.5;
  float Y0 = -1, Y1 = 1;
  int NX = 3, NY = 2;
  float DX = (X1-X0)/(NX-1);
  float DY = (Y1-Y0)/(NY-1);

  for (int y=0; y < NY; ++y) {
    for (int x=0; x < NX; ++x) {
      glPushMatrix();
      glTranslatef(X0 + x * DX, Y0 + y * DY, -5.0f);
      glScalef(scale, scale, scale);
      glRotatef(xrot, 1.0f, 0.0f, 0.0f); // Rotate On The X Axis
      glRotatef(yrot, 0.0f, 1.0f, 0.0f); // Rotate On The Y Axis
      glRotatef(zrot, 0.0f, 0.0f, 1.0f); // Rotate On The Z Axis
      draw_cube();
      glPopMatrix();
    }
  }

  // advance angles semi randomly
  xrot += rot_speed*0.05f; 	
  yrot += rot_speed*0.1f;  
  zrot += rot_speed*0.07f;

  scale += dscale;

  // clip scale and change direction when clipped
  if (scale < scale_min) {
    dscale = -dscale;
    scale = scale_min;
  }

  if (scale > scale_max) {
    dscale = -dscale;
    scale = scale_max;
  }
  
  // swap the buffers to display what just got drawn.
  glutSwapBuffers();

  usleep(20*1000); // to make x2go happy which doesn't swap on vsync ... don't remove!
}
