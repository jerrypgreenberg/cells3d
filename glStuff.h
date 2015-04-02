#ifndef _GLSTUFF_H_
#define _GLSTUFF_H_
// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#define INC 1
#define INCD10 INC/10
#define INCDD10 INCD10/10
#define INCDDD10 INCDD10/10
enum AXIS {
XAXIS, 
YAXIS,
ZAXIS
};
enum MOUSE {
XYROT,
ZROT,
XYTRAN,
ZTRAN,
SCALE
};
typedef GLdouble  glMatrixd[4][4];
typedef GLfloat   glMatrixf[4][4];
void myReshape(int w,int h);
void drawobject();
void rescalelight();
void rescale();
void mouse(int button,int state,int x,int y);
void xy_rotate(int x,int y);
void irot(int lrot,double da,glMatrixd ratmat);
void pers();
void ortho();
void print4D(double* matrix);
void print4F(float* matrix);
void drawaxis();
// void (*fpointer)( int x, int y) = 0;
void ratrot(double dx,double dy,double dz,glMatrixd matrix);
#endif
