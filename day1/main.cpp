#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int listDistance(vector<int> list1, vector<int> list2)
{
  /// sort the lists
  sort(list1.begin(), list1.end());
  sort(list2.begin(), list2.end());

  /// sum distances
  int sum = 0;
  for (int i = 0; i < list1.size(); i++)
  {
    sum += abs(list1[i] - list2[i]);
  }

  return sum;
}

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

  int result = listDistance(list1, list2);
  cout << "Result: " << result << endl;

  inputFile.close();
  return 0;
}