#include "GlStuff.h"
#include "Transform.h"
#include <cstdlib>
using namespace std;

double* Transform::rotate(double dx,double dy,double dz,double angle,double *coords)
{       
    glPushMatrix();
    glLoadIdentity();
    glMatrixd matrix;
    if(dx) glRotated(angle,1.,0.,0.);
    if(dy) glRotated(angle,0.,1.,0.);
    if(dz) glRotated(angle,0.,0.,1.);
    glMultMatrixd((double *) matrix);
    glGetDoublev(GL_MODELVIEW_MATRIX,(double *) matrix);
    glPopMatrix();
    return(opMatrixd(matrix,coords));
}                  
double* opMatrixd(glMatrixd matrix,double *vec)
{
     int i,j;
     double sum;
     double* returnVec = (double *) malloc(4*sizeof(double));
     for(i=0;i<4;++i) {
         sum = 0.;
         for(j=0;j<4;++j)
             sum += matrix[i][j]*vec[j];
         returnVec[i] = sum;
     }
     return(returnVec);
}
