#include <vector>
#include <queue>
#include <unordered_map>

/// @brief For a given update, returns the middle page
/// if it were in correct order.
/// @param rules
/// @param update
/// @return
int middleFixed(vector<vector<int>> const &rules, vector<int> const &update)
{
  // determine indegrees
  // indegrees : page in update -> indegree
  unordered_map<int, int> indegrees;
  for (int i = 0; i < update.size(); i++)
  {
    for (int j = 0; j < update.size(); j++)
    {
      indegrees[update[i]] = indegrees.find(update[i]) == indegrees.end() ? 0 : indegrees[update[i]];
      indegrees[update[i]] += rules[update[j]][update[i]];
    }
  }

  // make queue
  queue<int> q;
  for (const auto &pair : indegrees)
  {
    if (pair.second == 0)
    {
      q.push(pair.first);
    }
  }

  // process queue
  for (int i = 0; i < update.size() / 2; i++)
  {
    int p = q.front();
    q.pop();
    for (int c = 0; c < rules.size(); c++)
    {
      if (rules[p][c])
      {
        indegrees[c]--;
        if (indegrees[c] == 0)
        {
          q.push(c);
        }
      }
    }
  }

  return q.front();
}

/// @brief Sums the middle pages of all updates in wrong order,
/// if they were in the right order.
/// @param rules
/// @param updates
/// @param invalidUpdates
/// @return
int sumMiddleFixed(vector<vector<int>> const &rules,
                   vector<vector<int>> const &updates,
                   vector<int> const &invalidUpdates)
{
  int res = 0;

  for (int i : invalidUpdates)
  {
    res += middleFixed(rules, updates[i]);
  }

  return res;
}