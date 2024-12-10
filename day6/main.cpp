#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "part1.h"

using namespace std;

/*
INFO: yes i know my solution is overly complicated and probably less
efficient than optimal, but i was going for space efficiency here.
I wanted to avoid storing the entire grid in memory, instead only
storing the locations of walls.
not sure if it was worth it, but it was a fun exercise.
*/

int main()
{
  ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  /**
   * read in input file
   */
  // for each row, a list of indices where walls occur
  vector<vector<int>> rowToCol;
  // for each col, a list of indices where walls occur
  vector<vector<int>> colToRow;

  // start
  char startDir;
  pair<int, int> startPos;

  string line;
  int r = 0;
  while (getline(inputFile, line))
  {
    // init row
    rowToCol.push_back(vector<int>());
    // look through all cols for walls
    for (int c = 0; c < line.size(); c++)
    {
      // first row, init vec for each col
      if (r == 0)
      {
        colToRow.push_back(vector<int>());
      }
      // add walls
      if (line[c] == '#')
      {
        rowToCol[r].push_back(c);
        colToRow[c].push_back(r);
      }
      // starting pos
      else if (line[c] == '<' || line[c] == '>' || line[c] == '^' || line[c] == 'v')
      {
        startDir = line[c];
        startPos = {r, c};
      }
    }
    r++;
  }
  inputFile.close();

  /**
   * Part 1
   */
  PatrolGuard pg = PatrolGuard(rowToCol, colToRow, startDir, startPos);
  int result1 = pg.countVisitedPosns();
  cout << "Part 1 Result: " << result1 << endl;

  /**
   * Part 2
   */
  int result2 = pg.countPossibleObstructions();
  cout << "Part 2 Result: " << result2 << endl;

  return 0;
}
