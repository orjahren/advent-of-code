#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <deque>

#define pb push_back

int bfs(std::vector<std::string> &lines, int sr, int sc, int targetX, int targetY)
{
    const int height = lines[0].size();
    const int width = lines.size();

    char m[height][width];
    bool visited[height][width];

    for (int i = 0; i < width; i++)
    {
        std::string l = lines.at(i);
        for (int j = 0; j < height; j++)
        {
            m[j][i] = l[j];
            visited[j][i] = false;
        }
    }

    m[sr][sc] = 'a';
    m[targetX][targetY] = 'z';

    std::deque<int> rq;
    std::deque<int> cq;

    int nodesLeftInLayer = 1;
    int nodesInNextLayer = 0;

    int moveCount = 0;

    int dr[4] = {-1, +1, 0, 0};
    int dc[4] = {0, 0, +1, -1};

    rq.push_back(sr);
    cq.push_back(sc);
    visited[sr][sc] = true;

    while (rq.size() > 0)
    {
        int r = rq.front();
        rq.pop_front();
        int c = cq.front();
        cq.pop_front();
        if (r == targetX && c == targetY)
        {
            return moveCount;
        }
        for (int i = 0; i < 4; i++)
        {
            int rr = r + dr[i];
            int cc = c + dc[i];
            if ((m[rr][cc] - m[r][c] > 1) || rr < 0 || cc < 0 || rr >= height || cc >= width || visited[rr][cc])
            {
                continue;
            }
            rq.push_back(rr);
            cq.push_back(cc);
            visited[rr][cc] = true;
            nodesInNextLayer++;
        }
        nodesLeftInLayer--;
        if (nodesLeftInLayer == 0)
        {
            nodesLeftInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
            moveCount++;
        }
    }
    return -1;
}

int main()
{
    std::string filename("input");
    std::string line;
    std::ifstream file(filename);
    std::vector<std::string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    std::vector<int> a_x;
    std::vector<int> a_y;
    int part1StartX;
    int part1StartY;
    int targetX;
    int targetY;
    for (int i = 0; i < lines.size(); i++)
    {
        std::string l = lines.at(i);
        for (int j = 0; j < lines[0].size(); j++)
        {
            char c = l[j];
            if (c == 'E')
            {
                targetX = j;
                targetY = i;
            }
            else if (c == 'a')
            {
                a_x.pb(i);
                a_y.pb(j);
            }
            else if (c == 'S')
            {
                part1StartX = j;
                part1StartY = i;
            }
        }
    }
    std::cout << "Part 1: " << bfs(lines, part1StartX, part1StartY, targetX, targetY) << std::endl;
    int currPar2Res = 999;
    while (a_x.size() > 0)
    {
        int x = a_x.back();
        a_x.pop_back();

        int y = a_y.back();
        a_y.pop_back();

        int val = bfs(lines, y, x, targetX, targetY);
        if (val != -1 && val < currPar2Res)
        {
            currPar2Res = val;
        }
    }
    std::cout << "Part 2: " << currPar2Res << std::endl;
}