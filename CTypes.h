#ifndef __CTYPES__
#define __CTYPES__
enum class SubTypes {
    NORMAL,
    END,
    INTERMEDIATE,
    MAIN_R,
    MAIN_L,
    MAIN_C,
    MAIN,
    LAST
};
/** flags for cells crossing periodic boundary **/
enum class PeriodicType {
    NORMAL,
    CROSSED
};
/** flags for metanephric cells  **/
enum class AddedType {
    NORMAL,
    ADDED
};
enum class Types {
   NORMAL,
   METANEPHRIC,
   ATTRACTIVE
};
#endif
