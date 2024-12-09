#include <string>
#include <iostream>
#include <sstream>

using namespace std;

int allMults(string const &s)
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
