#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <utility>
#include <iostream>

using namespace std;

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

struct tuple_hash
{
  template <class T1, class T2, class T3>
  size_t operator()(const tuple<T1, T2, T3> &t) const
  {
    auto h1 = hash<T1>{}(std::get<0>(t));
    auto h2 = hash<T2>{}(std::get<1>(t));
    auto h3 = hash<T3>{}(std::get<2>(t));
    return h1 ^ h2 ^ h3;
  }
};

class PatrolGuard
{
private:
  /// @brief Store the locations of all the walls in our grid.
  /// rowToCol[r]: row index r -> list of col indices where (r,c) contains a wall
  vector<vector<int>> rowToCol;
  /// colToRow[c]: col index c -> list of row indices where (r,c) contains a wall
  vector<vector<int>> colToRow;

  /// @brief Our starting state as determined by the input.
  pair<int, int> startPos;
  char startDir;

  /// @brief For tracking internal state as we traverse the grid.
  pair<int, int> currentPos;
  char currentDir;

  /// @brief Set of all positions visited as we traverse the grid.
  unordered_set<pair<int, int>, pair_hash> visited;

  /// @brief Given the current position and direction,
  /// find the position of the next wall we would hit.
  /// @return
  pair<int, int> findNextWall();

  /// @brief If findNextWall does not find a wall,
  /// it will return the position right outside where we
  /// exit the grid. this checks whether the position returned
  /// by findNextWall is inside the bounds of the grid or not.
  /// This would probably be more efficient if findNextWall
  /// simply returned a bool as well indicating if we've exited.
  /// @param wall : returned by findNextWall
  /// @return
  bool isExit(pair<int, int> const &wall);

  /// @brief Finds the next wall and walks to it.
  /// All positions visited along the way are added to visited,
  /// and our current position is updated.
  /// @return
  bool walkToNextPos();

  /// @brief Adds another wall to our grid.
  /// @param pos
  void addWall(pair<int, int> const &pos);

  /// @brief Removes a wall from our grid.
  /// @param pos
  void removeWall(pair<int, int> const &pos);

  /// @brief Checks if our grid contains a loop.
  /// @return
  bool hasLoop();

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