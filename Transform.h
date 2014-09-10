#ifndef __TRANSFORM__
#define __TRANSFORM__
class Transform {
      public:
         static double* rotate(double dx,double dy,double dz,double angle,double *coords);
         static double* opMatrixd(glMatrixd matrix,double *vec);
};
#endif
