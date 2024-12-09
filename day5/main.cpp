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

  /**
   * read in input file
   */
  string line;
  vector<vector<int>> rules;
  vector<vector<int>> updates;
  bool isRules = true;
  while (getline(inputFile, line))
  {
    if (line.empty())
    {
      isRules = false;
      continue;
    }
    stringstream ss(line);
    if (isRules)
    {
      int a, b;
      char l;
      ss >> a >> l >> b;
      rules.push_back({a, b});
    }
    else
    {
      int x;
      char c;
      vector<int> pages;
      while (ss >> x)
      {
        pages.push_back(x);
        ss >> c;
      }
      updates.push_back(pages);
    }
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
