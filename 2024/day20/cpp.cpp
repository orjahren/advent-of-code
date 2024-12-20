#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <map>
#include <set>
using namespace std;
vector<vector<char>> getGridFromStdin()
{
  vector<vector<char>> grid;
  string line;
  while (getline(cin, line))
  {
    if (line.empty())
    {
      break;
    }
    grid.push_back(vector<char>(line.begin(), line.end()));
  }
  return grid;
}

struct triplet
{
  int x, y, distance;
};
int getDistanceBfs(vector<vector<char>> &grid, int trow, int tcol)
{
  queue<triplet> q;
  q.push({0, 0, 0});
  auto visited = vector<vector<bool>>(grid.size(), vector<bool>(grid.size(), false));
  while (!q.empty())
  {
    auto [col, row, distance] = q.front();
    q.pop();
    if (col < 0 || col >= grid.size() || row < 0 || row >= grid.size() || grid[col][row] == '#' || visited[col][row])
    {
      continue;
    }
    if (col == trow && row == tcol)
    {
      return distance;
    }
    visited[col][row] = true;
    q.push({col + 1, row, distance + 1});
    q.push({col - 1, row, distance + 1});
    q.push({col, row + 1, distance + 1});
    q.push({col, row - 1, distance + 1});
  }
  return -1;
}

vector<vector<char>> taintGrid(vector<vector<char>> &grid, vector<pair<int, int>> &fallenBytes, int fallFrom, int fallTo)
{
  for (int i = fallFrom; i < fallTo; i++)
  {
    auto [col, row] = fallenBytes[i];
    grid[col][row] = '#';
  }

  return grid;
}

int main()
{

  auto masterGrid = getGridFromStdin();

  cout << "Master Grid" << endl;
  // print size
  cout << "-----------" << endl;
  cout << masterGrid.size() << endl;
  cout << masterGrid[0].size() << endl;
  cout << "-----------" << endl;
  for (auto row : masterGrid)
  {
    for (auto cell : row)
    {
      cout << cell;
    }
    cout << endl;
  }
}
