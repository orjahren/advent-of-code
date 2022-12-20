#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#define LOG(x) std::cout << x << std::endl;

void printArr(std::vector<int> &arr, int n)
{
    std::cout << "\t\t[";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << ", ";
    }
    LOG("]")
}

int main()
{
    std::string line;
    std::vector<std::pair<int, int>> pairs;
    std::vector<int> arr;
    std::ifstream file("small");

    int lineCounter = 0;
    while (getline(file, line))
    {
        LOG(line)
        int x = std::stoi(line);
        std::pair<int, int> p = std::make_pair(lineCounter++, x);
        pairs.push_back(p);
        arr.push_back(x);
    }
    LOG("Har lest fil")
    LOG("Initial status:")
    printArr(arr, pairs.size());
    std::cout << "Begynner simulering..\n";
    for (int i = 0; i < pairs.size(); i++)
    {
        std::pair<int, int> p = pairs.at(i);
        // int newIdx = (((i + p.second) % pairs.size()) + pairs.size()) % pairs.size(); // burde ikke gjøre denne beregningen hvis casen under slår inn
        int newIdx = (((p.first + p.second) % pairs.size()) + pairs.size()) % pairs.size(); // burde ikke gjøre denne beregningen hvis casen under slår inn
        /*
        if (i + p.second < 0)
        {
            newIdx = pairs.size() + p.second; // subtraher fra slutten
            LOG("Hacket ny idx til: " << newIdx)
        }
        */

        if (newIdx < 0)
        {
            LOG("FEIL med ny idx: " << newIdx)
            return 1;
        }
        LOG("\t Skal flytte " << p.second << " fra " << p.first << " til " << newIdx)
        arr.erase(arr.begin() + p.first);
        arr.insert(arr.begin() + newIdx, p.second);
        p.first = newIdx;
        printArr(arr, pairs.size());

        LOG("Oppdaterer indexer")
        for (int j = 0; j < pairs.size(); j++)
        {
            pairs.at(j).first = j;
        }
    }
    LOG("...done")
    LOG("Final array: ")
    printArr(arr, pairs.size());
}