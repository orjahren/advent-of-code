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

int main()
{

  auto masterGrid = getGridFromStdin();
  int startRow, startCol, targetRow, targetCol;

  cout << "Master Grid" << endl;
  cout << "-----------" << endl;
  cout << masterGrid.size() << endl;
  cout << masterGrid[0].size() << endl;
  cout << "-----------" << endl;
  for (int i = 0; i < masterGrid.size(); i++)
  {
    for (int j = 0; j < masterGrid[0].size(); j++)
    {
      if (masterGrid[i][j] == 'S')
      {
        startRow = i;
        startCol = j;
      }
      else if (masterGrid[i][j] == 'E')
      {
        targetRow = i;
        targetCol = j;
      }

      cout << masterGrid[i][j];
    }
    cout << endl;
  }

  cout << "Start Row: " << startRow << " Start Col: " << startCol << endl;
  cout << "Target Row: " << targetRow << " Target Col: " << targetCol << endl;

  vector<vector<int>> distance(masterGrid.size(), vector<int>(masterGrid[0].size(), -1));
  vector<vector<int>> visited(masterGrid.size(), vector<int>(masterGrid[0].size(), 0));
  queue<pair<int, int>> q;
  q.push({startRow, startCol});
  visited[startRow][startCol] = 1;
  distance[startRow][startCol] = 0;
  while (!q.empty())
  {
    auto [row, col] = q.front();
    q.pop();
    if (row == targetRow && col == targetCol)
    {
      break;
    }
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (auto [dx, dy] : directions)
    {
      int newRow = row + dx;
      int newCol = col + dy;
      if (newRow < 0 || newRow >= masterGrid.size() || newCol < 0 || newCol >= masterGrid[0].size())
      {
        continue;
      }
      if (visited[newRow][newCol] == 0 && masterGrid[newRow][newCol] != '#')
      {
        visited[newRow][newCol] = 1;
        distance[newRow][newCol] = distance[row][col] + 1;
        q.push({newRow, newCol});
      }
    }
  }

  cout << "Saving" << endl;

  int part1 = 0;
  for (int row = 0; row < distance.size(); row++)
  {
    for (int col = 0; col < distance[0].size(); col++)
    {
      cout << distance[row][col] << " ";
      if (masterGrid[row][col] == '#')
      {
        continue;
      }

      for (auto [nr, nc] : vector<pair<int, int>>{{row + 2, col}, {row + 1, col + 1}, {row, col + 2}, {row - 1, col + 1}})
      {
        if (nr < 0 || nr >= masterGrid.size() || nc < 0 || nc >= masterGrid[0].size())
        {
          continue;
        }
        if (masterGrid[nr][nc] == '#')
        {
          continue;
        }
        if (abs(distance[row][col] - distance[nr][nc]) >= 102)
        {
          part1++;
        }
      }
    }
    cout << endl;
  }
  cout << "Part 1: " << part1 << endl;
  return 0;
}
