#ifndef _EXTERNAL_H_
#define _EXTERNAL_H_
GLfloat position1[4] = { 0.0, 0.0, 1., 1.0 };
int XMAXSCREEN,YMAXSCREEN;
int xpos,ypos;
double aspect;
GLfloat cblack[4] = { 0. , 0. , 0.,1.};
struct orig ori;
struct viewp vp,vp2;
int globstate;
glMatrixd *ratmat;
double sscale = 1.;
double sxrotate = 1.;
double syrotate = 1.;
double sztran = 1.;
int first = 1;
double box;
extern int count = 0;
CellSimulation *cs;
#endif
