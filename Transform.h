#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_
#include "glStuff.h"
class Transform {
      public:
         static double* rotate(double dx,double dy,double dz,double angle,double *coords);
         static double* translate(double *xyz,double *coords);
         static double* translate(double *coords,double dx,double dy,double dz);
         static double* translate(double dx,double dy,double dz,double *coords);
         static double* opMatrixd(glMatrixd matrix,double *vec);
         static void trans(double  x,double y,double z);
};
#endif
