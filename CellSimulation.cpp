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
void CellSimulation::growCell(Cell cell) {
    cout << "CALL growCell" << endl;
    AllCells[cell.getType()].push_back(cell);
    return;
}
void CellSimulation::growCells(vector<Cell> cells) {
    vector<Cell>::iterator i;
    for (i = cells.begin(); i == cells.end(); ++i)
        AllCells[i->getType()].push_back(*i);
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
    int i;
    double scale;
    double theta,phi;
    double ranThetaAngle,ranPhiAngle;
    double alignThetaAngle,alignPhiAngle;
    double dx,dy,dz;
    double dx2,dy2,dz2;
    double x,y,z;
    double xAttr,yAttr,zAttr;
    double totalPhiAngle=0,totalThetaAngle = 0;
    double xMin,yToXMin,zToXMin;
    Cell cellM;
    int jattract;
    cout << "IN PLACENEWCELL" << endl;
    cout << (long) oldCell.getLinkCellDown() <<endl;
    if (oldCell.getLinkCellDown() == (Cell *) NULL) {
        cout << "##$$## NEW CELL 1 first " << first << endl;
        cout << "SubType " << oldCell.to_String(oldCell.getSubType())  << " FIRST " << first << endl;
        if (first == false) {
            cout << "RETURN oldCell.getLinkCellDown()" << endl;
            return;

        }
        if (oldCell.getSubType() == SubTypes::INTERMEDIATE) {
            newCell.setCellCount(newCell.getCellCount() - 1);
            cout << "RETURN Cell.getSubType() == SubTypes::INTERMEDIATE" << endl;
            return;
        }
        cout << "BEFORE newCell" << endl;
        newCell.setCoords(Transform::translate(0., 1. * getStepLength(), 0.,oldCell.getCoords()));
        cout << "AFTER newCell" << endl;
        first = false;
    }
    else {
        if (cellGrowthCount <= 1) {
            cout << "RETURN Cell.getSubType() == SubTypes::INTERMEDIATE" <<endl;
            return;
        }
        if (getNumCellsToMain(oldCell) > MAX_NUM_CELLS_BRANCH) {
            cout << "RETURN getNumCellsToMain(oldCell)" <<endl;
            return;
        }
        // cout << "OLD CELL SUB TYPE " << oldCell.to_String(oldCell.getSubType) << endl;
        oldOldCell = *oldCell.getLinkCellDown();
        scale = scaleFactor(oldCell, oldOldCell);
        if ((oldCell.getSubType() == SubTypes::MAIN_R) ||
                (oldCell.getSubType() == SubTypes::MAIN_L) ||
                (oldCell.getSubType() == SubTypes::MAIN_C) ||
                (cellGrowthCount <= 2)) {
            newCell.setCoords(Transform::translate(0., getStepLength(), 0.,ZERO_COORDS));
        } else if (oldCell.getSubType() == SubTypes::MAIN) {
            newCell.setCoords(Transform::translate(ZERO_COORDS, 0., getStepLength(), 0.));
        } else {
            /* if newCell is a cell of subtype LAST, then make it 25 % the length of other normal cells */
            if (newCell.getSubType() == SubTypes::LAST) {
                newCell.setCoords(Transform::translate(ZERO_COORDS, 0.,getBranchStepLength() * 0.25, 0.));
            } else {
                /* if normal cell iteration count is >= 7 cut the distance from oldCell to newCell by 50% */
                if (cellGrowthCount >= 7) {
                    newCell.setCoords(Transform::translate(ZERO_COORDS, 0.,getBranchStepLength() * 0.5, 0.));
                } else {
                    newCell.setCoords(Transform::translate(ZERO_COORDS, 0., getBranchStepLength(), 0.));
                }
            }
        }
        /* vector between new and old cell */
        dx = ((oldCell.getCoordX() - oldOldCell.getCoordX()) / scale) * getStepLength();
        dy = ((oldCell.getCoordY() - oldOldCell.getCoordY()) / scale) * getStepLength();
        dz = ((oldCell.getCoordZ() - oldOldCell.getCoordZ()) / scale) * getStepLength();
        /* angle relative to Y axis of vector defined by oldCell and oldoldCell */
        phi   = getCalculatedPhiAngle(dx, dy, dz);
        theta = getCalculatedThetaAngle(dx, dy, dz);

        if ((oldCell.getSubType() == SubTypes::MAIN_R) ||
                (oldCell.getSubType() == SubTypes::MAIN_L) ||
                (oldCell.getSubType() == SubTypes::MAIN_C) ||
                (oldCell.getSubType() == SubTypes::MAIN)) {
            /* see the getMainRandomAngle and getRandomAngle methods for a description */
            ranPhiAngle = getMainRandomAngle();
            ranThetaAngle = getMainRandomAngle();
        } else {
            ranPhiAngle = getRandomAngle();
            ranThetaAngle = getRandomAngle();

            // cout << "RANDOM ANGLE " << ranAngle << endl;
        }
        /* set the cell SubType */
        if (cellGrowthCount == 2) {
            /* for cells # 2 and #3, create two MAIN branches (MAIN_R and MAIN_L) */
            switch (icount) {
            case 0:
                ranThetaAngle = -getSpreadAngle() / 2.;
                ranPhiAngle = 0.;
                // cout << "NEW CELL NUMBER " << newCell.getCellNumber() << " CELL TYPE " << newCell.to_String(newCell.getType()) << " CELL SUBTYPE " << newCell.to_String(newCell.getSubType()) << endl;
                newCell.setSubType(SubTypes::MAIN_L);
                // cout << " CHANGE TO CELL SUBTYPE " << newCell.getSubType()) << endl;
                break;

            case 1:
                ranThetaAngle = getSpreadAngle() / 2.;
                ranPhiAngle = 0;
                // cout << "NEW CELL NUMBER " << newCell.getCellNumber() << " CELL TYPE " << newCell.to_String(newCell.getType()) << " CELL SUBTYPE " << newCell.getSubType()) << endl;
                newCell.setSubType(SubTypes::MAIN_R);
                // count << " CHANGE TO CELL SUBTYPE " << newCell.getSubType()) << endl;
                break;
            case 2:
                ranThetaAngle = 0.;
                ranPhiAngle = 0.;
                // count << "NEW CELL NUMBER " << newCell.getCellNumber() << " CELL TYPE " << newCell.to_String(newCell.getType()) << " CELL SUBTYPE " << newCell.to_String(newCell.getSubType()) < endl;
                newCell.setSubType(SubTypes::MAIN_C);
                // count << " CHANGE TO CELL SUBTYPE " << newCell.to_String(newCell.getSubType()) << endl;
                break;
            }
        }
        else if ((oldCell.getSubType() == SubTypes::MAIN_R) || (oldCell.getSubType() == SubTypes::MAIN_L) || (oldCell.getSubType() == SubTypes::MAIN_C)) {
            // System.out.println("MAIN SWITCH");
            if (oldCell.getSubType() == SubTypes::MAIN_R) {
                // cout << "NEW CELL NUMBER " << newCell.getCellNumber() << " CELL TYPE " << newCell.to_String(newCell.getType()) << " CELL SUBTYPE " << newCell.to_String(newCell.getSubType()) << endl;
                newCell.setSubType(SubTypes::MAIN_R);
                // cout <<  " CHANGE TO CELL SUBTYPE " << newCell.to_String(newCell.getSubType()) << end;;
            } else if (oldCell.getSubType() == SubTypes::MAIN_L) {
                // cout << "NEW CELL NUMBER " << newCell.getCellNumber() << " CELL TYPE " << newCell.to_String(newCell.getType()) << " CELL SUBTYPE " << newCell.to_String(newCell.getSubType()) << endl;
                newCell.setSubType(SubTypes::MAIN_L);
                // count << " CHANGE TO CELL SUBTYPE " << newCell.getSubType()) << endl;
            } else if (oldCell.getSubType() == SubTypes::MAIN_C) {
                // cout << "NEW CELL NUMBER " << newCell.getCellNumber() << " CELL TYPE " << newCell.to_String(newCell.getType()) << " CELL SUBTYPE " << newCell.to_String(newCell.getSubType()) << endl;
                newCell.setSubType(SubTypes::MAIN_C);
                // cout << " CHANGE TO CELL SUBTYPE " << newCell.getSubType()) << endl;
            }

            // cout << "OLD CELL NUMBER " << oldCell.getCellNumber() << " CELL TYPE " << oldCell.getType() << " CELL SUBTYPE " << oldCell.getSubType()) << endl;
            oldCell.setSubType(SubTypes::MAIN);
            // cout << " CHANGE TO CELL SUBTYPE " << oldCell.getSubType()) << endl;
        } else if (oldCell.getSubType() != SubTypes::MAIN && oldCell.getSubType() != SubTypes::MAIN_L && oldCell.getSubType() != SubTypes::MAIN_R && oldCell.getSubType() != SubTypes::MAIN_C) {
            if ((oldCell.getGrowthCount() >= getMaxIntermediateBranch()) && (cellGrowthCount >= 2)) {
                // cout << "OLD CELL NUMBER " << oldCell.getCellNumber() << " CELL TYPE " << oldCell.getType() << " CELL SUBTYPE " << oldCell.getSubType()) << endl;
                oldCell.setSubType(SubTypes::SNORMAL);
                // cout << " CHANGE TO CELL SUBTYPE " << oldCell.getSubType()) << endl;
            } else if (oldCell.getSubType() != SubTypes::INTERMEDIATE) {
                // cout << "OLD CELL NUMBER " << oldCell.getCellNumber() << " CELL TYPE " << oldCell.getType() << " CELL SUBTYPE " << oldCell.getSubType()) <<endl;
                oldCell.setSubType(SubTypes::INTERMEDIATE);
                // cout << " CHANGE TO CELL SUBTYPE " << oldCell.getSubType()) << endl;
            }
        }
        /* increment count of cells grown from oldCell */
        oldCell.setGrowthCount(oldCell.getGrowthCount() + 1);

        // if(getAttractiveCellTotal() > 0 && oldCell.getSubType() == SubTypes.MAIN)
        jattract = -1;

        /* direct growth towards attractive cells */


        if ((getAttractiveCellTotal() > 0) && (newCell.getSubType() != SubTypes::LAST)) {
            x = oldCell.getCoordX();
            y = oldCell.getCoordY();
            z = oldCell.getCoordZ();

            /* distance table  from attactive cell i to normal cell */
            for (i = 0; i < getAttractiveCellTotal(); ++i) {
                cellM = getAttractiveCell(i);
                xAttr = cellM.getCoordX();
                yAttr = cellM.getCoordY();
                zAttr = cellM.getCoordZ();
                dx2 = x - xAttr;
                dy2 = y - yAttr;
                dz2 = z - zAttr;
                distVec.push_back(DistNo(i,sqrt((dx2 * dx2) + (dy2 * dy2) + (dz2*dz2))));
            }
            sortThem(distVec);
            DistNo tempDistNo = distVec.at(0);
            jattract = tempDistNo.getI();
            xMin = getAttractiveCell(jattract).getCoordX();
            yToXMin = getAttractiveCell(jattract).getCoordY();
            zToXMin = getAttractiveCell(jattract).getCoordZ();
            dx = xMin - x;
            dy = yToXMin - y;
            dz = yToXMin - z;
            alignPhiAngle = getCalculatedPhiAngle(dx, dy,dz);
            alignThetaAngle = getCalculatedThetaAngle(dx, dy,dz);
            alignPhiAngle /= DTR;
            alignThetaAngle /= DTR;
            newCell.setCoords(Transform::rotate(0,0,1,alignThetaAngle,newCell.getCoords()));
            newCell.setCoords(Transform::rotate(0,0,1,alignPhiAngle,newCell.getCoords()));
            totalPhiAngle += alignPhiAngle;
            totalThetaAngle += alignThetaAngle;
        }
    }
    growCell(newCell);
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

    cout << "currentIter " << currentIter << endl;
    cout << "getCellSkip " << getCellSkip() << endl;
    cout << "getIter " << getIter() << endl;

    if (((currentIter % getCellSkip()) == 0) && (currentIter < getIter())) {
        ++cellGrowthCount;
        cout << "initSize " << initSize << endl;

        /* loop over all normal cells: grow new ones */
        for (j = 0; j < initSize; ++j)
            currentAlgorithm((Cell) AllCells[Types::NORMAL][j]);

        setStepLength(getStepLength() * getFraction());
        setBranchStepLength(getBranchStepLength() * getFraction());
        if ((cellGrowthCount * getCellSkip()) == iter) {
            updateLastCellList();
        }
    }

    // cout << "CURRENTITER " << currentIter <<endl;

    /* move metanephric cells */
    if (currentIter > START_METANEPHRIC_CELLS) {
        if (debug)
            cout << "IN MOVEMETANEPHRIC CELLS" << ++updateCount <<endl;
        moveMetanenephricCells();
    }
}
int CellSimulation::getNormalCellTotal()
{
    return(AllCells[Types::NORMAL].size());
}
void CellSimulation::placeMetanephricCells()
{
    double x,y,z;

    for (int j = 0; j < NUM_METANEPHRIC_CELLS; ++j) {
        x = (iter * .7 * (-0.5 +  (double) (rand()/RAND_MAX))) / getCellSkip();
        y = (iter * .7 * (-0.5 +  (double) (rand()/RAND_MAX))) / getCellSkip();
        z = (iter * .7 *  (double) (rand()/RAND_MAX)) / getCellSkip();
        AllCells[Types::METANEPHRIC].push_back(Cell(x,
                                               getFraction() + y, getFraction()+z, Types::METANEPHRIC, SubTypes::SNORMAL));
    }
}
void CellSimulation::currentAlgorithm(Cell cell)
{
    int number;
    int direction;
    int i;
    int j;
    cout << " ALGORITHM ITER " << cellGrowthCount << " CELL NUMBER " << cell.getCellNumber() << " SubType " << cell.to_String(cell.getSubType()) <<endl;

    switch (cell.getSubType())
    {
    case SubTypes::SNORMAL:
        break;

    case SubTypes::MAIN_R:
    case SubTypes::MAIN_L:
    case SubTypes::MAIN_C:
    case SubTypes::MAIN:
        /* randomly pick one or 2 cells to grow out of MAIN cell */
        number = (int)((double) (rand()/RAND_MAX) * getMaxBranch()) + 1;

        if (cellGrowthCount == 2) {
            number = 2;
        }

        if ((cellGrowthCount > 2) && cell.getCellNumber() <= 3) {
            return;
        }

        if (cell.getLinkCellDown() == (Cell *) NULL) {
            number = 1;
        }

        for (i = 0; i < number; ++i) {
            // System.out.println("MAIN CELL " + cell.getSubType());
            if (cell.getGrowthCount() < getMaxBranch()) {

                /* grow a new cell */

                cout << "##$$##  1 CALL placeNewCell" <<endl;
                placeNewCell(cell, Cell(cell, SubTypes::END, cell), i);

                // System.out.println("SWITCH TO CELL TYPE " + cell.getSubType());
                if ((cell.getSubType() == SubTypes::SNORMAL) ||
                        (cell.getSubType() == SubTypes::INTERMEDIATE)) {
                    break;
                }
            } else {
                break;
            }
        }

        break;

    case SubTypes::END:
    case SubTypes::INTERMEDIATE:

        /* randomly pick one or 2 cells to grow out of END or INTERMEDIATE cell */

        number = (int)((double) (rand()/RAND_MAX) * getMaxBranch()) + 1;

        if (cellGrowthCount == 2) {
            number = 2;
        }

        if ((cellGrowthCount > 2) && cell.getCellNumber() <= 3) {
            return;
        }

        if (cell.getLinkCellDown() == (Cell *) NULL) {
            number = 1;
        }

        if (debug)
            cout << "CELLGROWTHCOUNT*SKIP " <<
                 (cellGrowthCount * getCellSkip()) <<  " ITER " << (iter - 1) << endl;

        if (((cellGrowthCount * getCellSkip()) >= iter) &&
                (cell.getSubType() == SubTypes::END)) {
            for (i = 0; i < 2; ++i) {
                if (cell.getGrowthCount() < getMaxIntermediateBranch()) {
                    cout << "##$$##  2 CALL placeNewCell" <<endl;
                    placeNewCell(cell,Cell(cell, SubTypes::LAST, cell),
                                 i);
                } else {
                    break;
                }
            }
        } else {
            for (i = 0; i < number; ++i) {
                if (cell.getGrowthCount() < getMaxIntermediateBranch()) {
                    cout << "##$$##  3 CALL placeNewCell" <<endl;
                    placeNewCell(cell, Cell(cell, SubTypes::END, cell), i);
                } else {
                    break;
                }
            }
        }

        break;
    case SubTypes::LAST:
        break;
    }
}
void CellSimulation::updateLastCellList()
{
    Cell cellTemp;
    vector<Cell>::iterator i;

    for (i = AllCells[Types::NORMAL].begin(); i == AllCells[Types::NORMAL].end();  ++i) {
        cellTemp = *i;
        if (cellTemp.getSubType() == SubTypes::LAST) {
            lastCells.push_back(cellTemp);
        }
    }

}
void CellSimulation::moveMetanenephricCells()
{
}
void CellSimulation::printSimulationStep()
{
    vector<Cell>::iterator i;

    for (i = AllCells[Types::NORMAL].begin(); i == AllCells[Types::NORMAL].end();  ++i)
        cout << i->toString() << endl;
}
double CellSimulation::getCalculatedPhiAngle(double dx, double dy,double dz)
{
    return(acos(dz/sqrt(dx*dx+dy*dy+dz*dz)));
}
double CellSimulation::getCalculatedThetaAngle(double dx, double dy,double dz)
{
    return(atan2(dy,dx));
}
int CellSimulation::getAttractiveCellTotal()
{
    return(AllCells[Types::ATTRACTIVE].size());
}
Cell CellSimulation::getAttractiveCell(int i)
{
    return(AllCells[Types::ATTRACTIVE].at(i));
}
CellSimulation::DistNo::DistNo(int no, double d)
{
    i = no;
    dist = d;
}
void CellSimulation::DistNo::setDist(double d)
{
    dist = d;
}
double CellSimulation::DistNo::getDist()
{
    return(dist);
}
void CellSimulation::DistNo::setI(int no)
{
    i = no;
}
int CellSimulation::DistNo::getI()
{
    return(i);
}
string CellSimulation::DistNo::toString()
{
    string out = to_string(i);
    out += " " + to_string(dist);
    return(out);
}
CellSimulation::DistNo::DistNo()
{
    i = 0;
    dist = 0.;
}
void CellSimulation::sortThem(vector<DistNo> distVec)
{
    DistNo temp1;
    DistNo temp2;
    vector<DistNo>::iterator i,j;
    for (i = distVec.begin() ; i == distVec.end(); ++i) {
        for (j = i + 1; j == distVec.end(); ++j) {
            temp1 = *i;
            temp2 = *j;
            if (temp2.getDist() < temp1.getDist()) {
                distVec.erase(j);
                distVec.insert(j+1,temp1);
                distVec.erase(i);
            }
        }
    }
}
void CellSimulation::placeAttractiveCells()
{
    double thetaAngle;
    double phiAngle;
    double x,y,z;

    for (int j = 0, phiAngle = 30; j < CellSimulation::NUM_ATTRACTIVE_CELLS; ++j,phiAngle += (12/CellSimulation::NUM_ATTRACTIVE_CELLS))
            for (int i = 0, thetaAngle = 30; i < CellSimulation::NUM_ATTRACTIVE_CELLS; ++i,thetaAngle += (12/CellSimulation::NUM_ATTRACTIVE_CELLS))
            {
             x = attractiveRadius * cos(phiAngle * DTR)*cos(thetaAngle*DTR);
             y = attractiveRadius * cos(phiAngle * DTR)*sin(thetaAngle*DTR);
             z = attractiveRadius * sin(phiAngle * DTR);
             AllCells[Types::ATTRACTIVE].push_back(Cell(x,y,z,Types::ATTRACTIVE,SubTypes::SNORMAL));
           }
}
