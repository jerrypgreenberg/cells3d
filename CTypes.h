#ifndef _CTYPES_H_
#define _CTYPES_H_
enum SubTypes {
    SNORMAL,
    END,
    INTERMEDIATE,
    MAIN_R,
    MAIN_L,
    MAIN_C,
    MAIN,
    LAST
};
/** flags for cells crossing periodic boundary **/
enum PeriodicType {
    PNORMAL,
    CROSSED
};
/** flags for metanephric cells  **/
enum AddedType {
    ANORMAL,
    ADDED
};
enum Types {
   NORMAL,
   METANEPHRIC,
   ATTRACTIVE
};
#endif
