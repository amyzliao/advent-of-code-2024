#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

/// @brief count the number of safe reports
/// @param reports
/// @return
int countSafe(vector<vector<int>> const &reports)
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

vector<int> getIntervals(vector<int> &report)
{
  vector<int> intervals;
  for (int i = 0; i < report.size() - 1; i++)
  {
    intervals.push_back(report[i + 1] - report[i]);
  }
  return intervals;
}

bool isIntervalsSafe(vector<int> &intervals)
{
  bool increasing = intervals[0] > 0;
  for (int i = 0; i < intervals.size(); i++)
  {
    if (false
        // too small
        || abs(intervals[i]) < 1
        // too big
        || abs(intervals[i]) > 3
        // increasing, but encounter a decrease
        || (increasing && intervals[i] < 0)
        // decreasing, but encounter a increase
        || (!increasing && intervals[i] > 0))
    {
      return false;
    }
  }
  return true;
}

bool doesRemovalFix(vector<int> intervals, int leftidx, int rightidx)
{
  // combine intervals
  vector<int> dampenedIntervals(intervals);
  if (leftidx != rightidx)
  {
    dampenedIntervals[leftidx] += dampenedIntervals[rightidx];
  }
  // erase right
  dampenedIntervals.erase(dampenedIntervals.begin() + rightidx);
  // check if it's safe
  if (isIntervalsSafe(dampenedIntervals))
  {
    return true;
  }
  return false;
}

/// @brief count the number of safe reports, with problem dampener
/// @param reports
/// @return
int countSafeDampener(vector<vector<int>> &reports)
{
  int count = 0;

  // each report: check if it's safe
  for (auto &report : reports)
  {
    /**
     * get intervals between numbers
     */
    vector<int> intervals = getIntervals(report);

    /**
     * gather info
     */
    vector<int> increments;
    vector<int> decrements;
    unordered_set<int> rset;
    for (int i = 0; i < intervals.size(); i++)
    {
      if (intervals[i] > 0)
      {
        increments.push_back(i);
      }
      else if (intervals[i] < 0)
      {
        decrements.push_back(i);
      }

      if (abs(intervals[i]) > 3 || abs(intervals[i]) < 1)
      {
        rset.insert(i);
      }
    }

    /**
     * add lesser direction intervals to removals
     */
    if (increments.size() < decrements.size())
    {
      rset.insert(increments.begin(), increments.end());
    }
    else
    {
      rset.insert(decrements.begin(), decrements.end());
    }

    // turn removals into a vector
    vector<int> removals(rset.begin(), rset.end());

    /**
     * unsafe conditions:
     */
    if (false
        // more than 2 removals needed
        || removals.size() > 2
        // 2 removals that are not adjacent
        || (removals.size() == 2 && abs(removals[1] - removals[0]) > 1))
    {
      continue;
    }

    /**
     * safe conditions
     */
    if (removals.size() == 0)
    {
      count++;
      continue;
    }

    /**
     * try dampening
     */
    if (removals.size() == 2 && doesRemovalFix(intervals, removals[0], removals[1]))
    {
      count++;
    }
    else if (removals.size() == 1)
    {
      if (false
          // combine with prev
          || (removals[0] > 0 && doesRemovalFix(intervals, removals[0] - 1, removals[0]))
          // remove this interval if its first
          || (removals[0] == 0 && doesRemovalFix(intervals, removals[0], removals[0]))
          // combine with next
          || (removals[0] < intervals.size() - 1 && doesRemovalFix(intervals, removals[0], removals[0] + 1))
          // remove this interval if its last
          || (removals[0] == intervals.size() - 1 && doesRemovalFix(intervals, removals[0], removals[0])))
      {
        count++;
      }
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