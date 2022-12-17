#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <complex>
#include <unordered_map>
#include <map>

int main()
{
    std::cout << "Hello world \n";
    // std::ifstream file("small");
    std::ifstream file("input");
    std::string line;
    getline(file, line);
    file.close();
    int windSize = line.size();
    // Use bits to indicate rock occupancy
    std::vector<int> rocks[5] = {{0x1E}, {0x08, 0x1C, 0x08}, {0x1C, 0x04, 0x04}, {0x10, 0x10, 0x10, 0x10}, {0x18, 0x18}};

    int side[5][2] = {{-2, 1}, {-2, 2}, {-2, 2}, {-2, 4}, {-2, 3}};

    std::vector<int> field;
    int sp = 0;
    int lineIdx = 0;

    field.push_back(0x7F);

    auto stonefit = [&](int rock, int shift, int bp) -> bool
    {
        for (int r = 0; r < rocks[rock].size(); r++)
        {
            int sv = shift > 0 ? rocks[rock][r] >> shift : rocks[rock][r] << -shift;
            if (bp + r < field.size() && (field[bp + r] & sv))
                return false;
        }
        return true;
    };

    std::vector<int> heights;
    std::map<std::pair<int, int>, std::vector<int>> drops;
    std::map<int, int> loopCount;

    while (true)
    {
        int bp = field.size() + 3;
        int shift = 0;
        bool drop = true;
        do
        {
            // Blow the wind
            switch (line[lineIdx])
            {
            case '<':
                if (shift != side[sp % 5][0] && stonefit(sp % 5, shift - 1, bp))
                {
                    shift--;
                }
                break;
            case '>':
                if (shift != side[sp % 5][1] && stonefit(sp % 5, shift + 1, bp))
                {
                    shift++;
                }
                break;
            }

            lineIdx = (lineIdx + 1) % windSize;
            drop = stonefit(sp % 5, shift, bp - 1);
            if (drop)
            {
                --bp;
            }
        } while (drop);
        int top = bp + rocks[sp % 5].size();
        if (field.size() < top)
        {
            field.resize(top);
        }
        for (int r = 0; r < rocks[sp % 5].size(); r++)
        {
            int sv = shift > 0 ? rocks[sp % 5][r] >> shift : rocks[sp % 5][r] << -shift;
            field[bp + r] |= sv;
        }
        ++sp;
        heights.push_back(field.size() - 1);

        auto check = std::make_pair((sp - 1) % 5, (lineIdx - 1 + windSize) % windSize);
        if (drops[check].size() != 0)
        {
            for (int x : drops[check])
            {
                int d = (sp - 1) - x;
                loopCount[d]++;
            }
        }
        drops[check].push_back(sp - 1);
        if (sp == 2022)
        {
            std::cout << "Part 1: " << field.size() - 1 << std::endl;
            return 0;
        }
    }
    return 0;
}