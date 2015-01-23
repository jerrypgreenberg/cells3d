#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <type_traits>
using namespace std;

int Cell::cellCount = 0;
Cell::Cell() {
        setCoords(0., 0., 0.);
        setType(Types::NORMAL);
        setSubType(SubTypes::NORMAL);
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
        setPeriodicType(PeriodicType::NORMAL);
        setAddedType(AddedType::NORMAL);
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
        setPeriodicType(PeriodicType::NORMAL);
        for(int i=0;i<3;++i)
           dock[i] = 0.;
        growthCount = 0;
        // System.out.println("CELL NUMBER " + getCellNumber() + " CELL TYPE " + getType() + " CELL SUBTYPE " + getSubType());
}
Cell::Cell(Cell cell, SubTypes stype, Cell down) {
        setCoords(cell.getCoords());
        setLinkCellDown(down);
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
void Cell::setLinkCellDown(Cell down)
{
     linkCellDown = &down;
}
ostream& operator<<(ostream& os, const SubTypes s)
{
    switch(s)
    {
       case SubTypes::NORMAL:
          os <<"NORMAL";
          break;
       case SubTypes::END:
          os <<"END";
          break;
       case SubTypes::INTERMEDIATE:
          os <<"INTERMEDIATE";
          break;
       case SubTypes::MAIN_R:
          os <<"MAIN_R";
          break;
       case SubTypes::MAIN_L:
          os <<"MAIN_L";
          break;
       case SubTypes::MAIN_C:
          os <<"MAIN_C";
          break;
       case SubTypes::MAIN:
          os <<"MAIN";
          break;
       case SubTypes::LAST:
          os <<"LAST";
          break;
    }   
    return(os);
}
ostream& operator<<(ostream& os, const PeriodicType p)
{
    switch(p)
    {
       case PeriodicType::NORMAL:
          os <<"NORMAL";
          break;
       case PeriodicType::CROSSED:
          os <<"CROSSED";
          break;
    }   
    return(os);
}
ostream& operator<<(ostream& os, const AddedType a)
{
    switch(a)
    {
       case AddedType::NORMAL:
          os <<"NORMAL";
          break;
       case AddedType::ADDED:
          os <<"ADDED";
          break;
    }   
    return(os);
}
ostream& operator<<(ostream& os, Types t)
{
    switch(t)
   {
      case Types::NORMAL:
          os << "NORMAL";
          break;
      case Types::METANEPHRIC:
         os <<"METANEPHRIC";
         break;
      case Types::ATTRACTIVE:
         os <<"ATTRACTIVE";
         break;
    }   
    return(os);
}
string Cell::to_String(SubTypes s)
{
    switch(s)
    {
       case SubTypes::NORMAL:
          return("NORMAL");
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
int Cell::to_Int(SubTypes s)
{
    switch(s)
    {
       case SubTypes::NORMAL:
          return(0);
          break;
       case SubTypes::END:
          return(1);
          break;
       case SubTypes::INTERMEDIATE:
          return(2);
          break;
       case SubTypes::MAIN_R:
          return(3);
          break;
       case SubTypes::MAIN_L:
          return(4);
          break;
       case SubTypes::MAIN_C:
          return(5);
          break;
       case SubTypes::MAIN:
          return(6);
          break;
       case SubTypes::LAST:
          return(7);
          break;
    }   
}
string Cell::to_String(PeriodicType p)
{
    switch(p)
    {
       case PeriodicType::NORMAL:
          return("NORMAL");
          break;
       case PeriodicType::CROSSED:
          return("CROSSED");
          break;
    }   
}
int Cell::to_Int(PeriodicType p)
{
    switch(p)
    {
       case PeriodicType::NORMAL:
          return(0);
          break;
       case PeriodicType::CROSSED:
          return(1);
          break;
    }   
}
string Cell::to_String(AddedType a)
{
    switch(a)
    {
       case AddedType::NORMAL:
          return("NORMAL");
          break;
       case AddedType::ADDED:
          return("ADDED");
          break;
    }   
}
int Cell::to_Int(AddedType a)
{
    switch(a)
    {
       case AddedType::NORMAL:
          return(0);
          break;
       case AddedType::ADDED:
          return(1);
          break;
    }   
}
string Cell::to_String(Types t)
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
int Cell::to_Int(Types t)
{
    switch(t)
    {
       case Types::NORMAL:
          return(0);
          break;
       case Types::METANEPHRIC:
          return(1);
          break;
       case Types::ATTRACTIVE:
          return(2);
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

