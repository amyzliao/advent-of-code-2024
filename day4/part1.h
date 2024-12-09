#include <string>
#include <vector>
#include <ranges>
#include <sstream>

using namespace std;

vector<vector<int>> directions = {
    {-1, 0}, // up
    {1, 0},  // down
    {0, -1}, // left
    {0, 1}   // right
};

vector<char> letters = {'X', 'M', 'A', 'S'};

int search(vector<vector<char>> board, int r, int c)
{
  int count = 0;
  for (const auto d : directions)
  {
    bool found = true;
    for (int l = 1; l <= 3; l++)
    {
      int nextR = r + d[0] * l;
      int nextC = c + d[1] * l;
      if (nextR < 0 || nextR >= board.size()           // row out of bounds
          || nextC < 0 || nextC >= board[nextR].size() // col out of bounds
          || board[nextR][nextC] != letters[l]         // wrong char
      )
      {
        found = false;
        break;
      }
    }
    if (found)
    {
      count++;
    }
  }
  return count;
}

int countXMAS(vector<vector<char>> board)
{
  int count = 0;

  // start the search from every X
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == 'X')
      {
        count += search(board, i, j);
      }
    }
  }

  return count;
}