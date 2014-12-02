#include "Transform.h"
#include <cstdlib>
#include <iostream>
using namespace std;

double* Transform::rotate(double dx,double dy,double dz,double angle,double *coords)
{       
    glMatrixd  matrix;
    double x[4];
    glPushMatrix();
    glLoadIdentity();
    if(dx) glRotated(angle,1.,0.,0.);
    if(dy) glRotated(angle,0.,1.,0.);
    if(dz) glRotated(angle,0.,0.,1.);
    glGetDoublev(GL_MODELVIEW_MATRIX,(double *) matrix);
    glPopMatrix();
    return(opMatrixd(matrix,coords));
}
double* Transform::translate(double dx,double dy,double dz,double *coords)
{
     double xyz[4];
     xyz[0] = dx;
     xyz[1] = dy;
     xyz[2] = dz;
     xyz[3] = 1.0;
 
     return(Transform::translate(xyz,coords));
}
double* Transform::translate(double *xyz,double *coords)
{
    glMatrixd  matrix;
    double x[4];
    glPushMatrix();
    glLoadIdentity();
    glTranslated(*coords,*(coords+1),*(coords+2));
    glGetDoublev(GL_MODELVIEW_MATRIX,(double *) matrix);
    glPopMatrix();
    return(opMatrixd(matrix,xyz));
}
double* Transform::opMatrixd(glMatrixd matrix,double *coords)
{
   double* returnVec = (double *) malloc(4*sizeof(double));
   double sum;
   int i,j;
    for(i=0;i<4;++i) {
         sum = 0.;
         for(j=0;j<4;++j)
             sum += matrix[j][i] * *(coords+j);
         returnVec[i] = sum;
    }
     return(returnVec);
}
