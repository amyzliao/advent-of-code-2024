#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  ifstream inputFile("input.txt");

  if (!inputFile.is_open())
  {
    cerr << "Could not open the file!" << endl;
    return 1;
  }

  vector<int> list1;
  vector<int> list2;
  string delimiter = "   ";

  string line;
  while (getline(inputFile, line))
  {
    list1.push_back(stoi(line.substr(0, line.find(delimiter))));
    list2.push_back(stoi(line.substr(line.find(delimiter) + delimiter.length())));
  }

  // print out list 1
  cout << "List 1:\n";
  for (int i = 0; i < list1.size(); i++)
  {
    cout << list1[i] << "\n";
  }
  cout << endl;
  // print out list 2
  cout << "List 2:\n";
  for (int i = 0; i < list2.size(); i++)
  {
    cout << list2[i] << "\n";
  }
  cout << endl;

  inputFile.close();
  return 0;
}