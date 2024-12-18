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

void printGrid(vector<vector<char>> &grid)
{
  for (int i = 0; i < grid.size(); i++)
  {
    for (int j = 0; j < grid[i].size(); j++)
    {
      cout << grid[i][j] << "";
    }
    cout << endl;
  }
}

struct triplet
{
  int x, y, distance;
};
int getDistanceBfs(vector<vector<char>> &grid, int tx, int ty)
{
  queue<triplet> q;
  q.push({0, 0, 0});
  auto visited = vector<vector<bool>>(grid.size(), vector<bool>(grid.size(), false));
  while (!q.empty())
  {
    auto [x, y, distance] = q.front();
    q.pop();
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid.size())
    {
      continue;
    }
    if (grid[y][x] == '#' || visited[y][x])
    {
      continue;
    }
    visited[y][x] = true;
    if (x == tx && y == ty)
    {
      return distance;
    }
    q.push({x + 1, y, distance + 1});
    q.push({x - 1, y, distance + 1});
    q.push({x, y + 1, distance + 1});
    q.push({x, y - 1, distance + 1});
  }
  return -1;
}

int main()
{
  int size = 6;
  int nBytes = 12;

  // real values
  size = 70;
  nBytes = 1024;

  auto grid = getGrid(size);
  printGrid(grid);

  char dn;
  int x, y;
  int fallen = 0;

  while (cin >> x >> dn >> y)
  {
    if (fallen++ >= nBytes)
    {
      cout << "All bytes have fallen" << endl;
      break;
    }
    cout << x << ", " << y << endl;
    grid[y][x] = '#';
  }

  printGrid(grid);
  auto bfs = getDistanceBfs(grid, size, size);
  cout << "Distance: " << bfs << endl;
}
