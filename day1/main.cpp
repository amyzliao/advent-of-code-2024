#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/// @brief Calculate the distance between two lists
/// @param list1
/// @param list2
/// @return
int listDistance(vector<int> &list1, vector<int> &list2)
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

/// @brief Calculate the similarity between two lists.
/// Assumes both lists are sorted.
/// @param list1
/// @param list2
/// @return
int similarity(vector<int> &list1, vector<int> &list2)
{
  int sum = 0;
  int list2Index = 0;

  for (int i = 0; i < list1.size(); i++)
  {
    // while currentlist2 is smaller or equal to currentlist1
    while (list2[list2Index] <= list1[i] && list2Index < list2.size())
    {
      // if equal, add currentlist1 to sum
      if (list2[list2Index] == list1[i])
      {
        sum += list1[i];
      }
      // go next
      list2Index++;
    }
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

  /**
   * Part 1
   */
  int result = listDistance(list1, list2);
  cout << "Part 1 Result: " << result << endl;

  /**
   * Part 2
   */
  int score = similarity(list1, list2);
  cout << "Part 2 Result: " << score << endl;

  inputFile.close();
  return 0;
}