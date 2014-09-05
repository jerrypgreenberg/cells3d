#include <cstdlib>
#include <iostream>
#include "Cell.h"
using namespace std;
class Ctypes
{
   public:
      static int totalNORMAL;
      static int totalMETANEPHRIC;
      static int totalATTRACTIVE;
   static void addCell(Types type)
   {
        switch(type)
        {
           case Types::NORMAL:
               ++totalNORMAL;
               break;
           case Types::METANEPHRIC:
               ++totalMETANEPHRIC;
               break;
           case Types::ATTRACTIVE:
               ++totalATTRACTIVE;
               break;
           default:
               cerr << "BAD CELL TYPE" <<endl;
               exit(0);
        }
   }
   static void subtractCell(Types type)
   {
        switch(type)
        {
           
           case Types::NORMAL:
               --totalNORMAL;
               break;
           case Types::METANEPHRIC:
               --totalMETANEPHRIC;
               break;
           case Types::ATTRACTIVE:
               --totalATTRACTIVE;
               break;
           default:
               cerr << "BAD CELL TYPE" <<endl;
               exit(0);
        }
   }
   static int cellTotal()
   {
       return(totalNORMAL+totalMETANEPHRIC+totalATTRACTIVE);
   }
};
