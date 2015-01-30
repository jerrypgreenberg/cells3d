#include <iostream>
#include <vector>
#include <string>
#include "Cell.h"
std::vector <std::vector <Cell> > vec;
int main()
{
  void testthis(Cell cell);
  vec.resize(3);
  testthis(Cell(0., 0., 0., SubTypes::END));
}
void testthis(Cell cell)
{
  vec[0].push_back(cell);
  std::cout<< vec[0][0].toString() << std::endl;
}

