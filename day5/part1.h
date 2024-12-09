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

/// @brief Sums the middle pages of all updates that are in valid order.
/// Also finds all invalid updates for part 2.
/// @param rules
/// @param updates
/// @param invalidUpdates
/// @return
int sumMiddlePages(vector<vector<int>> const &rules,
                   vector<vector<int>> const &updates,
                   vector<int> &invalidUpdates)
{
  int res = 0;

  for (int i = 0; i < updates.size(); i++)
  {
    int middle = middlePageIfValid(rules, updates[i]);
    if (!middle)
    {
      invalidUpdates.push_back(i);
    }
    res += middle;
  }

  return res;
}