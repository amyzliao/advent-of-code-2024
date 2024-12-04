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
  int result = countSafe(reports);
  cout << "Part 1 Result: " << result << endl;

  /**
   * Part 2
   */
  // int score = similarity(list1, list2);
  // cout << "Part 2 Result: " << score << endl;

  return 0;
}