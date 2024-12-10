#include "part1.h"

unordered_map<char, char> Right = {
    {'<', '^'},
    {'^', '>'},
    {'>', 'v'},
    {'v', '<'}};

unordered_map<char, pair<int, int>> Direction = {
    {'<', pair(0, -1)},
    {'^', pair(-1, 0)},
    {'>', pair(0, 1)},
    {'v', pair(1, 0)}};

pair<int, int> PatrolGuard::findNextWall()
{
  int startR = currentPos.first;
  int startC = currentPos.second;

  pair<int, int> wall;
  int wallC, wallR;
  switch (currentDir)
  {
  case '<':
    wallC = -1;
    for (int c : rowToCol[startR])
    {
      if (c >= startC)
      {
        break;
      }
      wallC = c;
    }
    wall = {startR, wallC};
    break;
  case '>':
    wallC = colToRow.size();
    for (int c : rowToCol[startR])
    {
      if (c > startC)
      {
        wallC = c;
        break;
      }
    }
    wall = {startR, wallC};
    break;
  case '^':
    wallR = -1;
    for (int r : colToRow[startC])
    {
      if (r >= startR)
      {
        break;
      }
      wallR = r;
    }
    wall = {wallR, startC};
    break;
  case 'v':
    wallR = rowToCol.size();
    for (int r : colToRow[startC])
    {
      if (r > startR)
      {
        wallR = r;
        break;
      }
    }
    wall = {wallR, startC};
    break;
  }

  return wall;
}

bool PatrolGuard::isExit(pair<int, int> const &wall)
{
  return (wall.first < 0 || wall.first >= rowToCol.size()      // row out of bounds
          || wall.second < 0 || wall.second >= colToRow.size() // col out of bounds
  );
}

bool PatrolGuard::walkToNextPos()
{
  // find next wall
  pair<int, int> nextWall = findNextWall();

  // walk to next wall, marking visited along the way
  pair<int, int> dir = Direction[currentDir];
  pair<int, int> nextPos = {currentPos.first + dir.first, currentPos.second + dir.second};
  while (nextPos != nextWall)
  {
    currentPos = nextPos;
    visited.insert(currentPos);
    nextPos = {currentPos.first + dir.first, currentPos.second + dir.second};
  }

  // we never found a wall
  if (isExit(nextWall))
  {
    return true;
  }

  return false;
}

int PatrolGuard::countVisitedPosns()
{
  visited.insert(startPos);

  while (true)
  {
    bool exit = walkToNextPos();
    // walk out of area
    if (exit)
    {
      break;
    }
    // turn and repeat
    currentDir = Right[currentDir];
  }

  return visited.size();
}

void PatrolGuard::addWall(pair<int, int> const &pos)
{
  int r = pos.first;
  int c = pos.second;
  rowToCol[r].push_back(c);
  colToRow[c].push_back(r);
  sort(rowToCol[r].begin(), rowToCol[r].end());
  sort(colToRow[c].begin(), colToRow[c].end());
}

void PatrolGuard::removeWall(pair<int, int> const &pos)
{
  int r = pos.first;
  int c = pos.second;
  rowToCol[r].erase(find(rowToCol[r].begin(), rowToCol[r].end(), c));
  colToRow[c].erase(find(colToRow[c].begin(), colToRow[c].end(), r));
}

bool PatrolGuard::hasLoop()
{
  // reset
  currentPos = startPos;
  currentDir = startDir;

  // record walls + direction visited
  unordered_set<tuple<int, int, char>, tuple_hash> visitedWalls;

  while (true)
  {
    pair<int, int> nextWall = findNextWall();

    // we exit
    if (isExit(nextWall))
    {
      return false;
    }

    // we've seen this wall before, with the same direction
    if (visitedWalls.find({nextWall.first, nextWall.second, currentDir}) != visitedWalls.end())
    {
      return true;
    }

    // track this wall + dir
    visitedWalls.insert({nextWall.first, nextWall.second, currentDir});

    // turn and repeat
    pair<int, int> dir = Direction[currentDir];
    currentPos.first = nextWall.first - dir.first;
    currentPos.second = nextWall.second - dir.second;
    currentDir = Right[currentDir];
  }

  return false;
}

int PatrolGuard::countPossibleObstructions()
{
  int count = 0;

  // cannot place obstruction at start
  visited.erase(startPos);

  // iterate through visited
  for (pair<int, int> pos : visited)
  {
    // add new wall
    addWall(pos);
    // check if theres now a loop
    if (hasLoop())
    {
      count++;
    }
    // remove our added wall
    removeWall(pos);
  }

  return count;
}