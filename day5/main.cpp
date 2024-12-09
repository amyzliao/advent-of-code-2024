#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
// #include "part1.h"
// #include "part2.h"

using namespace std;

int main()
{
  ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  string line;
  vector<vector<char>> board;
  while (getline(inputFile, line))
  {
    stringstream ss(line);
    char c;
    vector<char> row;
    while (ss >> c)
    {
      row.push_back(c);
    }
    board.push_back(row);
  }
  inputFile.close();

  /**
   * Part 1
   */

  /**
   * Part 2
   */

  return 0;
}
