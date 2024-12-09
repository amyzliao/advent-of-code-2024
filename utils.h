#include <string>
#include <vector>

using namespace std;

/// @brief split a string by a delimiter
/// @param s : input string
/// @param delimiter : string delimiter
/// @return
vector<string> split(string s, string delimiter)
{
  vector<string> tokens;
  size_t delimiterIndex = s.find(delimiter);
  while (delimiterIndex != string::npos)
  {
    string token = s.substr(0, delimiterIndex);
    tokens.push_back(token);
    s.erase(s.begin(), s.begin() + delimiterIndex + delimiter.size());
    delimiterIndex = s.find(delimiter);
  }
  tokens.push_back(s);
  return tokens;
}