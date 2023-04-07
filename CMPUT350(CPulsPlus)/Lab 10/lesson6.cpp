/*
  This code was created by Jeff Molofee '99 (ported to Linux/GLUT by
  Richard Campbell '99)

  If you've found this code useful, please let me know

  Visit me at www.demonews.com/hosted/nehe 
  (email Richard Campbell at ulmont@bellsouth.net)

  cosmetic changes by mic
*/
#include <GL/glut.h>   // header File For The GLUT Library 
#include <GL/gl.h>     // header File For The OpenGL32 Library
#include <GL/glu.h>    // header File For The GLu32 Library
#include <cstdio>      // header file for standard file i/o
#include <iostream>

using namespace std;

// ASCII code for the escape key
const int ESCAPE = 27;

// the number of our GLUT window
int window; 

// floats for x rotation, y rotation, z rotation
float xrot, yrot, zrot;

// storage for one texture
GLuint texture[1];

using uint4 = unsigned int;
using uint2 = unsigned short;

// Image type
struct Image
{
  uint4 sizeX;
  uint4 sizeY;
  char *data;

  Image() { sizeX = sizeY = 0; data = nullptr; }
  ~Image() { delete [] data; }
};

/*
   quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane
   only.  See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more
   info
*/
int ImageLoad(const char *filename, Image &image)
{
  FILE *file;
  uint4 size;   // size of the image in bytes
  uint4 i;      // standard counter
  uint2 planes; // number of planes in image (must be 1) 
  uint2 bpp;    // number of bits per pixel (must be 24)
  char temp;    // temporary color storage for bgr-rgb conversion

  const int sizeof_xy = 4;
  const int sizeof_planes = 2;
  const int sizeof_bpp = 2;
  
  // make sure the file is there
  if ((file = fopen(filename, "rb")) == nullptr) {
    cout << "File Not Found : " << filename << endl;
    return 0;
  }
    
  // seek through the bmp header, up to the width/height:
  fseek(file, 18, SEEK_CUR);

  // read the width
  static_assert(sizeof(image.sizeX) == sizeof_xy, "sizeof sizeX ?");

  if ((i = fread(&image.sizeX, sizeof_xy, 1, file)) != 1) {
    cout << "Error reading width from " << filename << endl;
    return 0;
  }
  cout << "Width of " << filename << " : " << image.sizeX << endl;
    
  // read the height 
  static_assert(sizeof(image.sizeY) == sizeof_xy, "sizeof sizeY ?");

  if ((i = fread(&image.sizeY, sizeof_xy, 1, file)) != 1) {
    cout << "Error reading height from " << filename << endl;
    return 0;
  }
  cout << "Height of " << filename << " : " << image.sizeY << endl;
    
  // calculate the size (assuming 24 bits or 3 bytes per pixel)
  size = image.sizeX * image.sizeY * 3;

  // read the planes
  static_assert(sizeof(planes) == sizeof_planes, "sizeof planes ?");

  if ((fread(&planes, sizeof_planes, 1, file)) != 1) {
    cout << "Error reading planes from " << filename << endl;
    return 0;
  }
  if (planes != 1) {
    cout << "Planes from " << filename << " is not 1: " << planes << endl;
    return 0;
  }

  // read the bpp
  static_assert(sizeof(bpp) == sizeof_bpp, "sizeof bpp ?");

  if ((i = fread(&bpp, sizeof_bpp, 1, file)) != 1) {
    cout << "Error reading bpp from " << filename << endl;
    return 0;
  }
  if (bpp != 24) {
    cout << "Bpp from " << filename << " %s is not 24: " << bpp << endl;
    return 0;
  }
	
  // seek past the rest of the bitmap header
  fseek(file, 24, SEEK_CUR);

  // read the data
  image.data = new char[size];

  if ((i = fread(image.data, size, 1, file)) != 1) {
    cout << "Error reading image data from " << filename << endl;
    return 0;
  }

  for (i=0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
    temp = image.data[i];
    image.data[i] = image.data[i+2];
    image.data[i+2] = temp;
  }
    
  // we're done
  return 1;
}
    
// Load Bitmaps And Convert To Textures
void LoadGLTextures()
{	
  // Load Texture
  Image image1;

  if (!ImageLoad("Data/lesson6/NeHe.bmp", image1)) {
    exit(1);
  }        

  // Create Texture	
  glGenTextures(1, &texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture

  // scale linearly when image bigger than texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // scale linearly when image smaller than texture  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

  /*
    2d texture, level of detail 0 (normal), 3 components (red, green, blue),
    x size from image, y size from image, border 0 (normal), rgb color data,
    unsigned byte data, and finally the data itself
  */
  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1.sizeX, image1.sizeY, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image1.data);
};

// initialize view
void init_view(int Width, int Height)
{
  // reset the current viewport and perspective transformation  
  glViewport(0, 0, Width, Height); 

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();			// Reset The Projection Matrix

  // Calculate The Aspect Ratio Of The Window    
  gluPerspective(45.0f, (GLfloat)Width/(GLfloat)Height, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

// A general OpenGL initialization function.  Sets all of the initial parameters
void init(int Width, int Height)	// We call this right after our OpenGL
                                        // window is created
{
  LoadGLTextures();			// Load The Texture(s) 
  glEnable(GL_TEXTURE_2D);		// Enable Texture Mapping
  glClearColor(0.0f, 0.0f, 1.0f, 0.0f);	// Clear The Background Color To Blue 
  glClearDepth(1.0);			// all z values will be cleared
  glDepthFunc(GL_LESS);			// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
  glShadeModel(GL_SMOOTH);		// Enables Smooth Color Shading

  init_view(Width, Height);
}

/*
  The function called when our window is resized (which shouldn't
  happen, because we're fullscreen)
*/
void resize(int Width, int Height)
{
  if (Height == 0) { // prevent a divide by zero if the window is too small
    Height = 1;
  }

  init_view(Width, Height);
}

// The main drawing function.
void display()
{
  // clear the screen and the depth buffer

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
  glLoadIdentity();                           // reset modelview matrix

  glTranslatef(0.0f, 0.0f, -5.0f);            // move 5 units into the screen
    
  glRotatef(xrot, 1.0f, 0.0f, 0.0f);          // rotate on the x axis
  glRotatef(yrot, 0.0f, 1.0f, 0.0f);          // rotate on the Y axis
  glRotatef(zrot, 0.0f, 0.0f, 1.0f);          // rotate on the Z axis

  glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use

  glBegin(GL_QUADS);                          // begin drawing a cube
    
  // front face
  // (note that the texture's corners have to match the quad's corners)

  // bottom left 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  // bottom right   
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  // top right   
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  // top left   
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f); 
    
  // back face

  // bottom right   
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  // top right   
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  // top Left   
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  // bottom Left   
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); 
	
  // top face

  // top Left   
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
  // bottom Left   
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  // bottom right   
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  // top right   
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f); 
    
  // bottom face

  // top right   
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  // top Left   
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  // bottom Left   
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
  // bottom right   
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f); 
    
  // right face

  // bottom right   
  glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
  // top right   
  glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
  // top Left   
  glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
  // bottom Left   
  glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f); 
    
  // left face

  // bottom left 
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
  // bottom right 
  glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
  // top right 
  glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
  // top Left 
  glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f); 
    
  glEnd();       // done with the polygon

  xrot += 0.05f; // x axis rotation	
  yrot += 0.1f;	 // y axis rotation
  zrot += 0.07f; // z axis rotation

  // since this is double buffered, swap the buffers to display what just got
  // drawn
  glutSwapBuffers();
}

// The function called whenever a key is pressed.
void key_pressed(unsigned char key, int x, int y) 
{
  // if escape is pressed, kill everything
  if (key == ESCAPE) { 
    // shut down our window
    glutDestroyWindow(window); 
      
    // exit the program...normal termination
    exit(0);                   
  }
}

int main(int argc, char **argv) 
{  
  /* Initialize GLUT state - glut will take any command line arguments
     that pertain to it or X Windows - look at its documentation at
     http://reality.sgi.com/mjk/spec3/spec3.html
  */  
  glutInit(&argc, argv);  

  /* Select type of Display mode:   
     RGBA color
     Double buffer 
     Alpha components supported 
     Depth buffer
  */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  // get a window
  int W = 1000, H = 750;
  glutInitWindowSize(W, H);  

  // the window starts at the upper left corner of the screen
  glutInitWindowPosition(0, 0);  

  // open a window
  window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");  

  // Register the function to do all our OpenGL drawing
  glutDisplayFunc(display);  

  // go fullscreen.  This is as soon as possible
  // !!! mic: was  glutFullScreen();

  // even if there are no events, redraw our gl scene
  glutIdleFunc(display);

  // register the function called when our window is resized
  glutReshapeFunc(resize);

  // register the function called when the keyboard is pressed
  glutKeyboardFunc(key_pressed);

  // initialize our window
  init(W, H);
  
  // start event processing engine
  glutMainLoop();  

  return 0;
}
