#include <iostream>
#include <map>
#include <fstream>
#include <ios>
#include <vector>

class File
{
public:
    int size;
    std::string *path;

    File(std::string *path, int size)
    {
        this->path = path;
        this->size = size;
    }
};

class Folder
{
public:
    std::string *path;
    std::vector<File *> file_pointers;
    std::vector<Folder *> subfolder_pointers;

    int totalSize;

    Folder(std::string *absPath)
    {
        this->path = absPath;
        this->totalSize = -1;
    }

    int getSize()
    {
        if (this->totalSize < 0)
        {
            int res = 0;
            for (int i = 0; i < this->file_pointers.size(); i++)
            {
                res += this->file_pointers.at(i)->size;
            }

            for (int i = 0; i < this->subfolder_pointers.size(); i++)
            {
                res += this->subfolder_pointers.at(i)->getSize();
            }
            this->totalSize = res;
        }
        return this->totalSize;
    }
};

std::string getPath(std::vector<std::string *> path)
{
    std::string s = "/";
    for (int i = 1; i < path.size(); i++)
    {
        s += "/" + *path.at(i);
    }
    return s;
}

int findSpaceIndex(std::string &s)
{
    return s.find(" ") + 1;
}

std::string getNameFromLine(std::string line)
{
    return line.substr(findSpaceIndex(line));
}

int getFileSizeFromLine(std::string line)
{
    return stoi(line.substr(0, findSpaceIndex(line)));
}

int main()
{
    std::string line;
    std::ifstream minFil("input");

    std::map<std::string, Folder *> fs;
    fs["/"] = new Folder(new std::string("/"));

    std::vector<Folder *> allFolders;
    std::vector<std::string *> path;

    while (getline(minFil, line))
    {
        if (line[0] == '$')
        {
            if (line[2] == 'c')
            {
                if (line[5] == '.')
                {
                    path.pop_back();
                }
                else
                {
                    std::size_t spaceIndex = line.substr(2).find(" ") + 3;
                    path.push_back(new std::string(line.substr(spaceIndex)));
                }
            }
        }
        else
        {
            if (line[0] == 'd')
            {
                std::string absPath = getPath(path);
                std::string newFolderName = getNameFromLine(line);
                std::string newPath = absPath + "/" + newFolderName;
                Folder *newFolder = new Folder(&newPath);
                fs[absPath]->subfolder_pointers.push_back(newFolder);
                fs[newPath] = newFolder;
                allFolders.push_back(newFolder);
            }
            else
            {
                std::string absPath = getPath(path);
                std::string filePath = absPath + "/" + getNameFromLine(line);
                fs[absPath]->file_pointers.push_back(new File(&filePath, getFileSizeFromLine(line)));
            }
        }
    }

    int part1Res = 0;
    int mustDelete = 30000000 - (70000000 - fs["/"]->getSize());
    std::vector<int> cands;
    for (int i = 0; i < allFolders.size(); i++)
    {
        int size = allFolders.at(i)->getSize();
        if (size <= 100000)
        {
            part1Res += size;
        }
        if (size >= mustDelete)
        {
            cands.push_back(size);
        }
    }
    std::cout << "Part 1: " << part1Res << std::endl;

    int currMin = INT_MAX;
    for (int i = 0; i < cands.size(); i++)
    {
        int curr = cands.at(i);
        if (curr < currMin)
        {
            currMin = curr;
        }
    }
    std::cout << "Part 2: " << currMin << std::endl;
    return 0;
}