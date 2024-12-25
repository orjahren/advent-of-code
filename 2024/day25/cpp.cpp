#include <iostream>
#include <vector>
using namespace std;
pair<vector<vector<string>>, vector<vector<string>>> readInput()
{
  vector<vector<string>> locks;
  vector<vector<string>> keys;
  // read lines from stdin
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
      locks.back().push_back(line);
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

int main()
{

  auto [locks, keys] = readInput();
  cout << "Locks: " << locks.size() << endl;
  for (auto &lock : locks)
  {
    for (auto &line : lock)
    {
      cout << line << endl;
    }
  }
  cout << "Keys: " << keys.size() << endl;
  for (auto &key : keys)
  {
    for (auto &line : key)
    {
      cout << line << endl;
    }
  }
}
