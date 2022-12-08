#include <iostream>
#include <map>
#include <fstream>
#include <ios>
#include <vector>

#define LOG(x) std::cout << x << std::endl;
#define ll long long

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
    if (path.size() != 1)
    {
        for (int i = 1; i < path.size(); i++)
        {
            s += "/" + *path.at(i);
        }
    }
    return s;
}

std::string getNameFromLine(std::string line)
{
    std::size_t spaceIndex = line.find(" ") + 1;
    return line.substr(spaceIndex);
}

int getFileSizeFromLine(std::string line)
{
    std::size_t spaceIndex = line.find(" ") + 1;
    return stoi(line.substr(0, spaceIndex));
}

int main()
{
    std::string line;
    std::ifstream minFil("input");

    std::map<std::string, Folder *> fs;
    std::string rootPath = "/";
    Folder root(&rootPath);
    fs["/"] = &root;

    std::vector<Folder *> allFolders;

    std::vector<std::string *> path;

    if (minFil.is_open())
    {
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
                        std::string *nav_to_folder = new std::string(line.substr(spaceIndex));
                        path.push_back(nav_to_folder);
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
                    Folder &parentFolder = *fs[absPath];
                    parentFolder.subfolder_pointers.push_back(newFolder);
                    fs[newPath] = newFolder;
                    allFolders.push_back(newFolder);
                }
                else
                {
                    std::string absPath = getPath(path);
                    Folder *folder = fs[absPath];
                    std::string fileName = getNameFromLine(line);
                    int fileSize = getFileSizeFromLine(line);
                    std::string filePath = absPath + "/" + fileName;
                    File *newFile = new File(&filePath, fileSize);
                    folder->file_pointers.push_back(newFile);
                }
            }
        }
    }

    int roof = 100000;
    int part1Res = 0;
    ll mustDelete = 30000000 - (70000000 - fs["/"]->getSize());
    std::vector<int> cands;
    for (int i = 0; i < allFolders.size(); i++)
    {
        int size = allFolders.at(i)->getSize();
        if (size <= roof)
        {
            part1Res += size;
        }
        if (size >= mustDelete)
        {
            cands.push_back(size);
        }
    }

    std::cout << "Part 1: " << part1Res << std::endl;

    ll currMin = INT_MAX;
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