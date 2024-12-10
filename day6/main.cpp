#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "part1.h"

using namespace std;

/*
READ ME:
my solution might appear to be overly complicated (why is there a class
and why are there so many functions).

i know i could have simplified a lot of the coding implementation by just
storing the entire input grid in a 2D array. however:

  1. that would take up a lot of memory, which might actually be slow
  (but i dont actually know if the grid is really that big where this
  would be a problem).

  2. looking at the input, there are a LOT more empty spaces than obstructions
  (which i will call walls for short). because of this, i had a hunch
  that iterating through walls only would be faster than iterating
  through all positions on the grid. even if, for every movement,
  i have to iterate through ALL the walls instead of a fraction of
  the grid positions. i dont actually know if this is true because i dont
  want to do the math.

thus, i opted to only store the locations of walls (and the start ofc).
i know that i will frequently need to find a wall in a given row
(when the guard travels up/down), or a given col (traveling left/right).
so, i create bidirectional mappings of row to col indices for each row (rowToCol)
and col to row indices for each col (colToRow).

but if i'm not storing the entire grid, how do i keep track of the number of
unique positions the guard has visited? well if i know my current location,
and next location i am stopping/turning at, and the direction is a straight line,
i can easily calculate all the positions i have visited along the way. i simply
add all of these to a set so i can count the number of unique positions.

but then you might ask, what was the point of finding the next wall faster
by iterating through walls instead of positions on the grid, if i am just
going to iterate through positions on the grid anyways to add them to my
visited set? isn't this less efficient?
well, you would be right, but space complexity, and to my surprise part 2
really does take advantage of my wall-only storage since part 2 doesn't
require tracking visited positions. i can detect loops by only tracking
what walls walls i've hit before.

a fantastic optimization i only thought of after having finished the problem
is using binary search when finding the next wall hit. rowToCol stores
a sorted list of cols per row, and same for colToRow, so binary search
would have just been a better option.
std::set implements BSTs and actually provides lower_bound and upper_bound
functions that would have been PERFECT for finding the next wall.
it also simplifies insertion and deletion for part 2.

i wont bother implementing this since my solution is already fast
(around 330ms total for both parts, including parsing input).
*/

int main()
{
  auto start = chrono::high_resolution_clock::now();

  ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  /**
   * read in input file
   */
  // for each row, a list of indices where walls occur
  vector<vector<int>> rowToCol;
  // for each col, a list of indices where walls occur
  vector<vector<int>> colToRow;

  // start
  char startDir;
  pair<int, int> startPos;

  string line;
  int r = 0;
  while (getline(inputFile, line))
  {
    // init row
    rowToCol.push_back(vector<int>());
    // look through all cols for walls
    for (int c = 0; c < line.size(); c++)
    {
      // first row, init vec for each col
      if (r == 0)
      {
        colToRow.push_back(vector<int>());
      }
      // add walls
      if (line[c] == '#')
      {
        rowToCol[r].push_back(c);
        colToRow[c].push_back(r);
      }
      // starting pos
      else if (line[c] == '<' || line[c] == '>' || line[c] == '^' || line[c] == 'v')
      {
        startDir = line[c];
        startPos = {r, c};
      }
    }
    r++;
  }
  inputFile.close();

  /**
   * Part 1
   */
  PatrolGuard pg = PatrolGuard(rowToCol, colToRow, startDir, startPos);
  int result1 = pg.countVisitedPosns();
  cout << "Part 1 Result: " << result1 << endl;

  /**
   * Part 2
   */
  int result2 = pg.countPossibleObstructions();
  cout << "Part 2 Result: " << result2 << endl;

  /**
   * Time results
   */
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << "Time: " << duration.count() << "ms" << endl;

  return 0;
}
