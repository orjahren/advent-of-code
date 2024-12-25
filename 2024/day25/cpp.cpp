#include <iostream>
#include <vector>
using namespace std;
pair<vector<vector<string>>, vector<vector<string>>> readInput()
{
  vector<vector<string>> locks;
  vector<vector<string>> keys;
  string line;
  while (getline(cin, line))
  {
    if (line[0] == '#')
    {
      locks.push_back(vector<string>());
      do
      {
        locks.back().push_back(line);
      } while (getline(cin, line) && !line.empty());
    }
    else
    {
      keys.push_back(vector<string>());
      do
      {
        keys.back().push_back(line);
      } while (getline(cin, line) && !line.empty());
    }
  }
  return {locks, keys};
}

int *objToNumbers(vector<string> obj, string blockChar)
{
  int height = obj.size();
  int width = obj[0].size();
  int *columnHeights = new int[width];
  for (int i = 0; i < width; i++)
  {
    if (blockChar == ".")
      columnHeights[i] = height;
    else
      columnHeights[i] = -1;
  }
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (obj[i][j] == blockChar[0] && blockChar == "#")
      {
        columnHeights[j]++;
      }
      else if (obj[i][j] == blockChar[0] && blockChar == ".")
      {
        columnHeights[j] = height - i - 2;
      }
    }
  }

  return columnHeights;
}

bool lockAndKeyOverlap(int *lock, int *key)
{
  for (int i = 0; i < 5; i++)
  {
    if ((lock[i] + key[i]) > 5)
    {
      return true;
    }
  }
  return false;
}

int main()
{
  auto [locks, keys] = readInput();

  int **lockNumberPtrs = new int *[locks.size()];
  for (int i = 0; i < locks.size(); i++)
    lockNumberPtrs[i] = objToNumbers(locks[i], "#");

  int **keyNumberPtrs = new int *[keys.size()];
  for (int i = 0; i < keys.size(); i++)
    keyNumberPtrs[i] = objToNumbers(keys[i], ".");

  int res = 0;
  for (int i = 0; i < locks.size(); i++)
    for (int j = 0; j < keys.size(); j++)
      if (!lockAndKeyOverlap(lockNumberPtrs[i], keyNumberPtrs[j]))
        res++;
  cout << "Part 1: " << res << endl;
}
