#include "glStuff.h"
#include "Transform.h"
#include "CellSimulation.h"
#include <iostream>
#include <cmath>
#include "orig.h"
#include "external.h"
using namespace std;
int main(int argc,char **argv)
{
   int mainwindow;
   int count = 0;
   GLboolean ib;
   GLuint namebuffer[50000];
   GLdouble position2[4] = { 3.0, 3.0,  2.0, 0.0 };
   GLfloat local_view[] = {0.};
   GLUquadricObj * quadObj,*quadObj2;
   void drawobject();
   void rescalelight();
   void rescale();



   double vec[4] = {0.,1.,0.,1.};
   double *returnVec;
   unsigned int seed = 872367251;
   int iter = 5;
   int cellSkip = 5;
   int i;

   glutInit(&argc,argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   XMAXSCREEN=glutGet(GLUT_SCREEN_WIDTH);
   YMAXSCREEN=glutGet(GLUT_SCREEN_HEIGHT);
   cout << "XMAXSCREEN " << XMAXSCREEN <<endl;
   cout << "YMAXSCREEN " << YMAXSCREEN <<endl;
   glutInitWindowSize (XMAXSCREEN, YMAXSCREEN);
   glutInitWindowPosition (0, 0);
   mainwindow=glutCreateWindow("CELLS 3D");
   glutDisplayFunc(drawobject);
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
   glutReshapeFunc(myReshape);
   CellSimulation cs(30,30., 60.,Cell(0., 0., 0., SubTypes::END),seed, 1.0, 1.0,2,2,120.,5);
   cout << "##$$##  NUMBER OF NORMAL CELLS " << cs.getNormalCellTotal() << endl;
   ++count;
   cs.updateSimulation(count-1);
   cs.printSimulationStep();
   cout << "##$$##  NUMBER OF NORMAL CELLS " << cs.getNormalCellTotal() << endl;
/*
   ++count;
   cout << endl;
   cout << endl;
   cout << endl;
   cs.updateSimulation(count-1);
   cs.printSimulationStep();
   cout << "##$$##  NUMBER OF NORMAL CELLS " << cs.getNormalCellTotal() << endl;
  
   cout << cs.getNormalCellTotal() << endl;
*/

   // glutKeyboardFunc(commandasciikeys);
   // glutPassiveMotionFunc(processmenus);
   // glutSpecialFunc(specialkeys);
   // glutMenuStateFunc(menuinuse);
   ori.xt[0] = 0.;
   ori.xt[1] = 0.;
   ori.xt[2] = 0;
   ori.nnear=NNEAR;
   ori.ffar=FFAR;
   ori.fovy=FOVY;
   ori.xyrotincr[0] = 0.;
   ori.xyrotincr[1] = 0.;
   ori.zrotincr = 0.;
   ori.xtincr[0] = 0.;
   ori.xtincr[1] = 0.;
   ori.xtincr[2] = 0.;
   ori.nearincr = 0.;
   ori.farincr = 0.;
   ori.fovyincr = 0;
   ori.xyrot[0] = 0.;
   ori.xyrot[1] = 0.;
   ori.zrot = 0.;
   ori.scale = (cs.getStepLength()*iter*1.6/cellSkip)/XMAXSCREEN;
   ori.scale = 0.5;
   glLoadIdentity();
   glGetDoublev(GL_MODELVIEW_MATRIX,(double *) ori.tsavemat);
   glGetDoublev(GL_MODELVIEW_MATRIX,(double *) ori.mmtmat);
   glGetDoublev(GL_MODELVIEW_MATRIX,(double *) ori.mtmat);
   glGetDoublev(GL_MODELVIEW_MATRIX,(double *) ori.savemat);

   
   glMatrixMode(GL_MODELVIEW);
   glViewport(0,0,XMAXSCREEN,YMAXSCREEN);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glGetDoublev(GL_MODELVIEW_MATRIX,(double *) ori.ratmat);
   glGetDoublev(GL_MODELVIEW_MATRIX,(double *) ori.tmat);
   glGetDoublev(GL_MODELVIEW_MATRIX,(double *) ori.tinitmat);
   rescalelight();
   rescale();
   Transform::trans(ori.xt[0],ori.xt[1],ori.xt[2]);
   drawobject();
   glutMainLoop();
}
void myReshape(int w,int h)
{
    void pers();
    void ortho();
    aspect = (float) w/h;
    glViewport(0,0,w,h);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    ortho();
    XMAXSCREEN=glutGet(GLUT_WINDOW_WIDTH);
    YMAXSCREEN=glutGet(GLUT_WINDOW_HEIGHT);
    printf("XMAX,YMAX %d %d\n",XMAXSCREEN,YMAXSCREEN);
}
void pers()
{       
        glMatrixd pmat;
        extern double aspect;
        extern int xpos,ypos;
    
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(ori.fovy,aspect,ori.nnear,ori.ffar);
        glGetDoublev(GL_PROJECTION_MATRIX,(double *) pmat);
        glMatrixMode(GL_MODELVIEW);
}       
void ortho()
{       
        glMatrixd pmat;
        extern double aspect;
        extern int xpos,ypos;
    
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.,1.,-1,1.,-1.,1.);
        glGetDoublev(GL_PROJECTION_MATRIX,(double *) pmat);
        glMatrixMode(GL_MODELVIEW);
}       
void drawobject()
{
       int i;
       int n;
       double x1,x2,y1,y2,z1,z2;
       double x,y,z;
       double xp1[3],xp2[3];
       void print4D(double* matrix);
       void print4F(float* matrix);
       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
       // glClearColor(0.,0.,0.,0.);
       glFogfv(GL_FOG_COLOR,cblack);
       glMatrixMode(GL_MODELVIEW);
       glGetIntegerv(GL_VIEWPORT,(int *) &vp2);
       glLoadIdentity();
       glMultMatrixf((float *) ori.lightscale);
       glLightfv(GL_LIGHT0, GL_POSITION, position1);
       glLoadIdentity();
       glMultMatrixd((double *) ori.tinitmat);
       glMultMatrixd((double *) ori.mscale);
       glMultMatrixd((double *) ori.tmat);
       glMultMatrixd((double *) ori.ratmat);
       glMultMatrixd((double *) ori.mtmat);
       n = 10;
       y = 0;
       z = 0;
       x2 = .1;
       y2 = .1;
       z2 = .1;
       // glColor3d(1.,1.,1.);
       xp1[0] = 0.;
       xp2[0] = 0.;
       for(i=0,x=0;i<n;x += x2,++i)
       {
             if(x == 0)
                 xp2[1] = .1;
             else
                 xp2[1] = .05;
             glPushMatrix();
             glTranslated(x,0.,0.);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if(x == 0)
                 xp2[1] = -.1;
             else
                 xp2[1] = -.05;
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();

             glPopMatrix();
       }
       for(i=0,x=0;i<n;x -= x2,++i)
       {
             if(x == 0)
                 xp2[1] = .1;
             else
                 xp2[1] = .05;
             xp2[2] = z;
             glPushMatrix();
             glTranslated(x,0.,0.);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if(x == 0)
                 xp2[1] = -.1;
             else
                 xp2[1] = -.05;
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();

             glPopMatrix();
       }
       x = 0.;
       y = 0.;
       z = 0.;
       xp1[0] = -1.;
       xp1[1] = y;
       xp1[2] = z;
       xp2[0] = 1.;
       xp2[1] = y;
       xp2[2] = z;
       glBegin(GL_LINES);
       glVertex3dv(xp1);
       glVertex3dv(xp2);
       glEnd();
       x = 0;
       z = 0;
       for(i=0,y=0;i<n;y += y2,++i)
       {
             if(y == 0)
                 xp2[0] = .1;
             else
                 xp2[0] = .05;
             glPushMatrix();
             glTranslated(0.,y,0.);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if(y == 0)
                 xp2[0] = -.1;
             else
                 xp2[0] = -.05;
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();

             glPopMatrix();
       }
       for(i=0,y=0;i<n;y -= y2,++i)
       {
             if(x == 0)
                 xp2[0] = .1;
             else
                 xp2[0] = .05;
             glPushMatrix();
             glTranslated(0.,y,0.);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if(x == 0)
                 xp2[0] = -.1;
             else
                 xp2[0] = -.05;
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();

             glPopMatrix();
       }
       glutSwapBuffers();
}
void rescale()
{   
    glPushMatrix();
    glLoadIdentity();
    glScaled(ori.scale,ori.scale,ori.scale);
    glGetDoublev(GL_MODELVIEW_MATRIX,(double * ) ori.mscale);
    glPopMatrix();
}   
void rescalelight()
{
    glPushMatrix();
    glLoadIdentity();
    glScalef(1.0,1.0,1.0);
    glGetFloatv(GL_MODELVIEW_MATRIX,(float * ) ori.lightscale);
    glPopMatrix();
}
void print4D(double *matrix)
{
     for(int i =0;i<4;++i)
     {
        for(int j=0;j<4;++j)
           cout << *(matrix+4*i+j) << " ";
        cout << endl;
     }
}
void print4F(float *matrix)
{
     for(int i =0;i<4;++i)
     {
        for(int j=0;j<4;++j)
           cout << *(matrix+4*i+j) << " ";
        cout << endl;
     }
}
