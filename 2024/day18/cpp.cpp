#include <bits/stdc++.h>
using namespace std;
vector<vector<char>> getGrid(int size)
{
  int padded = size + 1;
  vector<vector<char>> grid(padded, vector<char>(padded));
  for (int i = 0; i < padded; i++)
  {
    for (int j = 0; j < padded; j++)
    {
      grid[i][j] = '.';
    }
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
  // test values
  int size = 6;
  int nBytes = 12;

  // real values
  size = 70;
  nBytes = 1024;

  auto masterGrid = getGrid(size);

  char dn;
  int col, row;
  vector<pair<int, int>> fallenBytes;
  while (cin >> col >> dn >> row)
  {
    fallenBytes.push_back({col, row});
  }

  auto part1Grid = taintGrid(masterGrid, fallenBytes, 0, nBytes);
  auto part1 = getDistanceBfs(part1Grid, size, size);
  cout << "Part 1: " << part1 << endl;

  vector<vector<char>> lastGrid = masterGrid;
  for (int i = 0; i < fallenBytes.size(); i++)
  {
    auto part2Grid = taintGrid(lastGrid, fallenBytes, i, i + 1);
    auto part2 = getDistanceBfs(part2Grid, size, size);
    if (part2 == -1)
    {
      cout << "Part 2: " << fallenBytes[i].first << "," << fallenBytes[i].second << endl;
      return 0;
    }
    lastGrid = part2Grid;
  }
}
