#include <vector>
#include <queue>

/// @brief Fixes and update
/// @param rules
/// @param update
/// @return
int middleFixed(vector<vector<int>> const &rules, vector<int> const &update)
{
  // print out update
  cout << "Update: ";
  for (int i : update)
  {
    cout << i << " ";
  }
  cout << endl;

  // determine indegrees
  vector<int> indegrees(rules.size(), 0);
  for (int i = 0; i < rules.size(); i++)
  {
    for (int j = i + 1; j < rules.size(); j++)
    {
      indegrees[j] += rules[i][j];
    }
  }

  // make queue
  queue<int> q;
  for (int i = 0; i < indegrees.size(); i++)
  {
    if (indegrees[i] == 0)
    {
      q.push(i);
    }
  }

  // process queue
  for (int i = 0; i < update.size() / 2 - 1; i++)
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

  // next item in q is middle page
  return q.front();
}

/// @brief If the update is invalid, returns the middle page
/// if it were in correct order.
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