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

bool PatrolGuard::findNextPos()
{
}

void PatrolGuard::walkToPos()
{
}

int PatrolGuard::countVisitedPosns()
{

  /*
  1. find next wall in direction
  2. add all those to visited
  3. turn
  4. repeat

  if we have no wall in our direction
  then add to visited
  stop
  */
  while (true)
  {
    bool exit = findNextPos();
    walkToPos();
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
