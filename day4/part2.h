#include <string>
#include <vector>
#include <ranges>
#include <sstream>

using namespace std;

vector<vector<int>> pairs = {
    {1, 1, -1, -1}, // downright + upleft
    {1, -1, -1, 1}  // downleft + upright
};

bool isMASCenter(vector<vector<char>> board, int r, int c)
{
  bool isCenter = true;
  size_t boardRows = board.size();
  size_t boardCols = board[0].size();
  for (const auto p : pairs)
  {
    int firstR = r + p[0];
    int firstC = c + p[1];
    int secondR = r + p[2];
    int secondC = c + p[3];
    if (
        // first out of bounds
        firstR < 0 || firstR >= boardRows || firstC < 0 || firstC >= boardCols
        // second out of bounds
        || secondR < 0 || secondR >= boardRows || secondC < 0 || secondC >= boardCols)
    {
      isCenter = false;
      break;
    }
    char first = board[firstR][firstC];
    char second = board[secondR][secondC];
    if ((first != 'S' && first != 'M')      // first is not S or M
        || (second != 'S' && second != 'M') // second is not S or M
        || (first == second)                // first and second are the same
    )
    {
      isCenter = false;
      break;
    }
  }
  return isCenter;
}

int countX_MAS(vector<vector<char>> board)
{
  int count = 0;

  // check if every A is the center of X-MAS
  for (int i = 0; i < board.size(); i++)
  {
    for (int j = 0; j < board[i].size(); j++)
    {
      if (board[i][j] == 'A')
      {
        count += isMASCenter(board, i, j);
      }
    }
  }

  return count;
}