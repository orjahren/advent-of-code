#include <iostream>
#include <map>
#include <fstream>
#include <ios>

int main()
{
    std::cout << "Salut le monde" << std::endl;
    std::string line;
    std::ifstream minFil("small");
    std::map<std::string, int> hm;

    if (minFil.is_open())
    {
        std::cout << "Fikk lest fil helt fint " << std::endl;
        std::string workingDir;
        while (getline(minFil, line))
        {
            std::cout << "Leste: " << line << std::endl;
            if (line[0] == '$')
            {

                if (line[2] == 'c')
                {                      // La dette være cd
                    workingDir = line; // -> klarer ikke deale med 'cd ..'
                }
                else if (line[2] == 'l')
                {
                    hm[workingDir] = 0;
                }
                else
                {
                    std::cout << "Ukjent feil med parsing av kommando..." << std::endl;
                }
            }
            else
            {
                if (line[0] == 'd')
                {
                    // Ikke gjør noe for dirs?
                }
                else
                {

                    std::string numberSubstring = line.substr(0, line.find(" "));
                    std::cout
                        << "Uparset numberString for " << workingDir << ": " << numberSubstring << std::endl;
                    hm[workingDir] += stoi(numberSubstring);
                }
            }
        }
    }
    return 0;
}