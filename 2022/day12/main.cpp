#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <deque>

#define pb push_back

int bfs(std::vector<std::string> lines, int sr, int sc)
{
    std::cout << "Starter BFS" << std::endl;
    const int height = lines[0].size();
    const int width = lines.size();
    std::cout << "Grid size: " << width << "x" << height << std::endl;

    const int R = height;
    const int C = width;

    char m[R][C];
    bool visited[R][C];
    int goalI = -1;
    int goalJ = -1;

    std::cout << "SR og SC før: " << sr << ", " << sc << std::endl;

    for (int i = 0; i < width; i++)
    {
        std::string l = lines.at(i);
        for (int j = 0; j < height; j++)
        {
            char c = l[j];
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
                std::cout << "SETTER SR og SC: " << sr << ", " << sc << std::endl;
                m[j][i] = 'a';
                // sr = j;
                // sc = i;
                std::cout << "SETTER SR og SC: " << sr << ", " << sc << std::endl;
            }
            std::cout << m[j][i];
        }
        std::cout << std::endl;
    }

    std::cout << "TARGET: " << goalI << ", " << goalJ << std::endl;
    std::cout << "SR og SC etter: " << sr << ", " << sc << std::endl;

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
        std::cout << moveCount << std::endl;

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
    std::string line;
    std::ifstream file(filename);
    std::vector<std::string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    std::vector<int> a_x;
    std::vector<int> a_y;
    for (int i = 0; i < lines.size(); i++)
    {
        std::string l = lines.at(i);
        for (int j = 0; j < lines[0].size(); j++)
        {
            char c = l[j];
            if (c == 'E')
            {
                // TODO: Should save these as argument for bfs function
                // tarR = j;
                // tarC = i;
            }
            else if (c == 'a')
            {
                a_x.pb(i);
                a_y.pb(j);
            }
        }
    }
    std::cout << "Part 1: " << bfs(lines, 0, 0) << std::endl;

    std::vector<int> part2Options;
    while (a_x.size() > 0)
    {
        int x = a_x.back();
        a_x.pop_back();

        int y = a_y.back();
        a_y.pop_back();

        int val = bfs(lines, y, x);
        if (val != -1)
        {

            part2Options.pb(val);
        }
    }
    std::sort(part2Options.begin(), part2Options.end());
    std::cout << "Part 2: " << part2Options[0] << std::endl;
}