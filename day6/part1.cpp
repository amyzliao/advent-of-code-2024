#include "part1.h"

unordered_map<char, char> Right = {
    {'<', '^'},
    {'^', '>'},
    {'>', 'v'},
    {'v', '<'}};

unordered_map<char, tuple<int, int>> Direction = {
    {'<', make_tuple(0, -1)},
    {'^', make_tuple(-1, 0)},
    {'>', make_tuple(0, 1)},
    {'v', make_tuple(1, 0)}};

bool PatrolGuard::walkToNextPos()
{
  int startR = currentPos.first;
  int startC = currentPos.second;

  int wall = -1;
  pair<int, int> newPos;

  switch (currentDir)
  {
  case '<':
    // find wall to our left
    for (int c : rowToCol[startR])
    {
      if (c >= startC)
      {
        break;
      }
      wall = c;
    }
    // never found wall
    if (wall == -1)
    {
      for (int i = startC - 1; i >= 0; i--)
      {
        visited.insert({startR, i});
      }
    }
    // walk there
    for (int i = startC - 1; i > wall; i--)
    {
      visited.insert({startR, i});
    }
    // where we end up
    newPos = {startR, wall + 1};
    break;

  case '>':
    // find wall to our right
    for (int c : rowToCol[startR])
    {
      if (c > startC)
      {
        wall = c;
        break;
      }
    }
    // never found wall
    if (wall == -1)
    {
      for (int i = startC + 1; i < colToRow.size(); i++)
      {
        visited.insert({startR, i});
      }
    }
    // walk there
    for (int i = startC + 1; i < wall; i++)
    {
      visited.insert({startR, i});
    }
    // where we end up
    newPos = {startR, wall - 1};
    break;

  case '^':
    // find wall above us
    for (int r : colToRow[startC])
    {
      if (r >= startR)
      {
        break;
      }
      wall = r;
    }
    // never found wall
    if (wall == -1)
    {
      for (int i = startR - 1; i >= 0; i--)
      {
        visited.insert({i, startC});
      }
    }
    // walk there
    for (int i = startR - 1; i > wall; i--)
    {
      visited.insert({i, startC});
    }
    // end up
    newPos = {wall + 1, startC};
    break;

  case 'v':
    // find wall below us
    for (int r : colToRow[startC])
    {
      if (r > startR)
      {
        wall = r;
        break;
      }
    }
    // never found wall
    if (wall == -1)
    {
      for (int i = startR + 1; i < rowToCol.size(); i++)
      {
        visited.insert({i, startC});
      }
    }
    // walk there
    for (int i = startR + 1; i < wall; i++)
    {
      visited.insert({i, startC});
    }
    // end up
    newPos = {wall - 1, startC};
    break;
  }

  // we never found a wall
  if (wall == -1)
  {
    return true;
  }
  // we did found a wall
  currentPos = newPos;
  return false;
}

int PatrolGuard::countVisitedPosns()
{
  while (true)
  {
    // cout << "Current Pos: " << currentPos.first << ", " << currentPos.second << endl;
    // cout << "Current Dir: " << currentDir << endl;

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
