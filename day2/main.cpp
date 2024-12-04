#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/// @brief count the number of safe reports
/// @param reports
/// @return
int countSafe(vector<vector<int>> &reports)
{
  int count = 0;

  // each report: check if it's safe
  for (auto report : reports)
  {
    bool safe = true;
    // 'i'= increasing, 'd'= decreasing
    char direction = ' ';

    for (int i = 0; i < report.size() - 1; i++)
    {
      int curr = report[i];
      int next = report[i + 1];

      // all the invalid conditions
      if (false
          // adj levels differ by less than 1
          || abs(curr - next) < 1
          // adj levels differ by more than 3
          || abs(curr - next) > 3
          // increasing, but encounter a decrease
          || (direction == 'i' && next < curr)
          // decreasing, but encounter a increase
          || (direction == 'd' && next > curr))
      {
        safe = false;
        break;
      }

      // valid
      if (i == 0)
      {
        // set direction
        direction = (next > curr) ? 'i' : 'd';
      }
    }

    if (safe)
    {
      count++;
    }
  }

  return count;
}

/// @brief count the number of safe reports, with problem dampener
/// @param reports
/// @return
int countSafeDampener(vector<vector<int>> &reports)
{
  int count = 0;

  // each report: check if it's safe
  for (auto report : reports)
  {
    bool safe = true;
    int removals = 0;

    // track number of increases & decreases
    int increaseCount = 0;
    int decreaseCount = 0;

    for (int i = 0; i < report.size() - 1; i++)
    {
      int curr = report[i];
      int next = report[i + 1];

      // all the invalid conditions
      if (false
          // adj levels differ by less than 1
          || abs(curr - next) < 1
          // adj levels differ by more than 3
          || abs(curr - next) > 3)
      {
        // if removed previously, conclude unsafe
        if (removals > 0)
        {
          safe = false;
          break;
        }
        // perform removal (skip)
        removals++;
        continue;
      }

      // not removed, count inc/dec
      if (next > curr)
      {
        increaseCount++;
      }
      else
      {
        decreaseCount++;
      }
    }

    // 0 removals so far, we can tolerate 1 inc/dec difference
    if (removals == 0)
    {
      // if lower count > 1, unsafe
      int lower = (increaseCount > decreaseCount) ? decreaseCount : increaseCount;
      if (lower > 1)
      {
        safe = false;
      }
    }
    // 1 removal already, no tolerances
    else if (removals == 1)
    {
      // both nonzero, unsafe
      if (increaseCount > 0 && decreaseCount > 0)
      {
        safe = false;
      }
    }

    if (safe)
    {
      count++;
    }
  }

  return count;
}

int main()
{
  ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  vector<vector<int>> reports;
  char delimiter = ' ';

  string line;
  while (getline(inputFile, line))
  {
    stringstream iss(line);
    string s;
    vector<int> report;
    while (getline(iss, s, delimiter))
    {
      report.push_back(stoi(s));
    }
    reports.push_back(report);
  }
  inputFile.close();

  /**
   * Part 1
   */
  int result1 = countSafe(reports);
  cout << "Part 1 Result: " << result1 << endl;

  /**
   * Part 2
   */
  int result2 = countSafeDampener(reports);
  cout << "Part 2 Result: " << result2 << endl;

  return 0;
}