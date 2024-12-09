#include <string>
#include <vector>
#include <sstream>
#include "../utils.h"

using namespace std;

int validMults(string s)
{
  int result = 0;

  size_t start = 0;
  size_t index = s.find("mul(", start);
  while (index != string::npos)
  {
    string rest = s.substr(index + 4);
    stringstream ss(rest);

    // what we want to read from stream
    int x;
    char comma;
    int y;
    char close;

    // try to read from stream
    if (true                           //
        && ss >> x && x <= 999         //
        && ss >> comma && comma == ',' //
        && ss >> y && y <= 999         //
        && ss >> close && close == ')' //
    )
    {
      result += x * y;
    }

    // prep for next loop
    start = index + 1;
    index = s.find("mul(", start);
  }

  return result;
}

int main()
{
  ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  /**
   * Part 1
   */

  int result = 0;
  string line;
  while (getline(inputFile, line))
  {
    result += validMults(line);
  }
  inputFile.close();

  cout << "Part 1 Result: " << result << endl;

  return 0;
}
