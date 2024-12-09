#include <string>
#include <vector>
#include "../utils.h"

using namespace std;

int main()
{
  string test = "hi my name is amy";
  string delimiter = " ";
  vector<string> tokens = split(test, delimiter);

  // print out tokens
  for (int i = 0; i < tokens.size(); i++)
  {
    cout << tokens[i] << ",";
  }
  cout << endl;
}
