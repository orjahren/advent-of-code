#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <deque>

using ll = long long;

int bfs(std::string &filename)
{
    std::string line;
    std::ifstream file(filename);
    std::vector<std::string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    const int height = lines[0].size();
    const int width = lines.size();
    char grid[width][height];
    std::cout << "Grid size: " << width << "x" << height << std::endl;

    /*
    https://towardsdatascience.com/graph-theory-bfs-shortest-path-problem-on-a-grid-1437d5cb4023
    */
    const int R = height;
    const int C = width;

    char m[R][C];
    bool visited[R][C];
    int goalI = -1;
    int goalJ = -1;
    int startI = -1;
    int startJ = -1;

    int sr = 0;
    int sc = 0;
    /*
    for (int i = 0; i < width; i++)
    {
        std::string l = lines.at(i);
        for (int j = 0; j < height; j++)
    */
    for (int i = 0; i < width; i++)
    {
        std::string l = lines.at(i);
        for (int j = 0; j < height; j++)
        {

            char c = l[j];
            // m[i][j] = c;
            m[j][i] = c;
            visited[j][i] = false;

            if (c == 'E')
            {
                m[j][i] = 'z';
                goalI = j;
                goalJ = i;
            }
            else if (c == 'S')
            {
                m[j][i] = 'a';
                startI = j;
                startJ = i;
                sr = i;
                sc = j;
                sr = j;
                sc = i;
            }
            std::cout << m[j][i];
        }
        std::cout << std::endl;
    }

    std::deque<int> rq;
    std::deque<int> cq;

    int nodesLeftInLayer = 1;
    int nodesInNextLayer = 0;

    bool reachEnd = false;
    int moveCount = 0;

    int dr[4] = {-1, +1, 0, 0};
    int dc[4] = {0, 0, +1, -1};

    rq.emplace_back(sr);
    cq.emplace_back(sc);
    visited[sr][sc] = true;

    while (rq.size() > 0)
    {
        int r = rq.front();
        rq.pop_front();
        int c = cq.front();
        cq.pop_front();

        std::cout << "Sjekker ut noden " << m[r][c] << ", " << nodesLeftInLayer << std::endl;
        // moveCount++;
        //     std::cout << moveCount << std::endl;

        if (r == goalI && c == goalJ)
        {
            std::cout << "ER FERDIG" << std::endl;
            reachEnd = true;
            break;
        }
        // exploreNeighbors(r, c);
        for (int i = 0; i < 4; i++)
        {
            int rr = r + dr[i];
            int cc = c + dc[i];

            /*
                if (m[rr][cc] == 'E')
                {

                    std::cout << "Terminerer tidlig" << std::endl;
                    res = moveCount + 1;
                    return res;
                    break;
                }
            */

            if (rr < 0 || cc < 0)
            {
                continue;
            }
            if (rr >= R || cc >= C)
            {
                continue;
            }

            if (visited[rr][cc] == true)
            {
                continue;
            }
            std::cout << "\t Sammenligner med " << m[rr][cc] << "( " << rr << ", " << cc << ") " << int(m[rr][cc]) << std::endl;
            std::cout << "\t\t" << (m[rr][cc] - m[r][c]) << std::endl;
            // if (m[rr][cc] == '#')            // Må fikse her
            // if (m[r][c] - m[rr][cc] > 1)
            if (m[rr][cc] - m[r][c] > 1)
            {
                std::cout << "\tUaktuell kandidat." << std::endl;
                continue;
            }
            else
            {

                std::cout << "\tGår videre" << std::endl;
            }
            /*
            rq.push_back(rr);
            cq.push_back(cc);
            */
            rq.emplace_back(rr);
            cq.emplace_back(cc);
            visited[rr][cc] = true;
            nodesInNextLayer++;
        }
        nodesLeftInLayer--;
        if (nodesLeftInLayer == 0)
        {
            nodesLeftInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
            std::cout << "INKREMENTERER MOEVCOUNT " << std::endl;
            moveCount++;
        }
    }
    if (reachEnd == true)
    {
        std::cout << "HAR NÅDD ENDEN" << std::endl;
        return moveCount;
    }
    return -1;
}

int main()
{
    // std::string filename("small");
    std::string filename("input");
    int res = bfs(filename);
    std::cout << "Part 1: " << res << std::endl;
}