#include <vector>

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
      if (rules[s][page])
      {
        return 0;
      }
    }
  }
  return update[update.size() / 2];
}

int sumMiddlePages(vector<vector<int>> const &rules,
                   vector<vector<int>> const &updates)
{
  /**
   * 1|2
   * 3|1
   * 3|4
   * 5|6
   *
   * 4 5 1 2
   * g g g g
   *
   * 1 2 3
   * g g b
   *
   * seen: 6 3
   * 6 3 1 5
   * g g g b
   *
   * 1|2
   * 2|3
   * // implies 1|3
   *
   * 3 1
   * seen: 3 1
   * g g
   */

  int res = 0;

  for (const auto &update : updates)
  {
    res += middlePageIfValid(rules, update);
  }

  return res;
}