#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../utils.h"
#include "part1.h"
#include "part2.h"

using namespace std;

int main()
{
  ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  int result1 = 0;
  int result2 = 0;
  string line;
  bool enabled = true;
  while (getline(inputFile, line))
  {
    result1 += allMults(line);
    auto [res, e] = enabledMults(line, enabled);
    result2 += res;
    enabled = e;
  }
  inputFile.close();

  cout << "Part 1 Result: " << result1 << endl;
  cout << "Part 2 Result: " << result2 << endl;

  return 0;
}
