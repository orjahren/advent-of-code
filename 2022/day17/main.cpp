#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <complex>

#define LOG(x) std::cout << x << std::endl;

class Rock
{

public:
    char formation[4][4];
    short rockCount;
    Rock()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                this->formation[i][j] = '.';
            }
        }
    }
    void fall(char direction, char grid[7][1000])
    {
    }
    void lock()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                char c = this->formation[i][j];
                if (c == '#')
                {
                    this->formation[i][j] = '#';
                }
            }
        }
    }
    void draw()
    {

        LOG("Skal tegne en stein")
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                char c = this->formation[i][j];
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }
};

Rock makeRock(int type)
{
    LOG("SKal lage en rock av type " << type)
    Rock r;
    // Flat strek bortover
    if (type == 1)
    {
        for (short i = 0; i < 4; i++)
        {
            r.formation[0][i] = '@';
        }
        r.rockCount = 4;

    } // pluss
    else if (type == 2)
    {
        // Topp
        r.formation[0][1] = '#';
        // Vertikal rad
        for (short i = 0; i < 3; i++)
        {
            r.formation[1][i] = '@';
        }
        // Bunn
        r.formation[2][1] = '@';
        r.rockCount = 5;

    } // Speilvendt l
    else if (type == 3)
    {
        // Nedover
        for (short i = 0; i < 3; i++)
        {
            r.formation[i][2] = '@';
        }
        // Bortover nederst
        for (short i = 0; i < 2; i++)
        {
            r.formation[2][i] = '@';
        }
        r.rockCount = 5;
    }
    // Rett strek nedover
    else if (type == 4)
    {
        // Nedover
        for (short i = 0; i < 5; i++)
        {
            r.formation[i][0] = '@';
            ;
        }
        r.rockCount = 4;
    } // kompakt firkant
    else if (type == 5)
    {
        for (short i = 0; i < 2; i++)
        {
            for (short j = 0; j < 2; j++)
            {
                r.formation[i][j] = '@';
            }
        }
        r.rockCount = 4;
    }
    return r;
}
void drawGrid(char grid[7][1000])
{
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            char c = grid[j][i];
            std::cout << c;
        }
        std::cout << std::endl;
    }
}
int main()
{
    std::cout << "Hello world \n";
    char grid[7][1000];
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            grid[j][i] = '.';
        }
    }
    drawGrid(grid);
    Rock rockTypes[5];
    /*
    for (int i = 1; i < 6; i++)
    {

        Rock r = makeRock(i);
        r.draw();
    }
    */
    std::ifstream file("small");
    std::string line;
    getline(file, line);
    file.close();
    LOG(line)
    int operationIndex = 0;
    int stoppedRocks = 0;
    int rockCounter = 0;
    bool isFalling = false;
    // for (int iteration = 1; iteration < 2022; iteration++)
    while (rockCounter < 2022)
    {
        if (!isFalling)
        {
            isFalling = true;
            rockCounter++;
            Rock r = makeRock(rockCounter % 5 == 0 ? 5 : rockCounter % 5);
            // int val = rockCounter % 5 == 0 ? 5 : rockCounter % 5;
            // std::cout << val << std::endl;
        }
    }
}