// CMPUT 350 Lab Exercise 10
//
// Bouncing Cubes
//
// This code is based on Jeff Molofee's NeHe tutorial code
// (ported to Linux/GLUT by Richard Campbell '99)
//
// DON'T CHANGE THIS FILE !
//
#include <GL/glut.h>    
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <cstdio>       
#include <cstdlib>      
#include <unistd.h>     
#include <cassert>

// to be implemented in draw.cpp
extern void draw_scene();

// ASCII code for the escape key
const int ESCAPE = 27;

// the number of our GLUT window
int window; 

// storage for one texture
GLuint texture[1];

// Image type - contains height, width, and data
struct Image
{
  unsigned int sizeX;
  unsigned int sizeY;
  char *data;
};

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only. See
// http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int load_image(const char *filename, Image *image)
{
  FILE *file;
  unsigned long size;        // size of the image in bytes.
  unsigned long i;           // standard counter.
  unsigned short int planes; // number of planes in image (must be 1) 
  unsigned short int bpp;    // number of bits per pixel (must be 24)
  char temp;                 // temporary color storage for bgr-rgb conversion.

  // make sure the file is there.
  if ((file = fopen(filename, "rb")) == nullptr) {
    printf("File Not Found : %s\n",filename);
    return 0;
  }
    
  // seek through the bmp header, up to the width/height:
  fseek(file, 18, SEEK_CUR);

  // read the width
  assert(sizeof(image->sizeX) == 4);
  if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
    printf("Error reading width from %s.\n", filename);
    return 0;
  }
  printf("Width of %s: %d\n", filename, image->sizeX);
    
  // read the height
  assert(sizeof(image->sizeY) == 4);  
  if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
    printf("Error reading height from %s.\n", filename);
    return 0;
  }
  printf("Height of %s: %d\n", filename, image->sizeY);
    
  // calculate the size (assuming 24 bits or 3 bytes per pixel).
  size = image->sizeX * image->sizeY * 3;

  // read the planes
  assert(sizeof(planes) == 2);  
  if ((fread(&planes, 2, 1, file)) != 1) {
    printf("Error reading planes from %s.\n", filename);
    return 0;
  }
  if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, planes);
    return 0;
  }

  // read the bpp
  assert(sizeof(bpp) == 2);  
  if ((i = fread(&bpp, 2, 1, file)) != 1) {
    printf("Error reading bpp from %s.\n", filename);
    return 0;
  }
  if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    return 0;
  }
	
  // seek past the rest of the bitmap header.
  fseek(file, 24, SEEK_CUR);

  // read the data. 
  image->data = new char[size];
  if (!image->data) {
    printf("Error allocating memory for color-corrected image data");
    return 0;	
  }

  if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return 0;
  }

  for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] = temp;
  }
    
  // we're done.
  return 1;
}
    
// Load Bitmaps And Convert To Textures
void load_textures()
{	
  // Load Texture
  Image *image1;
    
  // allocate space for texture
  image1 = new Image;
  if (!image1) {
    printf("Error allocating space for image");
    exit(0);
  }

  if (!load_image("NeHe.bmp", image1)) {
    exit(1);
  }        

  // Create Texture	
  glGenTextures(1, &texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

  // scale linearly when image bigger than texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // scale linearly when image smaller than texture  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  // 2d texture, level of detail 0 (normal), 3 components (red, green,
  // blue), x size from image, y size from image,
  // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image1->data);
};

// The function called when our window is resized
void resize_scene(int width, int height)
{
  if (height <= 0) {
    // Prevent A Divide By Zero If The Window Is Too Small
    height = 1;
  }

  glViewport(0, 0, width, height); // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

// A general OpenGL initialization function.  Sets all of the initial
// parameters.  We call this right after our OpenGL window is created.
void init(int width, int height)	
{
  load_textures();			// Load The Texture(s) 
  glEnable(GL_TEXTURE_2D);		// Enable Texture Mapping
  glClearColor(0.0f, 0.5f, 0.0f, 0.0f);	// Clear The Background Color To Green 
  glClearDepth(1.0);			// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
  glShadeModel(GL_SMOOTH);		// Enables Smooth Color Shading

  resize_scene(width, height);
}

void draw_cube()
{
  glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
  glBegin(GL_QUADS);                          // begin drawing a cube
    
  // Front Face (note that the texture's corners have to match the quad's
  // corners)

  // Bottom Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  // Bottom Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  // Top Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  // Top Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); 
    
  // Back Face

  // Bottom Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  // Top Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  // Top Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  // Bottom Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); 
	
  // Top Face

  // Top Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  // Bottom Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  // Bottom Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  // Top Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); 
    
  // Bottom Face

  // Top Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  // Top Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  // Bottom Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  // Bottom Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); 
    
  // Right face

  // Bottom Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  // Top Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  // Top Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  // Bottom Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); 
    
  // Left Face

  // Bottom Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  // Bottom Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  // Top Right Of The Texture and Quad  
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  // Top Left Of The Texture and Quad  
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); 
    
  glEnd();       // done with the polygon.
}

// The function called whenever a key is pressed.
void key_pressed(unsigned char key, int /*x*/, int /*y*/) 
{
  // avoid thrashing this procedure
  usleep(100);

  // If escape is pressed, kill everything.
  if (key == ESCAPE) { 
    // shut down our window
    glutDestroyWindow(window); 
      
    // exit the program...normal termination.
    exit(0);                   
  }
}

int main(int argc, char **argv) 
{  
  /* Initialize GLUT state - glut will take any command line arguments
     that pertain to it or X Windows - look at its documentation at
     http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);  

  /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);  

  // get a window
  int W = 800, H = 600;
  glutInitWindowSize(W, H);  

  // the window starts at the upper left corner of the screen
  glutInitWindowPosition(0, 0);  

  // Open a window
  window = glutCreateWindow("CMPUT 350 Lab Exercise 10");  

  // Register the function to do all our OpenGL drawing.
  glutDisplayFunc(&draw_scene);  

  // Go fullscreen.  This is as soon as possible.
  // !!! mic: was  glutFullScreen();

  // Even if there are no events, redraw our gl scene.
  glutIdleFunc(&draw_scene);

  // Register the function called when our window is resized.
  glutReshapeFunc(&resize_scene);

  // Register the function called when the keyboard is pressed.
  glutKeyboardFunc(&key_pressed);

  // Initialize our window.
  init(W, H);
  
  // Start Event Processing Engine
  glutMainLoop();  
  return 0;
}
