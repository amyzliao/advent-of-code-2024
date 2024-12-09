#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

class PatrolGuard
{
private:
  vector<vector<int>> rowToCol;
  vector<vector<int>> colToRow;

  tuple<int, int> currentPos;
  char currentDir;

  unordered_set<tuple<int, int>> visited;

  bool findNextPos();
  void walkToPos();

public:
  PatrolGuard(vector<vector<int>> const &rowToCol,
              vector<vector<int>> const &colToRow,
              char startDir,
              tuple<int, int> startPos)
      : rowToCol(rowToCol), colToRow(colToRow), currentDir(startDir), currentPos(startPos)
  {
    visited.insert(startPos);
  }

  /// @brief Counts the number of visited positions
  /// @return
  int countVisitedPosns();
};