#include "CellSimulation.h"
#include<iostream>
#include<cmath>
using namespace std;

double CellSimulation::TOL = 0.00001;
double CellSimulation::ELLIPSE_MAJOR = .2;
double CellSimulation::ELLIPSE_MINOR = .035;
double CellSimulation::DTR = M_PI / 180.;
int CellSimulation::START_METANEPHRIC_CELLS = 1;
int CellSimulation::NUM_METANEPHRIC_CELLS = 50;
int CellSimulation::MAX_NUM_CELLS_BRANCH = 8;
double CellSimulation::BRANCH_STEP_LENGTH = 1.;
double CellSimulation::METANEPHRIC_WIDTH = 0.2;
double CellSimulation::ANGLE_DEVIATION = 20.;
bool CellSimulation::METANEPHRIC_CELL_PERIODIC = true;
int CellSimulation::CELL_TYPES = 3;
int CellSimulation::NUM_ATTRACTIVE_CELLS = 10;
int CellSimulation::MAX_METANEPHRIC_ATTRACT_MOVES = 60;
double[] CellSimulation::ZERO_COORDS = {
      0., 0., 0.
};

CellSimulation::CellSimulation(int inIter, double minang, double maxang, Cell cell, unsigned int seed, double length, double fraction, int maxB, int intermediate, double spread, int skip) {
                int i;
                setIter(inIter);
                setStepLength(length);
                setBranchStepLength(BRANCH_STEP_LENGTH);

                // cout << "RANDOM ANGLE MIN IN " << minang <<endl;
                // cout <<("RANDOM ANGLE MAX IN " << maxang <<endl;
                setMinAngle(minang);
                setMaxAngle(maxang);
                setFraction(fraction);
                setMaxBranch(maxB);
                setMaxIntermediateBranch(intermediate);
                setSpreadAngle(spread);
                setCellSkip(skip);
                setRandomSeed(seed);
                srand(getRandomSeed());
                growCell(cell);
                attractiveRadius = (0.9 * iter) / getCellSkip();
                upperLimit = attractiveRadius * 1.1;
                lowerLimit = 0.0;
                leftLimit = (-(upperLimit - lowerLimit) * 1.4) / 2;
                rightLimit = -leftLimit;

                // cout << " Left " << leftLimit << " Right " << rightLimit <<
                //  " Lower " << lowerLimit << " Upper " << upperLimit <<endl;
}
void setSpreadAngle(double a) {
           spreadAngle = a;
}
double CellSimulation::getSpreadAngle() {
           return (spreadAngle);
}
void CellSimulation::setCellSkip(int a) {
           cellSkip = a;
}
int CellSimulation::getCellSkip() {
           return (cellSkip);
}
void CellSimulation::setMaxAngle(double ang) {
           maxAngle = ang;
}
void CellSimulation::setMinAngle(double ang) {
           minAngle = ang;
}
double CellSimulation::getMinAngle() {
           return (minAngle);
}
double CellSimulation::getMaxAngle() {
           return (maxAngle);
}
double CellSimulation::getMainRandomAngle() {
           if (angleMainSign > 0) {
                   angleMainSign = -1;
           } else {
                   angleMainSign = 1;
           }

           return ( ( (double) (rand()/RAND_MAX)*30.) * angleMainSign);
}
double CellSimulation::getRandomAngle() {
           double angleDiff = getMaxAngle() - getMinAngle();

           if (angleSign > 0) {
                   angleSign = -1;
           } else {
                   angleSign = 1;
           }

           return (getMinAngle() + angleDiff *  (double) (rand()/RAND_MAX)  * angleSign);
}
void CellSimulation::setMaxBranch(int it) {
        maxBranch = it;
}
int CellSimulation::getMaxBranch() {
        return (maxBranch);
}
void CellSimulation::setIter(int it) {
        iter = it;
}
int CellSimulation::getIter() {
        return (iter);
}
double CellSimulation::getStepLength() {
        return (stepLength);
}
void CellSimulation::setStepLength(double s) {
        stepLength = s;
}
double CellSimulation::getBranchStepLength() {
        return (branchStepLength);
}
void CellSimulation::setBranchStepLength(double s) {
        branchStepLength = s;
}
unsigned int  CellSimulation::getRandomSeed() {
        return (randomSeed);
}
void CellSimulation::setRandomSeed(unsigned int seed) {
         randomSeed = seed;
}
double CellSimulation::getFraction() {
        return (fraction);
}
void CellSimulation::setFraction(double frac) {
       fraction = frac;
}
void CellSimulation::printSimulationStep() {
       int i;
       int j;
       Cell cell;

       // for (j = 0; j < getNormalCellTotal(); ++j) {
       //   cout << AllCells[Types.NORMAL.ordinal()].elementAt(j)) << endl;
       // }
}
void CellSimulation::growCell(Cell cell) {
         AllCells[cell.getType()].push_back(cell);
         return;
}
void CellSimulation::growCells(vector<Cell> cells) {
         vector<Cell>::iterator i;
         for (i = cells.begin(); i != cells.end(); ++i)
               AllCells[cells[0].getType()].push_back(i);
         return;
}
int CellSimulation::getNumCellsToMain(Cell cell)
{
       vector<Cell> trace;
       int count = 0;
       int vector<Cell>::iterator i;
       trace = cell.traceCellDown();

        if ((cell.getSubType() == SubTypes.MAIN_R) ||
            (cell.getSubType() == SubTypes.MAIN_L) ||
            (cell.getSubType() == SubTypes.MAIN_C) ||
            (cell.getSubType() == SubTypes.MAIN)) {
            return (0);
        }

        for (i = itrace.begin(); i == trace.end(); ++i) {

            if ((i.getSubType() == SubTypes.MAIN_R) ||
                (i.getSubType() == SubTypes.MAIN_L) ||
                (cell.getSubType() == SubTypes.MAIN_C) ||
                (i.getSubType() == SubTypes.MAIN)) {
                return (count);
            } else {
                ++count;
            }
        }

        return (count);
}
void CellSimulation::placeNewCell(Cell oldCell, Cell newCell, int icount) {
	if (oldCell.getLinkCellDown() == (Cell *) NULL) {
	     if (first == false) {
		// cout << "RETURN oldCell.getLinkCellDown() == NULL");
				return;
            
             }
             if (oldCell.getSubType() == SubTypes.INTERMEDIATE) {
     	         newCell.setCellCount(newCell.getCellCount() - 1);
	            // cout << "RETURN Cell.getSubType() == SubTypes.INTERMEDIATE" << endl;
	         return;
	    }
	    newCell.setCoords(Transform.translate(oldCell.getCoords(), 0., 1. * getStepLength(), 0.));
	    first = false;
         }
	 else {
	       if (cellGrowthCount <= 1) {
			// cout << "RETURN Cell.getSubType() == SubTypes.INTERMEDIATE" <<endl;
			return;
		}
		if (getNumCellsToMain(oldCell) > MAX_NUM_CELLS_BRANCH) {
			// cout << "RETURN getNumCellsToMain(oldCell)" <<endl;
			return;
		}
		// cout << "OLD CELL SUB TYPE " << oldCell.getSubType()) << endl;
		oldOldCell = oldCell.getLinkCellDown();
		scale = scaleFactor(oldCell, oldOldCell);
		if ((oldCell.getSubType() == SubTypes.MAIN_R) ||
			(oldCell.getSubType() == SubTypes.MAIN_L) ||
			(oldCell.getSubType() == SubTypes.MAIN_C) ||
			(cellGrowthCount <= 2)) {
			   newCell.setCoords(Transform.translate(ZERO_COORDS, 0., getStepLength(), 0.));
		}
}
