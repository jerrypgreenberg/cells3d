#include "glStuff.h"
#include "CellSimulation.h"
#include <iostream>
#include <cmath>
using namespace std;
int main(int argc,char **argv)
{
   int mainwindow;
   int XMAXSCREEN,YMAXSCREEN;
   GLboolean ib;
   GLuint namebuffer[50000];
   GLfloat position1[4] = { 0.0, 0.0, 1., 1.0 };
   GLfloat position2[4] = { 3.0, 3.0,  2.0, 0.0 };
   GLfloat local_view[] = {0.};
   float cblack[4] = { 0. , 0. , 0.,1.};
   GLUquadricObj * quadObj,*quadObj2;



   double vec[4] = {0.,1.,0.,1.};
   double *returnVec;
   int i;

   glutInit(&argc,argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   XMAXSCREEN=glutGet(GLUT_SCREEN_WIDTH);
   YMAXSCREEN=glutGet(GLUT_SCREEN_HEIGHT);
   glutInitWindowSize (XMAXSCREEN, YMAXSCREEN);
   glutInitWindowPosition (0, 0);
   mainwindow=glutCreateWindow("CELLS 3D");
   glGetBooleanv(GL_DEPTH_WRITEMASK,&ib);
   glGetBooleanv(GL_DOUBLEBUFFER,&ib);
   glGetBooleanv(GL_STEREO,&ib);
   glClearColor(0.,0.,0.,0.);
   glDrawBuffer(GL_BACK);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glDrawBuffer(GL_FRONT);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glClearColor(0.,0.,0.,0.);
   glDrawBuffer(GL_BACK);
   glSelectBuffer(50000,namebuffer);
   glShadeModel(GL_SMOOTH);
   glMatrixMode(GL_MODELVIEW);
   glLightfv(GL_LIGHT0, GL_POSITION, position1);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_FOG);
   glFogi (GL_FOG_MODE, GL_LINEAR);
   glHint (GL_FOG_HINT, GL_NICEST);
   glFogfv(GL_FOG_COLOR,cblack);
   glEnable(GL_NORMALIZE);
   quadObj = gluNewQuadric ();
   quadObj2 = gluNewQuadric ();
   gluQuadricDrawStyle (quadObj, GLU_LINE);
   gluQuadricDrawStyle (quadObj2, GLU_FILL);
   gluQuadricOrientation (quadObj2, GLU_OUTSIDE);
   gluQuadricNormals(quadObj2, GLU_SMOOTH);
   // glutReshapeFunc(myReshape);
  
   CellSimulation cs(30, 30., 60.,Cell(0., 0., 0., SubTypes::END),1.0, 1.0), 2, 2,120.,5);

}

