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

// Other header files
#include "stack.h"

#define PI 3.1415926535898

#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
 
/*  Globals */
double dim=1.1; /* dimension of orthogonal box */
char *windowName = "Infinite menu wall";
int windowWidth=1000;
int windowHeight=900;
 
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
  glColor3f(1.0,1.0,0.0);
  glVertex3fv(vertA);
  glVertex3fv(vertB);
  glVertex3fv(vertC);
  glVertex3fv(vertD);
  /* back  */
  glColor3f(1.0,0.0,0.0);
  glVertex3fv(vertF);
  glVertex3fv(vertE);
  glVertex3fv(vertH);
  glVertex3fv(vertG);
  /* right 1  */
  glColor3f(0.0,1.0,0.0);
  glVertex3fv(vertR1);
  glVertex3fv(vertA);
  glVertex3fv(vertD);
  glVertex3fv(vertR2);
  /* right 2  */
  glColor3f(0.0,0.5,0.0);
  glVertex3fv(vertE);
  glVertex3fv(vertR1);
  glVertex3fv(vertR2);
  glVertex3fv(vertH);
  /* left 1 */
  glColor3f(0.0,0.0,1.0);
  glVertex3fv(vertB);
  glVertex3fv(vertL1);
  glVertex3fv(vertL2);
  glVertex3fv(vertC);
  /* left 2 */
  glColor3f(0.0,0.0,0.5);
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
  }
  /*  Left arrow key - decrease azimuth by 5 degrees */
  else if (key == GLUT_KEY_LEFT) {
    movement_l = 1;
  }
 
  /*  Keep angles to +/-360 degrees */
  azimuth %= 360;
  ph %= 360;
 
  project();
  glutPostRedisplay();
}

void timer() {
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
 *  main()
 *  ----
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth,windowHeight);
  glutCreateWindow(windowName);
 
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(windowKey);
  glutTimerFunc( 0, timer, 0 );
  glutSpecialFunc(windowSpecial);
 
  glutMainLoop();
  return 0;
}