#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

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
        std::pair<int, int> &p = pairs.at(i);
        // int newIdx = (((i + p.second) % pairs.size()) + pairs.size()) % pairs.size(); // burde ikke gjøre denne beregningen hvis casen under slår inn
        // int newIdx = (((p.first + p.second) % pairs.size()) + pairs.size()) % pairs.size(); // burde ikke gjøre denne beregningen hvis casen under slår inn
        int newIdx = (((p.first + p.second) % pairs.size()) + pairs.size()) % pairs.size(); // burde ikke gjøre denne beregningen hvis casen under slår inn
        if (i + p.second <= 0)
        {
            newIdx = pairs.size() + p.second; // subtraher fra slutten
            LOG("Hacket ny idx til: " << newIdx)
        }

        if (newIdx < 0)
        {
            LOG("FEIL med ny idx: " << newIdx)
            return 1;
        }
        LOG("\t Skal flytte " << p.second << " fra " << p.first << " til " << newIdx)
        std::cout << "Før: \t";
        printArr(arr, pairs.size());
        /*
        arr.insert(arr.begin() + newIdx, p.second);
        arr.erase(arr.begin() + p.first);
        */
        arr.erase(arr.begin() + p.first);
        arr.insert(arr.begin() + newIdx, p.second);

        p.first = newIdx;
        std::cout << "Etter: \t";
        printArr(arr, pairs.size());

        LOG("Oppdaterer indexer")
        for (int j = 0; j < pairs.size(); j++)
        {
            // pairs.at(j).first = j;
            auto idx = std::find(arr.begin(), arr.end(), pairs.at(j).second);
            if (idx != arr.end())
            {
                std::cout << "Fant " << *idx << " på " << idx - arr.begin() << std::endl;
                pairs.at(j).first = idx - arr.begin();
            }
            else
            {
                LOG("Fant ikke " << pairs.at(j).second << " i arr...");
                return 1;
            }
            //  pairs.at(j).first = arr.begin(), arr.end(), pairs.at(j).second);
            /*
            std::pair<int, int> &p = pairs.at(j);
            arr.at(j) = p.second;
            */
        }
    }
    LOG("...done")
    LOG("Final array: ")
    printArr(arr, pairs.size());
}