#include <vector>
#include <iostream>

using namespace std;

/// @brief If the update pages are in valid order, returns the value of the middle
/// page. Otherwise, returns 0.
/// @param rules
/// @param update
/// @return
int middlePageIfValid(vector<vector<int>> const &rules, vector<int> const &update)
{
  vector<int> seen;
  for (const auto &page : update)
  {
    for (const int &s : seen)
    {
      // breaks dependency
      if (rules[page][s])
      {
        return 0;
      }
    }
    seen.push_back(page);
  }
  return update[update.size() / 2];
}

int sumMiddlePages(vector<vector<int>> const &rules,
                   vector<vector<int>> const &updates)
{
  int res = 0;

  for (const auto &update : updates)
  {
    res += middlePageIfValid(rules, update);
  }

  return res;
}