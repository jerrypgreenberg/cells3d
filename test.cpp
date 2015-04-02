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
   extern int count;
   extern double box;
   GLboolean ib;
   GLuint namebuffer[50000];
   GLdouble position2[4] = { 3.0, 3.0,  2.0, 0.0 };
   GLfloat local_view[] = {0.};
   GLUquadricObj * quadObj,*quadObj2;
   void transformmenu(int mvalue);
   void xy_rotate(int x,int y);
   void keys(unsigned char key,int xx, int yy);
   void specialkeys(int key,int x,int y);
   extern CellSimulation *cs;


   double vec[4] = {0.,1.,0.,1.};
   double *returnVec;
   unsigned int seed = 872367251;
   int iter = 10;
   int cellSkip = 5;
   int i;
   int imenu;

   glutInit(&argc,argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   ratmat = &(ori.ratmat);
   XMAXSCREEN=glutGet(GLUT_SCREEN_WIDTH);
   YMAXSCREEN=glutGet(GLUT_SCREEN_HEIGHT);
   cout << "XMAXSCREEN " << XMAXSCREEN <<endl;
   cout << "YMAXSCREEN " << YMAXSCREEN <<endl;
   glutInitWindowSize (XMAXSCREEN, YMAXSCREEN);
   glutInitWindowPosition (0, 0);
   mainwindow=glutCreateWindow("CELLS 3D");
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glShadeModel (GL_FLAT);
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
   glutIdleFunc(0);
   glutReshapeFunc(myReshape);
   cs = new CellSimulation(30,30., 60.,Cell(0., 0., 0., SubTypes::END),seed, 1.0, 1.0,2,2,120.,5);
   ++count;
/*
   cout << "##$$##  NUMBER OF NORMAL CELLS " << cs->getNormalCellTotal() << endl;
   cs->updateSimulation(count-1);
   cs->printSimulationStep();
   cout << "##$$##  NUMBER OF NORMAL CELLS " << cs->getNormalCellTotal() << endl;
   ++count;
   cout << endl;
   cout << endl;
   cout << endl;
   cs->updateSimulation(count-1);
   cs->printSimulationStep();
   cout << "##$$##  NUMBER OF NORMAL CELLS " << cs->getNormalCellTotal() << endl;
  
   cout << cs->getNormalCellTotal() << endl;
*/

   ori.xt[0] = 0.;
   ori.xt[1] = 0.;
   ori.xt[2] = 0.;
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
   ori.scale = (cs->getStepLength()*iter*1.6/cellSkip)/10;
   box = floor((cs->getStepLength()*iter*1.6/cellSkip)) + 1;
   //ori.scale = 0.5;
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
   imenu = glutCreateMenu(transformmenu);
   glutAddMenuEntry("XY-ROTATE",0);
   glutAddMenuEntry("ZROT",1);
   glutAddMenuEntry("XY-TRAN",2);
   glutAddMenuEntry("Z-TRAN",3);
   glutAddMenuEntry("SCALE",4);
   glutSetMenu(imenu);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutMouseFunc(mouse);
   glutMotionFunc(xy_rotate);
   glutKeyboardFunc(keys);
   glutSpecialFunc(specialkeys);
   drawobject();
   glutMainLoop();
}
void myReshape(int w,int h)
{
    // aspect = (float) w/h;
    glViewport(0,0,XMAXSCREEN,YMAXSCREEN);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    XMAXSCREEN=glutGet(GLUT_WINDOW_WIDTH);
    YMAXSCREEN=glutGet(GLUT_WINDOW_HEIGHT);
    ortho();
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
        extern double box;
    
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        cout << "ASPECT " << aspect << endl;
        cout << "BOX " << box << endl;
        glOrtho(-box,box,-box*aspect,box*aspect,-box,-box);
        glMatrixMode(GL_MODELVIEW);
}       
void drawobject()
{
       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
       // glClearColor(0.,0.,0.,0.);
       glFogfv(GL_FOG_COLOR,cblack);
       glMatrixMode(GL_MODELVIEW);
       glGetIntegerv(GL_VIEWPORT,(int *) &vp);
       aspect=(double ) vp.height/(double ) vp.width;
       ortho();
       glLoadIdentity();
       glMultMatrixf((float *) ori.lightscale);
       glLightfv(GL_LIGHT0, GL_POSITION, position1);
       glLoadIdentity();
       glMultMatrixd((double *) ori.tinitmat);
       glMultMatrixd((double *) ori.mscale);
       glMultMatrixd((double *) ori.tmat);
       glMultMatrixd((double *) ori.ratmat);
       glMultMatrixd((double *) ori.mtmat);
       drawaxis();
       plot();
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
void drawaxis()
{
       int i;
       int n;
       double x1,x2,y1,y2,z1,z2;
       double x,y,z;
       double xp1[3],xp2[3];
       n = 10*box;
       y = 0;
       z = 0;
       x2 = .1;
       y2 = .1;
       z2 = .1;
       // glColor3d(1.,1.,1.);
       xp1[0] = 0.;
       xp1[1] = 0.;
       xp1[2] = 0.;
       xp2[0] = 0.;
       xp2[1] = 0.;
       xp2[2] = 0.;
       for(i=0,x=0;i<n;x += x2,++i)
       {
             if((i % 10) == 0)
                 xp2[1] = .1;
             else
                 xp2[1] = .05;
             glPushMatrix();
             glTranslated(x,0.,0.);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if( (i % 10) == 0)
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
             if((i % 10) == 0)
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
             if((i % 10) == 0)
                 xp2[1] = -.1;
             else
                 xp2[1] = -.05;
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();

             glPopMatrix();
       }
       xp1[0] = -box;
       xp1[1] = 0.;
       xp1[2] = 0.;
       xp2[0] = box;
       xp2[1] = 0.;
       xp2[2] = 0.;
       glBegin(GL_LINES);
       glVertex3dv(xp1);
       glVertex3dv(xp2);
       glEnd();
       x = 0.;
       y = 0.;
       z = 0.;
       xp1[0] = x;
       xp1[1] = y;
       xp1[2] = z;
       xp2[0] = x;
       xp2[1] = y;
       xp2[2] = z;
       for(i=0,y=0;i<n;y += y2,++i)
       {
             if((i % 10)  == 0)
                 xp2[0] = .1;
             else
                 xp2[0] = .05;
             glPushMatrix();
             glTranslated(0.,y,0.);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if((i % 10) == 0)
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
             if((i % 10)  == 0)
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
       xp1[0] = 0.;
       xp1[1] = -box;
       xp1[2] = 0.;
       xp2[0] = 0.;
       xp2[1] = box;
       xp2[2] = 0.;
       glBegin(GL_LINES);
       glVertex3dv(xp1);
       glVertex3dv(xp2);
       glEnd();
       x = 0.;
       y = 0.;
       z = 0.;
       xp1[0] = x;
       xp1[1] = y;
       xp1[2] = z;
       xp2[0] = x;
       xp2[1] = y;
       xp2[2] = z;
       for(i=0,z=0;i<n;z += z2,++i)
       {
             if((i % 10) == 0)
                 xp2[1] = .1;
             else
                 xp2[1] = .05;
             glPushMatrix();
             glTranslated(0.,0.,z);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if((i % 10) == 0)
                 xp2[1] = -.1;
             else
                 xp2[1] = -.05;
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();

             glPopMatrix();
       }
       for(i=0,z=0;i<n;z -= z2,++i)
       {
             if((i % 10) == 0)
                 xp2[1] = .1;
             else
                 xp2[1] = .05;
             glPushMatrix();
             glTranslated(0.,0.,z);
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();
             if((i % 10) == 0)
                 xp2[1] = -.1;
             else
                 xp2[1] = -.05;
             glBegin(GL_LINES);
             glVertex3dv(xp1);
             glVertex3dv(xp2);
             glEnd();

             glPopMatrix();
       }
       xp1[0] = 0.;
       xp1[1] = 0.;
       xp1[2] = -box;
       xp2[0] = 0.;
       xp2[1] = 0.;
       xp2[2] = box;
       glBegin(GL_LINES);
       glVertex3dv(xp1);
       glVertex3dv(xp2);
       glEnd();
}
void mouse(int button,int state,int x,int y)
{
      int i;
      extern int YMAXSCREEN;
      extern int xpos,ypos;
      extern int globstate;
      extern int *popmenu;
      extern int currmenu;
      extern int cheaprender,docheaprender;
      extern int num;
      extern int domenu;

      if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
	  globstate = GLUT_UP;
          cout << "UP" << endl;
      }
      else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	  globstate = GLUT_DOWN;
          xpos = x;
          ypos = y;
          cout << "DOWN" << endl;
      }
}
void xy_rotate(int x,int y)
{
	int mtemp;
	extern struct orig ori;
        extern double sxrotate;
        extern double syrotate;
	extern int globstate;
	extern int xpos,ypos;
	extern int otherqmvs,redlight,ctype,record;
	extern struct molecules *molecule;
	extern glMatrixd *ratmat;
	extern int specialrotate;
	extern int specialtranslate;
	extern glMatrixd tempmat;
	void irot(int axis ,double rotate,glMatrixd ratmat);
        if(first) {
            xpos = x;
            ypos = y;
            first = 0;
            return;
        }
        cout << x << " " << y <<endl;
	if(x==xpos && y==ypos) return;
	if(globstate == GLUT_UP) return;
	irot((int) AXIS::YAXIS,syrotate*(x-xpos)*.20,*ratmat);
	irot((int) AXIS::XAXIS,sxrotate*(y-ypos)*.20,*ratmat);
	xpos=x;
	ypos=y;
	glutPostRedisplay();
}
void xy_tran(int x,int y)
{
        double sxtran = 1.;
        double sytran = 1.;
	extern int xpos,ypos;
        if(first) {
            xpos = x;
            ypos = y;
            first = 0;
            return;
        }
	if(x==xpos && y==ypos) return;
	if(globstate == GLUT_UP) return;
	if(ori.scale >= 1.) {
             ori.xt[0] += (double) sxtran*(x - xpos)  * .01/ori.scale;
	     ori.xt[1] += (double) -sytran*(y - ypos)  * .01/ori.scale;
	     Transform::trans((double) sxtran*(x - xpos)  * .01/ori.scale,(double) -sytran*(y - ypos)  * .01/ori.scale,0.);
        }
        else {
              ori.xt[0] += (double) sxtran*(x - xpos)  * .01*ori.scale;
              ori.xt[1] += (double) -sytran*(y - ypos)  * .01*ori.scale;
              Transform::trans((double) sxtran*(x - xpos)  * .01*ori.scale,(double) -sytran*(y - ypos)  * .01*ori.scale,.0);
        }
        cout << "ORI.XT " << ori.xt[0] << " " << ori.xt[1] << " " << ori.xt[2] << endl;
	xpos=x;
	ypos=y;
	glutPostRedisplay();
}
void z_tran(int x,int y)
{
	extern struct orig ori;
	extern int globstate;
	extern int xpos,ypos;
	extern double sx,sy,sz;
	extern int srot;
        extern double sztran;
	extern int xpos,ypos;

	if(y==ypos) return;
        if(first) {
            xpos = x;
            ypos = y;
            first = 0;
            return;
        }
	if(globstate == GLUT_UP) return;
	if(ori.scale > 1.) {
		ori.xt[2] += (double) -sztran*(y - ypos)  * .01/ori.scale;
	        Transform:: trans(0.,0.,(double) -sztran*(y - ypos)  * .01/ori.scale);
	}
	else {
		ori.xt[2] += (double) -sztran*(y - ypos)  * .01*ori.scale;
	        Transform:: trans(0.,0.,(double) -sztran*(y - ypos)  * .01*ori.scale);
	}
	xpos=x;
	ypos=y;
	printf("Z_TRANS %f\n",ori.xt[2]);
	glutPostRedisplay();
}
void z_rotate(int x,int y)
{
	extern int xpos,ypos;
	void irot(int axis,double rot ,glMatrixd ratmat);
        double szrot = 1;
        if(first) {
            xpos = x;
            ypos = y;
            first = 0;
            return;
        }
	if(x==xpos) return;
	if(globstate == GLUT_UP) return;
	irot(AXIS::ZAXIS,(double) szrot*(x-xpos)*.50,*ratmat);
	printf("Z_ROT %d\n",(int) (szrot*x-xpos));
	xpos=x;
	ypos=y;
	glutPostRedisplay();
}
void transformmenu(int mvalue)
{
        extern int xpos,ypos;
        void change_scale(int x,int y);
	switch(mvalue) {
	case MOUSE::XYROT:
		// fpointer = xy_rotate;
                first = 1;
                glutChangeToMenuEntry(1,"XY-ROTATE <-",0);
		ratmat = &(ori.ratmat);
		glutMotionFunc(xy_rotate);
		break;
	case MOUSE::ZROT:
		// fpointer = z_rotate;
                first = 1;
                glutChangeToMenuEntry(2,"ZROT <-",1);
		ratmat = &(ori.ratmat);
		glutMotionFunc(z_rotate);
		break;
	case MOUSE::XYTRAN:
		// fpointer = xy_tran;
                first = 1;
                glutChangeToMenuEntry(3,"XY-TRAN <-",2);
		glutMotionFunc(xy_tran);
		break;
	case MOUSE::ZTRAN:
		// fpointer = z_tran;
                first = 1;
                glutChangeToMenuEntry(4,"Z-TRAN <-",3);
		glutMotionFunc(z_tran);
		break;
        case MOUSE::SCALE:
                // fpointer = change_scale;
                first = 1;
                glutChangeToMenuEntry(5,"SCALE <-",4);
                glutMotionFunc(change_scale);
                break;

     }
}
void irot(int lrot,double da,glMatrixd ratmat)
{
        int j;
        extern struct orig ori;



        da *= 10.;
        switch (lrot) {
        case AXIS::XAXIS :
                if(da > 0.) {
                       for(j=1;j<=(int) da;++j)  {
                                ratrot((double) INCD10,0.,0.,ratmat);
                                ori.xyrot[0] += (double) INCD10;
                       }
                }
                else if(da < 0.)  {
                        for(j=(int) da;j<=-1;++j)  {
                                ratrot((double) -INCD10,0.,0.,ratmat);
                                ori.xyrot[0] -= (double) INCD10;
                        }
                }
                break;
        case AXIS::YAXIS :
                if(da > 0.) {
                       for(j=1;j<=(int) da;++j)  {
                                ratrot(0.,(double) INCD10,0.,ratmat);
                                ori.xyrot[1] += (double) INCD10;
                       }
                }
                else if(da < 0.) {
                        for(j=(int) da;j<=-1;++j)  {
                                ratrot(0.,(double) -INCD10,0.,ratmat);
                                ori.xyrot[1] += (double) -INCD10;
                        }
                }
                break;
        case AXIS::ZAXIS :
                if(da > 0.) {
                       for(j=1;j<=(int) da;++j)  {
                                ratrot(0.,0.,(double) INCD10,ratmat);
                                ori.zrot += (double) INCD10;
                       }
                }
                else if(da < 0.) {
                        for(j=(int) da;j<=-1;++j) {
                                ratrot(0.,0.,(double) -INCD10,ratmat);
                                ori.zrot -= INCD10;
                        }
                }
                break;
        }
}
void ratrot(double dx,double dy,double dz,glMatrixd matrix)
{
    glPushMatrix();
    glLoadIdentity();
    if(dx) glRotated(dx,1.,0.,0.);
    if(dy) glRotated(dy,0.,1.,0.);
    if(dz) glRotated(dz,0.,0.,1.);
    glMultMatrixd((double *) matrix);
    glGetDoublev(GL_MODELVIEW_MATRIX,(double *) matrix);
    glPopMatrix();
}
void change_scale(int x,int y)
{
        extern struct orig ori;
        extern int globstate;
        extern int xpos,ypos;
        extern double sscale;
        if(first) {
            xpos = x;
            ypos = y;
            first = 0;
            return;
        }
        cout << "ORI.SCALE " << ori.scale << endl;
        if(y==ypos) return;
        if(globstate == GLUT_UP) return;
        if(ori.scale >= 1.)
                ori.scale += (double) -sscale*(y - ypos)*.03;
        else
                ori.scale += (double) -sscale*(y - ypos)*.003;
        if(ori.scale < 0.0001)
                ori.scale = 0.0001;
        rescale();
        ypos = y;
        xpos = x;
        glutPostRedisplay();
}
void keys(unsigned char key,int xx, int yy)
{
    switch(key)
    {
      case 27:
         exit(0);
    }
}
void specialkeys(int key,int xx, int yy)
{
    extern int count;
    switch(key)
    {
     case GLUT_KEY_RIGHT:
       cs->updateSimulation(count-1);
       drawobject();
       ++count;
       cout << "##$$##  NUMBER OF NORMAL CELLS " << cs->getNormalCellTotal() << endl;
       cs->printSimulationStep();
       break;
    }
}
void plot()
{
      vector<Cell>::iterator cellNum;
      double x1,y1;
      
      AllCells[TYPES::NORMAL].begin();
      for(cellNum = AllCells[TYPES::NORMAL].begin(); cellNum = AllCells[TYPES::NORMAL].end(); ++cellNum)
      {
          x1 = cellNum.getCoordX();
          y1 = cellNum.getCoordY();
          z1 = cellNum.getCoordZ();
          glRectd();
      }
}
