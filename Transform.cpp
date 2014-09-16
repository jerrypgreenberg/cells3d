#include "glStuff.h"
#include "Transform.h"
#include <cstdlib>
#include <iostream>
using namespace std;

double* Transform::rotate(double dx,double dy,double dz,double angle,double *coords)
{       
    double  *matrix = (double *) malloc(16*sizeof(double));
    double x[4];
    int i,j;
    double sum;
    double* returnVec = (double *) malloc(4*sizeof(double));
    glPushMatrix();
    glLoadIdentity();
    if(dx) glRotated(angle,1.,0.,0.);
    if(dy) glRotated(angle,0.,1.,0.);
    if(dz) glRotated(angle,0.,0.,1.);
    glGetDoublev(GL_MODELVIEW_MATRIX,(double *) matrix);
    glPopMatrix();
    for(j=0;j<4;++j) {
      for(i=0;i<4;++i)
         cout << *(matrix+4*i+j) << " " ;
      cout << endl;
    }
    for(i=0;i<4;++i) {
         sum = 0.;
         for(j=0;j<4;++j)
             sum += *(matrix+4*j+i) * coords[j];
         returnVec[i] = sum;
    }
    free(matrix);
    return(returnVec);
}
/*
double* opMatrixd(double *matrix,double *vec)
{
     return(returnVec);
}
*/
