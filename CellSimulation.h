#ifndef _CELLSIMULATION_H_
#define _CELLSIMULATION_H_
#include "Cell.h"
#include<vector>
#define CELL_TYPES 3
class CellSimulation {

   private:
     static int NUM_ATTRACTIVE_CELLS;
     static int MAX_METANEPHRIC_ATTRACT_MOVES;
     static double ZERO_COORDS[];
     double stepLength;
     double branchStepLength;
     int iter;
     int count = 0;
     double angleMainSign = 1.;
     double angleSign = 1.;
     double perpAngleSign = 1.;
     unsigned int randomSeed = 101010;
     double maxAngle = 60;
     double minAngle = 30;
     double random;
     int maxBranch;
     int maxIntermediateBranch;
     double DOCKING_DISTANCE = 0.1;
     double spreadAngle = 120.;
     int cellSkip = 4;
     double fraction;
     std::vector<Cell> lastCells;
     std::vector < std::vector <Cell> > AllCells;
     bool first = true;
     int cellGrowthCount = 0;
     int metanephric_attract_moves = 0;
     double attractiveRadius;
     static bool METANEPHRIC_CELL_PERIODIC;
     bool debug = false;
     Cell oldOldCell;
     void placeNewCell(Cell oldCell, Cell newCell, int icount);
     double scaleFactor(Cell c1,Cell C2);
     void placeMetanephricCells();
     void placeAttractiveCells();
     void currentAlgorithm(Cell cell);
     Cell dummyCell;
     void growCell(Cell cell);
     void growCells(std::vector<Cell> cells);
     int getNumCellsToMain(Cell cell);
     void setMaxIntermediateBranch(int branch);
     int getMaxIntermediateBranch();
     void updateLastCellList();
     void moveMetanenephricCells();
     static double getCalculatedPhiAngle(double dx, double dy,double dz);
     static double getCalculatedThetaAngle(double dx, double dy,double dz);
     int getAttractiveCellTotal();
     Cell getAttractiveCell(int i);
     class DistNo {
         private:
              int i;
              double dist;
         public:
             DistNo();
             DistNo(int no,double d);
             int getI();
             std::string toString();
             void setI(int no);
             double getDist();
             void setDist(double d);
             void setDist(int no,double d);
     };
     std::vector<DistNo> distVec;
     void sortThem(std::vector<DistNo> distVec);

  public:
     static double TOL;
     static double ELLIPSE_MAJOR;
     static double ELLIPSE_MINOR;
     static double DTR;
     static int START_METANEPHRIC_CELLS;
     static int NUM_METANEPHRIC_CELLS;
     static int MAX_NUM_CELLS_BRANCH;
     static double BRANCH_STEP_LENGTH;
     static double METANEPHRIC_WIDTH;
     static double ANGLE_DEVIATION;
     static int MAX_ATTRACT;
     double rightLimit;
     double leftLimit;
     double upperLimit;
     double lowerLimit;
     int updateCount;
     void setSpreadAngle(double a);
     CellSimulation(int inIter,double minang, double maxang, Cell cell,unsigned int seed, double length, double fraction, int maxB,int intermediate,double spread,int skip);
     double getSpreadAngle();
     void setCellSkip(int a);
     int getCellSkip();
     void setMaxAngle(double ang);
     void setMinAngle(double ang);
     double getMinAngle();
     double getMaxAngle();
     double getMainRandomAngle();
     double getRandomAngle();
     void setMaxBranch(int it);
     int getMaxBranch();
     void setIter(int it);
     int getIter();
     double getStepLength();
     void setStepLength(double s);
     double getBranchStepLength();
     void setBranchStepLength(double s);
     unsigned getRandomSeed();
     void setRandomSeed(unsigned int seed);
     double getFraction();
     void setFraction(double frac);
     void printSimulationStep();
     int  getNormalCellTotal();
     void updateSimulation(int currentIter);
     Cell getNormalCell(int index);
};
#endif
