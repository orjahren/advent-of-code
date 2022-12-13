#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string filename("small");
    std::string x;
    std::string y;
    int part1Matches;
    std::ifstream file(filename);
    while (getline(file, x))
    {
        getline(file, y);
        // PERFORM ACTION

        // discard newlilne
        getline(file, y);
    }
    std::cout << "Part 1: " << part1Matches << std::endl;
}