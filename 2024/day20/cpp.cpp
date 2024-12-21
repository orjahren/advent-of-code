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

  int row = startRow;
  int col = startCol;

  vector<vector<int>> distance(masterGrid.size(), vector<int>(masterGrid[0].size(), -1));
  distance[row][col] = 0;
  while (masterGrid[row][col] != 'E')
  {
    for (auto [nr, nc] : vector<pair<int, int>>{{row + 1, col}, {row - 1, col}, {row, col + 1}, {row, col - 1}})
    {
      if (nr < 0 || nr >= masterGrid.size() || nc < 0 || nc >= masterGrid[row].size())
      {
        continue;
      }
      if (masterGrid[nr][nc] == '#')
      {
        continue;
      }
      if (distance[nr][nc] != -1)
      {
        continue;
      }
      distance[nr][nc] = distance[row][col] + 1;
      row = nr;
      col = nc;
    }
  }

  cout << "Saving" << endl;

  int part1 = 0;
  int part2 = 0;
  for (row = 0; row < distance.size(); row++)
  {
    for (col = 0; col < distance[row].size(); col++)
    {
      if (masterGrid[row][col] == '#')
      {
        continue;
      }
      // cout << distance[row][col] << " ";
      // cout << endl;
      // Part 1
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
      // Part 2
      for (int rad = 2; rad <= 20; rad++)
      {
        for (int rowDist = 0; rowDist <= rad; rowDist++)
        {
          int colDist = rad - rowDist;

          set<pair<int, int>> seen;
          for (auto [nr, nc] : vector<pair<int, int>>{{row + rowDist, col + colDist}, {row + rowDist, col - colDist}, {row - rowDist, col + colDist}, {row - rowDist, col - colDist}})
          {
            if (nr < 0 || nr >= masterGrid.size() || nc < 0 || nc >= masterGrid[row].size())
            {
              continue;
            }
            if (masterGrid[nr][nc] == '#')
            {
              continue;
            }
            if (seen.count({nr, nc}))
            {
              continue;
            }
            seen.insert({nr, nc});
            if ((distance[row][col] - distance[nr][nc]) >= (100 + rad))
            {
              part2++;
              // cout << "nr: " << nr << ", nc: " << nc << ", distance[row][col]: " << distance[row][col] << ", distance[nr][nc]: " << distance[nr][nc] << ", part2: " << part2 << endl;
            }
          }
        }
      }
    }
  }
  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2 << endl;
  // 1094950 too high
  // 1146285 too high
  // 842467 too low
  // 1039369 nondescript feil.
  return 0;
}
