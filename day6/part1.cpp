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

bool PatrolGuard::causesLoop(pair<int, int> const &pos)
{
  /*
  keep walking to next pos
  if we reach wall we've already been to before
  from the same direction, we have a loop
  */
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
    if (causesLoop(pos))
    {
      count++;
    }
  }

  return count;
}