#include "CellSimulation.h"
#include "Transform.h"
#include "Cell.h"
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
int CellSimulation::NUM_ATTRACTIVE_CELLS = 10;
int CellSimulation::MAX_METANEPHRIC_ATTRACT_MOVES = 60;
double CellSimulation::ZERO_COORDS[3] = {
	0., 0., 0.
};


CellSimulation::CellSimulation(int inIter, double minang, double maxang, Cell cell,unsigned int seed, double length, double fraction, int maxB,int intermediate,double spread,int skip) {
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
        AllCells.resize(CELL_TYPES);
        for(i=0;i<CELL_TYPES;++i)
            AllCells[i].resize(1);
	growCell(cell);
	attractiveRadius = (0.9 * iter) / getCellSkip();
	upperLimit = attractiveRadius * 1.1;
	lowerLimit = 0.0;
	updateCount = 0;
	leftLimit = (-(upperLimit - lowerLimit) * 1.4) / 2;
	rightLimit = -leftLimit;
	// cout << " Left " << leftLimit << " Right " << rightLimit <<
	//  " Lower " << lowerLimit << " Upper " << upperLimit <<endl;
}
void CellSimulation::setSpreadAngle(double a) {
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
	//   cout << AllCells[Cell::to_Int(cell.getType())][j] << endl;
       // }
}
void CellSimulation::growCell(Cell cell) {
         AllCells[Cell::to_Int(cell.getType())].push_back(cell);
         return;
}
void CellSimulation::growCells(vector<Cell> cells) {
         vector<Cell>::iterator i;
         for (i = cells.begin(); i == cells.end(); ++i)
           //     AllCells[Cell::to_Int(cells[0].getType())].push_back(*i);
         return;
}
int CellSimulation::getNumCellsToMain(Cell cell)
{
       vector<Cell> trace;
       int count = 0;
       vector<Cell>::iterator i;
       trace = cell.traceCellDown();

        if ((cell.getSubType() == SubTypes::MAIN_R) ||
            (cell.getSubType() == SubTypes::MAIN_L) ||
            (cell.getSubType() == SubTypes::MAIN_C) ||
            (cell.getSubType() == SubTypes::MAIN)) {
            return (0);
        }

        for (i = trace.begin(); i == trace.end(); ++i) {

            if ((i->getSubType() == SubTypes::MAIN_R) ||
                (i->getSubType() == SubTypes::MAIN_L) ||
                (cell.getSubType() == SubTypes::MAIN_C) ||
                (i->getSubType() == SubTypes::MAIN)) {
                return (count);
            } else {
                ++count;
            }
        }

        return (count);
}
void CellSimulation::setMaxIntermediateBranch(int branch) {
        maxIntermediateBranch = branch;
}

int CellSimulation::getMaxIntermediateBranch() {
        return (maxIntermediateBranch);
}

double CellSimulation::scaleFactor(Cell c1, Cell c2) {
        return (sqrt(pow(c2.getCoordX() - c1.getCoordX(),2) +
            pow((c2.getCoordY() - c1.getCoordY()), 2) +
            pow((c2.getCoordZ() - c1.getCoordZ()), 2)));
}


void CellSimulation::placeNewCell(Cell oldCell, Cell newCell, int icount) {
        double scale;
	if (oldCell.getLinkCellDown() == (Cell *) NULL) {
	     if (first == false) {
		// cout << "RETURN oldCell.getLinkCellDown() == NULL");
				return;
            
             }
             if (oldCell.getSubType() == SubTypes::INTERMEDIATE) {
     	         newCell.setCellCount(newCell.getCellCount() - 1);
	            // cout << "RETURN Cell.getSubType() == SubTypes::INTERMEDIATE" << endl;
	         return;
	    }
	    newCell.setCoords(Transform::translate(0., 1. * getStepLength(), 0.,oldCell.getCoords()));
	    first = false;
         }
	 else {
	       if (cellGrowthCount <= 1) {
			// cout << "RETURN Cell.getSubType() == SubTypes::INTERMEDIATE" <<endl;
			return;
		}
		if (getNumCellsToMain(oldCell) > MAX_NUM_CELLS_BRANCH) {
			// cout << "RETURN getNumCellsToMain(oldCell)" <<endl;
			return;
		}
		// cout << "OLD CELL SUB TYPE " << oldCell.getSubType()) << endl;
		oldOldCell = *oldCell.getLinkCellDown();
		scale = scaleFactor(oldCell, oldOldCell);
		if ((oldCell.getSubType() == SubTypes::MAIN_R) ||
			(oldCell.getSubType() == SubTypes::MAIN_L) ||
			(oldCell.getSubType() == SubTypes::MAIN_C) ||
			(cellGrowthCount <= 2)) {
			   newCell.setCoords(Transform::translate(0., getStepLength(), 0.,ZERO_COORDS));
		}
        }
}
void CellSimulation::updateSimulation(int currentIter)
{
        int j;
        int initSize;
        initSize = getNormalCellTotal();

        if (currentIter == 0) {
            cellGrowthCount = 0;
        }

        if (currentIter == START_METANEPHRIC_CELLS) {
            placeMetanephricCells();
            placeAttractiveCells();
        }

        if (((currentIter % getCellSkip()) == 0) && (currentIter < getIter())) {
            ++cellGrowthCount;

            /* loop over all normal cells: grow new ones */
            for (j = 0; j < initSize; ++j)
                currentAlgorithm((Cell) AllCells[Cell::to_Int(Types::NORMAL)][j]);

            setStepLength(getStepLength() * getFraction());
            setBranchStepLength(getBranchStepLength() * getFraction());
            if ((cellGrowthCount * getCellSkip()) == iter) {
                updateLastCellList();
            }
        }

        // System.out.println("CURRENTITER " + currentIter);

        /* move metanephric cells */
        if (currentIter > START_METANEPHRIC_CELLS) {
            if (debug)
                System.out.println("IN MOVEMETANEPHRIC CELLS " + ++updateCount);
            moveMetanenephricCells();
        }
}
void CellSimulation::getNormalCellTotal()
{
         AllCells[Cell::to_Int(Types::NORMAL)].size());
}
void CellSimulation::placeMetanephricCells()
{
        int j;
        double x;
        double y;

        for (j = 0; j < NUM_METANEPHRIC_CELLS; ++j) {
            x = (iter * .7 * (-0.5 +  (double) (rand()/RAND_MAX))) / getCellSkip();
            y = (iter * .7 *  (double) (rand()/RAND_MAX)) / getCellSkip();
            AllCells[Cell::to_Int(Types:METANEPHRIC)].push_back(Cell(x,
                getFraction() + y, 0., Types::METANEPHRIC, SubTypes::NORMAL));
        }
}
void CellSimulation::placeAttractiveCells()
{
        double angle;
        int j;
        double x;
        double y;

        for (j = 0, angle = 30; j < NUM_ATTRACTIVE_CELLS;
            ++j, angle += (120 / NUM_ATTRACTIVE_CELLS)) {
            x = attractiveRadius * cos(angle * DTR);
            y = attractiveRadius * sin(angle * DTR);
            AllCells[Cell::to_Int(Types::ATTRACTIVE)].push_back(Cell(x, y, 0.,
                Types.ATTRACTIVE, SubTypes.NORMAL));

        }
}
void CellSimulation::currentAlgorithm(Cell cell)
{
        int number;
        int direction;
        int i;
        int j;
        // System.out.println(" ALGORITHM ITER " + cellGrowthCount + " CELL NUMBER " + cell.getCellNumber());

        switch (Cell:to_Int(SubTypes::getSubType())
        {
          case Cell::to_Int(SubTypes::NORMAL):
            break;

          case Cell::to_Int(SubTypes::MAIN_R):
          case Cell::to_Int(SubTypes::MAIN_L):
          case Cell::to_Int(SubTypes::MAIN_C):
          case Cell::to_Int(SubTypes::MAIN):
            /* randomly pick one or 2 cells to grow out of MAIN cell */
            number = (int)((double) (rand()/RAND_MAX)) * getMaxBranch()) + 1;

            if (cellGrowthCount == 2) {
                number = 2;
            }

            if ((cellGrowthCount > 2) && cell.getCellNumber() <= 3) {
                return;
            }

            if (cell.getLinkCellDown() == null) {
                number = 1;
            }

            for (i = 0; i < number; ++i) {
                // System.out.println("MAIN CELL " + cell.getSubType());
                if (cell.getGrowthCount() < getMaxBranch()) {

                    /* grow a new cell */

                    placeNewCell(cell, new Cell(cell, SubTypes.END, cell), i);

                    // System.out.println("SWITCH TO CELL TYPE " + cell.getSubType());
                    if ((cell.getSubType() == SubTypes.NORMAL) ||
                        (cell.getSubType() == SubTypes.INTERMEDIATE)) {
                        break;
                    }
                } else {
                    break;
                }
            }

            break;

        case END:
        case INTERMEDIATE:

            /* randomly pick one or 2 cells to grow out of END or INTERMEDIATE cell */

            number = (int)((double) (rand()/RAND_MAX) * getMaxBranch()) + 1;

            if (cellGrowthCount == 2) {
                number = 2;
            }

            if ((cellGrowthCount > 2) && cell.getCellNumber() <= 3) {
                return;
            }

            if (cell.getLinkCellDown() == null) {
                number = 1;
            }

            if (debug)
                System.out.println("CELLGROWTHCOUNT*SKIP " +
                    (cellGrowthCount * getCellSkip()) + " ITER " + (iter - 1));

            if (((cellGrowthCount * getCellSkip()) >= iter) &&
                (cell.getSubType() == SubTypes.END)) {
                for (i = 0; i < 2; ++i) {
                    if (cell.getGrowthCount() < getMaxIntermediateBranch()) {
                        placeNewCell(cell, new Cell(cell, SubTypes.LAST, cell),
                            i);
                    } else {
                        break;
                    }
                }
            } else {
                for (i = 0; i < number; ++i) {
                    if (cell.getGrowthCount() < getMaxIntermediateBranch()) {
                        placeNewCell(cell, Cell(cell, SubTypes::END, cell), i);
                    } else {
                        break;
                    }
                }
            }

            break;
        }
}
void CellSimulation::updateLastCellList()
{
        int i;
        Cell cellTemp;
        lastCells = new Vector();

        for (i = 0; i < AllCells[Types.NORMAL.ordinal()].size(); ++i) {
            cellTemp = (Cell) AllCells[Types.NORMAL.ordinal()].elementAt(i);

            if (cellTemp.getSubType() == SubTypes.LAST) {
                lastCells.addElement(cellTemp);
            }
        }

}
