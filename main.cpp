#include <iostream>
#include "MazeSolver.h"
#include <fstream>
#include <string>
using namespace std;

int main() {
  //cout<<"before main file"<<endl;
  MazeSolver solver("inputA.txt");
  //cout<<"after main file"<<endl;

  if(solver.mazeIsReady())
  {
    solver.solveMaze();
    solver.printSolution();
  }


  return 0;
}
