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
  int *numbers = new int[5];
  // find height of each column
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
  cout << "Checking overlap between lock and key" << endl;
  cout << "Lock: ";
  for (int i = 0; i < 5; i++)
  {
    cout << lock[i] << " ";
  }
  cout << endl;
  cout << "Key: ";
  for (int i = 0; i < 5; i++)
  {
    cout << key[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < 5; i++)
  {
    if ((lock[i] + key[i]) > 5)
    {
      cout << "\t Overlap FOUND in column " << i << endl;
      return true;
    }
  }
  cout << "No overlap" << endl;
  return false;
}

int main()
{

  auto [locks, keys] = readInput();
  cout << "Locks: " << locks.size() << endl;
  int **lockNumberPtrs = new int *[locks.size()];
  for (int i = 0; i < locks.size(); i++)
  {
    auto &lock = locks[i];
    for (auto &line : lock)
    {
      cout << line << endl;
    }
    lockNumberPtrs[i] = objToNumbers(lock, "#");
    for (int j = 0; j < 5; j++)
    {
      cout << lockNumberPtrs[i][j] << " ";
    }
    cout << endl;
  }
  cout << "Keys: " << keys.size() << endl;
  int **keyNumberPtrs = new int *[keys.size()];
  for (int i = 0; i < keys.size(); i++)
  {
    auto &key = keys[i];
    for (auto &line : key)
    {
      cout << line << endl;
    }
    keyNumberPtrs[i] = objToNumbers(key, ".");
    for (int j = 0; j < 5; j++)
    {
      cout << keyNumberPtrs[i][j] << " ";
    }
    cout << endl;
  }

  int res = 0;
  for (int i = 0; i < locks.size(); i++)
  {
    for (int j = 0; j < keys.size(); j++)
    {
      if (lockAndKeyOverlap(lockNumberPtrs[i], keyNumberPtrs[j]))
      {
      }
      else
      {
        res++;
      }
    }
  }
  cout << "Part 1: " << res << endl;
  // 59615 too high
}
