// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include "tokenscanner.h"

using namespace std;

void readDataIntoGrid(ifstream &infile, Grid<char> &life);
void displayGrid(const Grid<char> &life);
int calcNeighbors(int i, int j, const Grid<char> &life);
void updateToNextGen(Grid<char> &life);

int main() {
  //Welcome messages
  cout << "Welcome to the CS 106B Game of Life," << endl;
  cout << "a simulation of the lifecycle of a bacteria colony." << endl;
  cout << "Cells (X) live and die by the following rules:" << endl;
  cout << "- A cell with 1 or fewer neighbors dies." << endl;
  cout << "- Locations with 2 neighbors remain stable." << endl;
  cout << "- Locations with 3 neighbors will create life." << endl;
  cout << "- A cell with 4 or more neighbors dies." << endl << endl;

  ifstream infile;
  string filename = promptUserForFile(infile, "Grid input file name?");

  Grid<char> life;
  readDataIntoGrid(infile, life);
  displayGrid(life);
  cout << endl;
  updateToNextGen(life);
  displayGrid(life);
  
  //cout << calcNeighbors(0, 0, life) << endl;
  
  cout << "Have a nice Life!" << endl;
  return 0;
}


/* Function: readDataIntoGrid
 * Usage:    readDataIntoGrid(infile, life)
 * ----------------------------------------
 * Precondition:
 * Postcondition:
 */
void readDataIntoGrid(ifstream &infile, Grid<char> &life) {
  string line;

  // the following code relys on the
  // intial input file has correct format
  getLine(infile, line);
  int r = stringToInteger(line);
  getLine(infile, line);
  int c = stringToInteger(line);
  life.resize(r, c);
  
  int row = 0;

  while (true) {
    string line;
    getline(infile, line);

    // weird bug here
    // if (line == "") continue;
    // if (startsWith(line, "#")) continue;

    if (row < r) {
      for (int i = 0; i < line.length(); i++) {
	life.set(row, i, line[i]);
      }
      row++;
    }

    if (infile.fail()) break;
  }
}


void displayGrid(const Grid<char> &life) {
  for (int i = 0; i < life.numRows(); i++) {
    for (int j = 0; j < life.numCols(); j++) {
      cout << life[i][j];
    }
    cout << endl;
  }
}


/* Function: calcNeighbors
 * Usage:    int n = calcNeighbors(i, j life)
 * -------------------------------------------
 * Calculates how many of cell [i][j]'s neighbors
 * Has live cells in it. Note there are eight neightbors
 * In total, the cell itself should not be counted as neighbor
 * Also for some cells not all eight neighbors are within range
 * Precondtion:
 * Postcondition:
 */
int calcNeighbors(int i, int j, const Grid<char> &life) {
  int result = 0;
  if (life.inBounds(i-1, j) && life[i-1][j] == 'X') result++;
  if (life.inBounds(i+1, j) && life[i+1][j] == 'X') result++;
  if (life.inBounds(i, j-1) && life[i][j-1] == 'X') result++;
  if (life.inBounds(i, j+1) && life[i][j+1] == 'X') result++;
  if (life.inBounds(i-1, j-1) && life[i-1][j-1] == 'X') result++;
  if (life.inBounds(i-1, j+1) && life[i-1][j+1] == 'X') result++;
  if (life.inBounds(i+1, j-1) && life[i+1][j-1] == 'X') result++;
  if (life.inBounds(i+1, j+1) && life[i+1][j+1] == 'X') result++;

  return result;
}


/* Function: updateToNextGen
 * Usage:    updateToNextGen(life)
 * --------------------------------
 * Updates the grid to next generation
 * According to rules specified by handout
 * Precondition:
 * Postcondition:
 */
void updateToNextGen(Grid<char> &life) {
  // need this for temp storage since you don't
  // want to change the original while figuring out
  // what to do with each cell
  Grid<char> temp(life.numRows(), life.numCols());
  temp = life;

  for (int i = 0; i < temp.numRows(); i++) {
    for (int j = 0; j < temp.numCols(); j++) {
      if (calcNeighbors(i, j, life) < 2) {
	temp.set(i, j, '-');
      } else if (calcNeighbors(i, j, life) == 3) {
	temp.set(i, j, 'X');
      } else if (calcNeighbors(i, j, life) >= 4) {
	temp.set(i, j, '-');	
      }
    }
  }

  life = temp;
}

