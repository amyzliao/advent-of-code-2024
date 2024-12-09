#include <string>
#include <iostream>
#include <tuple>
#include <sstream>

using namespace std;

/// @brief Given a string, determines whether do() or don't()
///        is called last. True = do(), False = don't().
/// @param s
/// @param enabled: returned if neither is called
/// @return
bool getNextEnabledState(string s, bool enabled)
{
  reverse(s.begin(), s.end());
  size_t lastEnabled = s.find(")(od");
  size_t lastDisabled = s.find(")(t'nod");
  if (lastEnabled != string::npos && lastDisabled != string::npos)
  {
    return lastEnabled < lastDisabled;
  }
  else if (lastEnabled != string::npos)
  {
    enabled = true;
  }
  else if (lastDisabled != string::npos)
  {
    enabled = false;
  }
  return enabled;
}

/// @brief Only sum results of enabled mults
/// @param s
/// @param enabled
/// @return
tuple<int, bool> enabledMults(string const &s, bool enabled)
{
  int result = 0;

  size_t start = 0;

  // find first occurrence of stuff
  size_t nextMul = s.find("mul(", start);

  // set initial state
  enabled = getNextEnabledState(s.substr(start, nextMul), enabled);

  while (nextMul != string::npos)
  {
    if (enabled)
    {
      // setup string stream
      string rest = s.substr(nextMul + 4);
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
    }

    // prep for next loop
    start = nextMul + 1;
    nextMul = s.find("mul(", start);
    enabled = getNextEnabledState(s.substr(start, nextMul - start), enabled);
  }

  return tuple<int, bool>{result, enabled};
}
