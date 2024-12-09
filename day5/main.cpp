#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "part1.h"
#include "part2.h"

using namespace std;

int main()
{
  ifstream inputFile("test.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  /**
   * read in input file
   */
  // 2D adjacency matrix graph where [r][c] = r must be before c
  size_t size = 100;
  vector<vector<int>> rules(size, vector<int>(size, 0));
  vector<vector<int>> updates;

  string line;
  while (getline(inputFile, line) && !line.empty())
  {
    stringstream ss(line);
    int a, b;
    char l;
    ss >> a >> l >> b;
    rules[a][b] = 1;
  }
  while (getline(inputFile, line))
  {
    stringstream ss(line);
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
  inputFile.close();

  /**
   * Part 1
   */
  vector<int> invalidUpdates;
  int result1 = sumMiddlePages(rules, updates, invalidUpdates);
  cout << "Part 1 Result: " << result1 << endl;

  /**
   * Part 2
   */
  int result2 = sumMiddleFixed(rules, updates, invalidUpdates);
  cout << "Part 2 Result: " << result2 << endl;

  return 0;
}
