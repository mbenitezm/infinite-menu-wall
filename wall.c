// C libraries
#ifndef SCREENCASTS
#define SCREENCASTS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#endif

/* ============== COLOR LIST METHODS ============== */

#define MAXSIZE 100
#define RGBSIZE 3

float right[MAXSIZE][RGBSIZE];
float left[MAXSIZE][RGBSIZE];

/* List globals */
float currentRed;
float currentGreen;
float currentBlue;
int currentColor;

/* List functions */
void push(float r, float g, float b, int direction, int index);
int isEmpty(int direction, int index);
void initialize(int start, int direction);

/*
 * push()
 * ------
 * Push value to array
 */
void push(float r, float g, float b, int direction, int index)
{
  // Right
  if (direction == 1)
  {
    if (index == MAXSIZE)
    {
      printf("Right list full\n");
    }
    else
    {
      right[index][0] = r;
      right[index][1] = g;
      right[index][2] = b;
    }
  }
  // Left
  else
  {
    if (index == MAXSIZE)
    {
      printf("Left stack full\n"); 
    }
    else {
      left[index][0] = r;
      left[index][1] = g;
      left[index][2] = b;
    }
  }
}

/*
 * isEmpty()
 * ------
 * Check value if is empty
 */
int isEmpty(int direction, int index)
{
  // Right
  if (direction == 1)
  {  
    if (right[index][0] == -1)
    {
      return 1;
    }
    return 0;
  }
  else
  {
    if (left[index][0] == -1)
    {
      return 1;
    } 
    return 0;
  }
}

/*
 * initialize()
 * ------
 * Sets the initial matrix values to -1
 */
void initialize(int start, int direction)
{
  if (direction == 1)
  {
    for (int i = start; i < MAXSIZE; i ++)
    {
      right[i][0] = -1;
      right[i][1] = -1;
      right[i][2] = -1;
    }
  }
  else
  {
    for (int i = start; i < MAXSIZE; i ++)
    {
      left[i][0] = -1;
      left[i][1] = -1;
      left[i][2] = -1;
    } 
  }
}


// void growList(int direction)
// {
//   if (direction == 1)
//   {
//     int tempMAXSIZE = rightMAXSIZE * 2;
//     float temp[3];

//     // for (int i = 0; i < rightMAXSIZE; i ++)
//     // {
//     //   temp[i][0] = right.stack[i][0];
//     //   temp[i][1] = right.stack[i][1];
//     //   temp[i][2] = right.stack[i][2];
//     // }

//     float **tmp = realloc(right.stack, tempMAXSIZE*sizeof(temp));
//     // Reallocation correct
//     if (tmp)
//     {
//       right.stack = tmp;
//     }
//     //Error - Out of memory
//     else
//     {
//       exit(1);
//     }
//     initialize(rightMAXSIZE, 1);
//     rightMAXSIZE = tempMAXSIZE;
//   }
//   else
//   {
//     int tempMAXSIZE = leftMAXSIZE * 2;
//     float temp[3];

//     // for (int i = 0; i < leftMAXSIZE; i ++)
//     // {
//     //   temp[i][0] = left.stack[i][0];
//     //   temp[i][1] = left.stack[i][1];
//     //   temp[i][2] = left.stack[i][2];
//     // }

//     float **tmp = realloc(left.stack, tempMAXSIZE*sizeof(temp));
//     // Reallocation correct
//     if (tmp)
//     {
//       left.stack = tmp;
//     }
//     //Error - Out of memory
//     else
//     {
//       exit(1);
//     }
//     initialize(leftMAXSIZE, 1);
//     leftMAXSIZE = tempMAXSIZE;
//   }
// }

/* ============== OPENGL ============== */

#define PI 3.1415926535898

#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
 
/*  Globals */
double dim=1.1; /* dimension of orthogonal box */
char *windowName = "Infinite menu wall";
int windowWidth=1000;
int windowHeight=900;

/* Initialize colors as white, except front */
float rFront = 1.0;
float gFront = 1.0;
float bFront = 1.0;
float rBack = 0.0;
float gBack = 0.0;
float bBack = 0.0;
float rRightOne = 0.0;
float gRightOne = 0.0;
float bRightOne = 0.0;
float rRightTwo = 0.0;
float gRightTwo = 0.0;
float bRightTwo = 0.0;
float rLeftOne = 0.0;
float gLeftOne = 0.0;
float bLeftOne = 0.0;
float rLeftTwo = 0.0;
float gLeftTwo = 0.0;
float bLeftTwo = 0.0;
 
/*  Various global state */
int toggleAxes = 1;   /* toggle axes on and off */
int toggleValues = 1; /* toggle values on and off */
int toggleMode = 0; /* projection mode */
int azimuth = 0;   /* azimuth of view angle */
int ph = 6;   /* elevation of view angle */
int fov = 55; /* field of view for perspective */
int asp = 1;  /* aspect ratio */
int movement_r = 0;
int movement_l = 0;
int units_moved = 0;
int units_needed = 12;
int currentFace = 0; /* current face: front */

#define RIGHT 1
#define LEFT 2

/*  Hexagon vertices */
GLfloat vertA[3] = { 0.5, 0.5, 0.9};
GLfloat vertB[3] = {-0.5, 0.5, 0.9};
GLfloat vertC[3] = {-0.5,-0.5, 0.9};
GLfloat vertD[3] = { 0.5,-0.5, 0.9};
GLfloat vertR1[3] = { 1.0, 0.5, 0};
GLfloat vertR2[3] = { 1.0, -0.5, 0};
GLfloat vertL1[3] = { -1.0, 0.5, 0};
GLfloat vertL2[3] = { -1.0, -0.5, 0};
GLfloat vertE[3] = { 0.5, 0.5,-0.9};
GLfloat vertF[3] = {-0.5, 0.5,-0.9};
GLfloat vertG[3] = {-0.5,-0.5,-0.9};
GLfloat vertH[3] = { 0.5,-0.5,-0.9};
 
/*
 * project()
 * ------
 * Sets the projection
 */
void project()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
 
  if (toggleMode) {
    /* perspective */
    gluPerspective(fov,asp,dim/4,4*dim);
  }
  else {
    /* orthogonal projection*/
    glOrtho(-dim*asp,+dim*asp, -dim,+dim, -dim,+dim);
  }
 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
 
/*
 * setEye()
 * ------
 * Set the eye position
 */
void setEye()
{
  glRotatef(ph,1,0,0);
  glRotatef(azimuth,0,1,0);
}

/*
 *  drawShape()
 *  ------
 *  Draw the GLUT shape
 */
void drawShape()
{
  /* Hexagon */
  glBegin(GL_QUADS);
  /* front  */
  glColor3f(rFront,gFront,bFront);
  glVertex3fv(vertA);
  glVertex3fv(vertB);
  glVertex3fv(vertC);
  glVertex3fv(vertD);
  /* back  */
  glColor3f(rBack,gBack,bBack);
  glVertex3fv(vertF);
  glVertex3fv(vertE);
  glVertex3fv(vertH);
  glVertex3fv(vertG);
  /* right 1  */
  glColor3f(rRightOne,gRightOne,bRightOne);
  glVertex3fv(vertR1);
  glVertex3fv(vertA);
  glVertex3fv(vertD);
  glVertex3fv(vertR2);
  /* right 2  */
  glColor3f(rRightTwo,gRightTwo,bRightTwo);
  glVertex3fv(vertE);
  glVertex3fv(vertR1);
  glVertex3fv(vertR2);
  glVertex3fv(vertH);
  /* left 1 */
  glColor3f(rLeftOne,gLeftOne,bLeftOne);
  glVertex3fv(vertB);
  glVertex3fv(vertL1);
  glVertex3fv(vertL2);
  glVertex3fv(vertC);
  /* left 2 */
  glColor3f(rLeftTwo,gLeftTwo,bLeftTwo);
  glVertex3fv(vertF);
  glVertex3fv(vertL1);
  glVertex3fv(vertL2);
  glVertex3fv(vertG);
  /* top 1 */
  glColor3f(0.0,1.0,1.0);
  glVertex3fv(vertA);
  glVertex3fv(vertB);
  glVertex3fv(vertL1);
  glVertex3fv(vertF);
  /* top 2 */
  glColor3f(0.0,1.0,1.0);
  glVertex3fv(vertR1);
  glVertex3fv(vertE);
  glVertex3fv(vertF);
  glVertex3fv(vertA);
  /* bottom  */
  glColor3f(1.0,0.0,1.0);
  glVertex3fv(vertD);
  glVertex3fv(vertC);
  glVertex3fv(vertG);
  glVertex3fv(vertH);
  glEnd();
}
 
/*
 *  display()
 *  ------
 *  Display the scene
 */
void display()
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
 
  /* setup functions */
  setEye();
 
  /* magic here */
  drawShape();
 
  glFlush();
  glutSwapBuffers();
}
 
/*
 *  reshape()
 *  ------
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
  asp = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  project();
}

void timer() 
{
  if(movement_r)
    {
      units_moved++;
      azimuth += 5;
      if (units_moved == units_needed) {
        units_moved = 0;
        movement_r = 0;
      }
    }
  else if (movement_l)
    {
      units_moved++;
      azimuth -= 5;
      if (units_moved == units_needed) {
        units_moved = 0;
        movement_l = 0;
      }
    }

    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

/* 
*   generateColor()
*   ----
*   Generates random new color for a face
*/
void generateColor(int face, int direction, int index)
{
  float red = (float)rand()/(float)(RAND_MAX);
  float green = (float)rand()/(float)(RAND_MAX);
  float blue = (float)rand()/(float)(RAND_MAX);

  switch(face)
  {
    case 0:
      rFront = red;
      gFront = green;
      bFront = blue;
    break;
    case 1:
      rRightOne = red;
      gRightOne = green;
      bRightOne = blue;
    break;
    case 2:
      rRightTwo = red;
      gRightTwo = green;
      bRightTwo = blue;
    break;
    case 3:
      rBack = red;
      gBack = green;
      bBack = blue;
    break;
    case 4:
      rLeftTwo = red;
      gLeftTwo = green;
      bLeftTwo = blue;
    break;
    case 5:
      rLeftOne = red;
      gLeftOne = green;
      bLeftOne = blue;
    break;
  }

  push(red, green, blue, direction, index);
}

/* 
*   assignColor()
*   ----
*   Assigns color for a face
*/
void assignColor(int face, int direction, int index)
{
  float red, green, blue;

  if (direction == 1)
  {
    red = right[index][0];
    green = right[index][1];
    blue = right[index][2];
  }
  else
  {
    red = left[index][0];
    green = left[index][1];
    blue = left[index][2];
  }

  switch(face)
  {
    case 0:
      rFront = red;
      gFront = green;
      bFront = blue;
    break;
    case 1:
      rRightOne = red;
      gRightOne = green;
      bRightOne = blue;
    break;
    case 2:
      rRightTwo = red;
      gRightTwo = green;
      bRightTwo = blue;
    break;
    case 3:
      rBack = red;
      gBack = green;
      bBack = blue;
    break;
    case 4:
      rLeftTwo = red;
      gLeftTwo = green;
      bLeftTwo = blue;
    break;
    case 5:
      rLeftOne = red;
      gLeftOne = green;
      bLeftOne = blue;
    break;
  }
}

/* 
*   changeColor()
*   ----
*   Reset color of front initial face
*/
void resetColor(int realFace)
{
  rFront = 1.0;
  gFront = 1.0;
  bFront = 1.0;
}

/* 
*   changeColor()
*   ----
*   Decides which face will recieve the new colors
*/
void changeColor(int direction)
{
  int realFace = currentFace % 6;
  int index;

  // Right
  if (direction == 1)
  {
    currentColor -= 1;
  }
  // Left
  else
  {
    currentColor += 1;
  }

  if (currentColor == 0)
  {
    resetColor(realFace);
  }
  else if (currentColor < 0)
  {
    index = (currentColor + 1) * -1;
    if(isEmpty(0, index) == 1)
    {
      generateColor(realFace, 0, index);
    }
    else
    {
      assignColor(realFace, 0, index);
    }
  }
  else
  {
    index = currentColor - 1;
    if (isEmpty(1, index) == 1)
    {
      generateColor(realFace, 1, index);
    }
    else
    {
      assignColor(realFace, 1, index);
    }
  }
}

/* 
*   changeFace()
*   ----
*   Changes current face
*/
void changeFace(int movement)
{
  if (movement == -1 && currentFace == 0)
  {
    currentFace = 5;
  }
  else
  {
    currentFace += movement;
  }
}

/*
 *  windowKey()
 *  ------
 *  GLUT calls this routine when a non-special key is pressed
 */
void windowKey(unsigned char key,int x,int y)
{
  /*  Exit on ESC */
  if (key == 27) exit(0);
  /*  Change dimensions */
  else if (key == 'D') dim += 0.1;
  else if (key == 'd') dim -= 0.1;
 
  project();
  glutPostRedisplay();
}
 
/*
 *  windowSpecial()
 *  ------
 *  GLUT calls this routine when an arrow key is pressed
 */
void windowSpecial(int key,int x,int y)
{
  /*  Right arrow key - increase azimuth by 5 degrees */
  if (key == GLUT_KEY_RIGHT) {
    movement_r = 1;
    changeFace(-1);
    changeColor(1);
  }
  /*  Left arrow key - decrease azimuth by 5 degrees */
  else if (key == GLUT_KEY_LEFT) {
    movement_l = 1;
    changeFace(1);
    changeColor(0);
  }
 
  /*  Keep angles to +/-360 degrees */
  azimuth %= 360;
  ph %= 360;
 
  project();
  glutPostRedisplay();
}

void processMenuEvents(int option) {
  switch (option) {
    case RIGHT :
      movement_r = 1;
      changeFace(-1);
      changeColor(1);
      break;
    case LEFT :
      movement_l = 1;
      changeFace(1);
      changeColor(0);
      break;
  }
}
 
void createGLUTMenus() {
 
  int menu;
 
  menu = glutCreateMenu(processMenuEvents);
 
  glutAddMenuEntry("->",RIGHT);
  glutAddMenuEntry("<-",LEFT);
 
  glutAttachMenu(GLUT_LEFT_BUTTON);
}
 
/*
 *  main()
 *  ----
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  // Initialize empty stacks
  initialize(0, 1);
  initialize(0, 0);

  // Initialize first color
  currentColor = 0;

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth,windowHeight);
  glutCreateWindow(windowName);
  createGLUTMenus();
 
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(windowKey);
  glutTimerFunc( 0, timer, 0 );
  glutSpecialFunc(windowSpecial);
 
  glutMainLoop();
  return 0;
}