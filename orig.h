#ifndef _ORIG_H_
#define _ORIG_H_
#define FOVY 20.
#define NNEAR 10.
#define FFAR 2000.
struct orig {
  glMatrixd ratmat;
  glMatrixd tmat;
  glMatrixd tinitmat;
  glMatrixd tsavemat;
  glMatrixd savemat;
  glMatrixd mscale;
  glMatrixd mmtmat;
  glMatrixd mtmat;
  glMatrixf lightscale;
  double   rad;
  double xt[3];
  double nnear;
  double ffar;
  double fovy;
  double xyrotincr[2];
  double zrotincr;
  double xtincr[3];
  double nearincr;
  double farincr;
  double fovyincr;
  double xyrot[2];
  double zrot;
  double scale;
} ori;
struct viewp {
  int xcoord;
  int ycoord;
  int  width;
  int  height;
} vp,vp2;
GLfloat position1[4] = { 0.0, 0.0, 1., 1.0 };
int XMAXSCREEN,YMAXSCREEN;
double aspect;
GLfloat cblack[4] = { 0. , 0. , 0.,1.};
#endif
