#ifndef __TRANSFORM__
#define __TRANSFORM__
#include "glStuff.h"
class Transform {
      public:
         static double* rotate(double dx,double dy,double dz,double angle,double *coords);
         static double* translate(double *xyz,double *coords);
         static double* translate(double dx,double dy,double dz,double *coords);
         static double* opMatrixd(glMatrixd matrix,double *vec);
};
#endif
