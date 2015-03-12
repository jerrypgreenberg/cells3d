#ifndef _GLSTUFF_H_
#define _GLSTUFF_H_
// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
enum class AXIS {
XAXIS, 
YAXIS,
ZAXIS
};
typedef GLdouble  glMatrixd[4][4];
typedef GLfloat   glMatrixf[4][4];
void myReshape(int w,int h);
#endif
