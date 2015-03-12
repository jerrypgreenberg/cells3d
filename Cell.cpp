#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <type_traits>
using namespace std;

int Cell::cellCount = 0;
Cell::Cell() {
        setCoords(0., 0., 0.);
        setType(Types::NORMAL);
        setSubType(SubTypes::SNORMAL);
        setCellCount(getCellCount() + 1);
        setCellNumber(getCellCount());
        for(int i=0;i<3;++i)
           dock[i] = 0.;
        growthCount = 0;
}
Cell::Cell(double x, double y, double z, SubTypes stype) {
        setCoords(x, y, z);
        setType(Types::NORMAL);
        setSubType(stype);
        setCellCount(getCellCount() + 1);
        setCellNumber(getCellCount());
        setPeriodicType(PeriodicType::PNORMAL);
        setAddedType(AddedType::ANORMAL);
        setLinkCellDown((Cell *) NULL);
        for(int i=0;i<3;++i)
           dock[i] = 0.;
        growthCount = 0;
        // System.out.println("CELL NUMBER " + getCellNumber() + " CELL TYPE " + getType() + " CELL SUBTYPE " + getSubType());
    }
Cell::Cell(double x, double y, double z, Types type, SubTypes stype) {
        setCoords(x, y, z);
        setType(type);
        setSubType(stype);
        setCellCount(getCellCount() + 1);
        setCellNumber(getCellCount());
        setPeriodicType(PeriodicType::PNORMAL);
        for(int i=0;i<3;++i)
           dock[i] = 0.;
        growthCount = 0;
        cout << "CELL NUMBER " << getCellNumber() << " CELL TYPE " << to_string(getType()) << " CELL SUBTYPE " << to_string(getSubType()) << endl;
}
Cell::Cell(Cell cell, SubTypes stype, Cell down) {
        setCoords(cell.getCoords());
        setLinkCellDown(&down);
        setType(cell.getType());
        setSubType(stype);
        setCellCount(getCellCount() + 1);
        setCellNumber(getCellCount());
        for(int i=0;i<3;++i)
           dock[i] = 0.;
        growthCount = 0;
        // System.out.println("CELL NUMBER " + getCellNumber() + " CELL TYPE " + getType() + " CELL SUBTYPE " + getSubType());
}
void Cell::setCoords(double* coor) {
        int i;
        for (i = 0; i < 3; ++i)
            coords[i] = coor[i];
}
/** return cell coordinates as an array **/
double* Cell::getCoords() {
        return (coords);
}
/** copy coordinates to an array **/
double* Cell::copyCoords() {
        double *copyCoords = new double[3];
        copyCoords[0] = getCoordX();
        copyCoords[1] = getCoordY();
        copyCoords[2] = getCoordZ();
        return (copyCoords);
}
   
    /** set cell coordinates given x,y,z **/
void Cell::setCoords(double coorX, double coorY, double coorZ) {
        coords[0] = coorX;
        coords[1] = coorY;
        coords[2] = coorZ;
}
/** return the x coordinate **/
double Cell::getCoordX() {
        return (coords[0]);
}
/** return the y coordinate **/
double Cell::getCoordY() {
        return (coords[1]);
}
/** return the z coordinate **/
double Cell::getCoordZ() {
      return (coords[2]);
}
/** set the x coordinate **/
void Cell::setCoordX(double x) {
        coords[0] = x;
}
/** set the y coordinate **/
void Cell::setCoordY(double y) {
        coords[1] = y;
}
/** set the z coordinate **/
void Cell::setCoordZ(double z) {
        coords[2] = z;
}
void Cell::setType(Types ttype) {
        type = ttype;
}
/** return the  main type of this cell **/
Types Cell::getType() {
       return (type);
}
/** set the sub type of this cell **/
void Cell::setSubType(SubTypes tsubType) {
      subType = tsubType;
}
/** get the sub type of this cell **/
SubTypes Cell::getSubType() {
        return (subType);
}
/** set the number of this cell **/
void Cell::setCellCount(int count) {
     cellCount = count;
}
/** get the cell number for this cell **/
int Cell::getCellCount() {
     return (cellCount);
 }
void Cell::setCellNumber(int cNumber) {
        cellNumber = cNumber;
}
/** get the cell number of this cell **/
int Cell::getCellNumber() {
      return (cellNumber);
}
/** return instance variables **/
string Cell::toString() {
        string returnString;
        returnString = "Cell # " + to_string(getCellNumber()) + " " + to_String(getType()) + " " + to_String(getSubType()) + " Coords " + to_string(getCoordX()) + " " + to_string(getCoordY()) + " " + to_string(getCoordZ());
        vector<Cell>::iterator c;
        for (c = linkCellUp.begin(); c != linkCellUp.end(); c++) {
             returnString += " CellUp " + to_string(c->getCellNumber());
        }
        returnString += " Cell Branch " + to_string(getGrowthCount());
        return (returnString);
}
/** set an angle for a child cell **/
void Cell::setAngle(double a)
{
      angles.push_back(a);
} 
/** get ith angle for a child cell **/
double Cell::getAngle(int i)
{
       return(angles[i]);
} 
/** return the number of angles in the angle Vector **/
int Cell::getAngleSize()
{
       return(angles.size());
}
/** add a cell to the attractive cell list **/
void Cell::addAttractCells(Cell addCell) {
      attractCells.push_back(addCell);
}
/** return the last attractive cell in the list **/
Cell Cell::getLastAttractCell() {
      try
      {
          return ((Cell) attractCells[attractCells.size() - 1]);
      }
      catch(exception& e)     
      {
          cout <<e.what() << endl;
          exit(-1);
      }
}
/** get the ith attractive cell **/
Cell Cell::getAttractCell(int i) {
        return (attractCells[i]);
}
/** return the number of attractive cells **/
int Cell::getNumberOfAttractCells() {
        return (attractCells.size());
}
/** bind this cell **/
void Cell::setBoundCell(Cell bCell) {
     boundCell = &bCell;
     ++nBoundCell;
}
/** return the cell this cell is bound to **/
Cell Cell::getBoundCell() {
    return (*boundCell);
}
void Cell::setNormalBoundCell(Cell bCell) {
    normalBoundCell = &bCell;
}
/** return the cell this cell is bound to **/
Cell Cell::getNormalBoundCell() {
    return (*normalBoundCell);
}
/**  set the periodic type of this cell **/
void Cell::setPeriodicType(PeriodicType newpType) {
     pType = newpType;
}
/**  return the periodic type of this cell **/
PeriodicType Cell::getPeriodicType() {
     return (pType);
}
/**  set the added type of this cell **/
void Cell::setAddedType(AddedType newaType) {
     aType = newaType;
}
/**  return the added type of this cell **/
AddedType Cell::getAddedType() {
     return (aType);
}
/** set the docked coordinates  given a coordinate set **/
void Cell::setDock(double x, double y, double z) {
     dock[0] = x;
     dock[1] = y;
     dock[2] = z;
}
/** set the docked coordinates  given an array **/
void Cell::setDock(double *xyz) {
     dock[0] = xyz[0];
     dock[1] = xyz[1];
     dock[2] = xyz[2];
}
/** return the docked coordinates **/
double* Cell::getDock() {
     return (dock);
}
/** get a dock coordinate **/
double Cell::getDock(int i) {
     if (i <= 2 && i >= 0)
          return (dock[i]);
      else {
         cerr << "Bad dock reference" <<endl;
         exit(-1);
         return (-1.);
      }
}
double Cell::getMangle()
{
     return(mAngle);
}
void Cell::setMangle(double inAngle)
{
     mAngle = inAngle;
}
Cell Cell::getTestCell()
{
   return(*testCell);
}
void Cell::setTestCell(Cell tCell)
{
     testCell = &tCell;
}
Cell* Cell::getLinkCellDown()
{
     return (linkCellDown);
}
void Cell::setLinkCellDown(Cell *down)
{
     linkCellDown = down;
}
const string Cell::to_String(SubTypes s)
{
    switch(s)
    {
       case SubTypes::SNORMAL:
          return("PNORMAL");
          break;
       case SubTypes::END:
          return("END");
          break;
       case SubTypes::INTERMEDIATE:
          return("INTERMEDIATE");
          break;
       case SubTypes::MAIN_R:
          return("MAIN_R");
          break;
       case SubTypes::MAIN_L:
          return("MAIN_L");
          break;
       case SubTypes::MAIN_C:
          return("MAIN_C");
          break;
       case SubTypes::MAIN:
          return("MAIN");
          break;
       case SubTypes::LAST:
          return("LAST");
          break;
    }   
}
const string Cell::to_String(PeriodicType p)
{
    switch(p)
    {
       case PeriodicType::PNORMAL:
          return("PNORMAL");
          break;
       case PeriodicType::CROSSED:
          return("CROSSED");
          break;
    }   
}
const string Cell::to_String(AddedType a)
{
    switch(a)
    {
       case AddedType::ANORMAL:
          return("ANORMAL");
          break;
       case AddedType::ADDED:
          return("ADDED");
          break;
    }   
}
const string Cell::to_String(Types t)
{
    switch(t)
    {
       case Types::NORMAL:
          return("NORMAL");
          break;
       case Types::METANEPHRIC:
          return("METANEPHRIC");
          break;
       case Types::ATTRACTIVE:
          return("ATTRACTIVE");
          break;
    }   
}
int Cell::traceCellDownNum() {
        Cell currentCell = *this;
        int cCount = 1;
        while (currentCell.getLinkCellDown() != (Cell*) NULL) {
            currentCell = *currentCell.getLinkCellDown();
            ++cCount;
        }
        return (cCount);
}
vector<Cell> Cell::traceCellDown() {
        Cell currentCell = *this;
        vector<Cell> cellList;
        cellList.push_back(currentCell);
        while (currentCell.linkCellDown != NULL) {
            cellList.push_back(*currentCell.getLinkCellDown());
            currentCell = *currentCell.getLinkCellDown();
        }
        return (cellList);
}
int Cell::getGrowthCount()
{
        return (growthCount);
}
void Cell::setGrowthCount(int growth)
{
        growthCount = growth;
}
