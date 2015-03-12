#ifndef _CELL_H_
#define _CELL_H_
#include<vector>
#include<string>
#include "CTypes.h"
class Cell {
    private:
        /** maximum number of cells **/
        static const int MAX_BRANCH = 1000;
        /** Types enum variable **/
        int cellNumber;
        Types type;
        /** SubTypes enum variable **/
        SubTypes subType;
        /** 3d coord array **/
        double coords[4];
        /** cell that the current cell has "grown" from **/
       /** cells grown after this one that are linked to it  (currently not used) **/
        std::vector<Cell> linkCellUp;
        /** number assigned to this cell **/
        int growthCount;
        Cell *testCell;
         /** cell this cell is bound to (if this is a metanephric cell **/
        Cell *boundCell;
        Cell *linkCellDown = NULL;
        int nBoundCell;
        Cell *normalBoundCell;
        /** metaneprhic cells bound to this cell **/
        std::vector<Cell> attractCells;
        /** angles between cell and child cells (only 1 element used )**/
        std::vector<double> angles;
        /** PeriodicType enum variable **/
        PeriodicType pType;
        /** AddedType enum variable **/
        AddedType aType;
        /**  docked metanephric cell coordinates **/
        double dock[4];
        double mAngle;
    public:
        /** total number of cells **/

        Cell();
        Cell(double x, double y, double z, SubTypes stype);
        Cell(double x, double y, double z, Types type, SubTypes stype);
        Cell(Cell cell, SubTypes stype, Cell down);
        void setCoords(double* coor);
        double* getCoords();
        double* copyCoords();
        void setCoords(double coorX, double coorY, double coorZ);
        double getCoordX();
        /** return the y coordinate **/
        double getCoordY();
        /** return the z coordinate **/
        double getCoordZ();
        /** set the x coordinate **/
        static int cellCount;
        void setCoordX(double x);
        void setCoordY(double y);
        void setCoordZ(double z);
        void setType(Types ttype);
        /** return the  main type of this cell **/
        Types getType();
        void setSubType(SubTypes tsubType);
        /** get the sub type of this cell **/
        SubTypes getSubType();
        /** set the number of this cell **/
        static void setCellCount(int count);
        /** get the cell number for this cell **/
        static int getCellCount();
        /** set how many cells have grown from this cell **/
        void setGrowthCount(int growth);
        /** get how many cells have grown from this cell **/
        int getGrowthCount();
       /** return a list of cells that trace the lineage of this cell **/
        std::vector<Cell> traceCellDown();
        int traceCellDownNum();
        /** set the cell number of this cell **/
        void setCellNumber(int cNumber);
        /** get the cell number of this cell **/
        int getCellNumber();
         /** return instance variables **/
        std::string toString();
         /** set an angle for a child cell **/
         void setAngle(double a);
         /** get ith angle for a child cell **/
         double getAngle(int i);
         /** return the number of angles in the angle Vector **/
         int getAngleSize();
         /** add a cell to the attractive cell list **/
         void addAttractCells(Cell addCell);
         /** return the last attractive cell in the list **/
         Cell getLastAttractCell();
         /** get the ith attractive cell **/
         Cell getAttractCell(int i);
         /** return the number of attractive cells **/
        int getNumberOfAttractCells();
         /** bind this cell **/
        void setBoundCell(Cell bCell);
        /** return the cell this cell is bound to **/
        Cell getBoundCell();
        void setNormalBoundCell(Cell bCell);
        /** return the cell this cell is bound to **/
        Cell getNormalBoundCell();
        /**  set the periodic type of this cell **/
        void setPeriodicType(PeriodicType newpType);
        /**  return the periodic type of this cell **/
        PeriodicType getPeriodicType();
        /**  set the added type of this cell **/
        void setAddedType(AddedType newaType);
        /**  return the added type of this cell **/
        AddedType getAddedType();
       /** set the docked coordinates  given a coordinate set **/
        void setDock(double x, double y, double z);
       /** set the docked coordinates  given an array **/
       void setDock(double* xyz);
       /** return the docked coordinates **/
       /** get a dock coordinate **/
       double* getDock();
       double getDock(int i);
       double getMangle();
       void setMangle(double inAngle);
       Cell getTestCell();
       void setTestCell(Cell tCell);
       Cell *getLinkCellDown();
       void setLinkCellDown(Cell *cell);
       const std::string to_String(SubTypes s);
       const std::string to_String(PeriodicType p);
       const std::string to_String(AddedType a);
       const std::string to_String(Types t);
       friend std::ostream& operator<<(std::ostream& os, SubTypes s);
       friend std::ostream& operator<<(std::ostream& os, PeriodicType p);
       friend std::ostream& operator<<(std::ostream& os, AddedType a);
       friend std::ostream& operator<<(std::ostream& os, Types t);
};
#endif
