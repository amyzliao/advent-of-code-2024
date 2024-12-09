#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <iostream>

using namespace std;

/*
INFO: yes i know my solution is overly complicated and probably less
efficient than optimal, but i was going for space efficiency here.
I wanted to avoid storing the entire grid in memory, instead only
storing the locations of walls.
not sure if it was worth it, but it was a fun exercise.
*/

struct pair_hash
{
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2> &p) const
  {
    auto h1 = hash<T1>{}(p.first);
    auto h2 = hash<T2>{}(p.second);
    return h1 ^ h2;
  }
};

class PatrolGuard
{
private:
  vector<vector<int>> rowToCol;
  vector<vector<int>> colToRow;

  pair<int, int> startPos;
  char startDir;
  pair<int, int> currentPos;
  char currentDir;

  unordered_set<pair<int, int>, pair_hash> visited;

  pair<int, int> findNextWall();
  bool isExit(pair<int, int> const &wall);
  bool walkToNextPos();
  bool causesLoop(pair<int, int> const &pos);

public:
  PatrolGuard(vector<vector<int>> const &rowToCol,
              vector<vector<int>> const &colToRow,
              char startDir,
              pair<int, int> startPos)
      : rowToCol(rowToCol), colToRow(colToRow),
        startDir(startDir), startPos(startPos),
        currentPos(startPos), currentDir(startDir) {}

  /// @brief Counts the number of visited positions
  /// @return
  int countVisitedPosns();

  /// @brief Counts the number of possible obstructions
  /// we can place to cause a loop.
  /// @return
  int countPossibleObstructions();
};