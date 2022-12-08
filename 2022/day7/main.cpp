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
        std::cout << "Opprettet en ny fil på " << *path << std::endl;
    }
};

class Folder
{
public:
    std::string *path;
    std::vector<File> files;
    std::vector<Folder> subfolders;

    // int totalSize;

    Folder(std::string *absPath)
    {
        this->path = absPath;
        // this->totalSize = -1;
        std::cout << "Opprettet en folder" << std::endl;
    }

    int getSize()
    {
        /*
        if (this->totalSize > -1)
        {
            return this->totalSize;
        }
        */
        std::cout << "Je suis en folder som skal finne min størrelse." << std::endl;
        int res = 0;
        // std::cout << "Mine files er: " << this->files << std::endl;
        // for (File f : this->files)
        for (int i = 0; i < this->files.size(); i++)
        {
            File f = this->files.at(i);
            std::cout << "Jeg har en fil med " << f.size << "  size" << std::endl;
            res += f.size;
        }

        for (Folder f : this->subfolders)
        {
            int fz = f.getSize();
            std::cout << "Og jeg har en mappe med " << fz << std::endl;
            // res += f.getSize();
            res += fz;
        }
        // this->totalSize = res;
        return res;
    }
};

std::string getPath(std::vector<std::string> path)
{
    std::cout << "Skal generere path fra denne vektoren med strenger: " << std::endl;
    for (auto x : path)
    {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    std::string s = "/"; // = "ssss";
    if (path.size() == 1)
    {
        s = "/";
    }
    else
    {
        // for (auto x : path) {
        for (int i = 1; i < path.size(); i++)
        {
            std::cout << "Appender dette til pathen: '" << path.at(i) << "'" << std::endl;
            s += "/" + path.at(i);
        }
    }
    std::cout << "Lagde denne stien: " << s << std::endl;
    return s;
}

std::string getFolderNameFromLine(std::string line)
{
    std::cout << "Skal finne folder-navn fra denne linjen: " << line << std::endl;
    std::size_t spaceIndex = line.find(" ") + 1;
    std::cout << "Fant " << line.substr(spaceIndex) << std::endl;
    return line.substr(spaceIndex);
}

std::string getFileNameFromLine(std::string line)
{
    std::cout << "Skal finne file-navn fra denne linjen: " << line << std::endl;
    std::size_t spaceIndex = line.find(" ") + 1;
    std::cout << "Fant " << line.substr(spaceIndex) << std::endl;
    return line.substr(spaceIndex);
}

int getFileSizeFromLine(std::string line)
{
    std::cout << "Skal finne file-size fra denne linjen: " << line << std::endl;
    std::size_t spaceIndex = line.find(" ") + 1;
    std::cout << "Fant " << line.substr(0, spaceIndex) << std::endl;
    return stoi(line.substr(0, spaceIndex));
}

int main()
{
    std::cout << "Salut le monde" << std::endl;
    std::string line;
    std::ifstream minFil("small");

    // std::map<std::string, Folder> fs;
    std::map<std::string, Folder *> fs;
    std::string rootPath = "/";
    Folder root(&rootPath);
    fs["/"] = &root;

    std::vector<Folder> allFolders;

    std::vector<std::string> path;

    if (minFil.is_open())
    {
        std::cout << "Fikk lest fil helt fint " << std::endl;
        std::string workingDir;
        while (getline(minFil, line))
        {
            std::cout << "Leste: " << line << std::endl;
            if (line[0] == '$')
            {
                if (line[2] == 'c') // La dette være cd
                {
                    if (line[5] == '.')
                    { // cd ..
                        path.pop_back();
                        path.pop_back();
                    }
                    else
                    { // cd <en faktisk folder>
                        std::size_t spaceIndex = line.substr(2).find(" ") + 3;
                        std::cout << "Space index er: " << spaceIndex << std::endl;
                        std::string nav_to_folder = line.substr(spaceIndex);
                        std::cout << "Pusher back dette folder-navnet: " << nav_to_folder << std::endl;
                        path.push_back(nav_to_folder);
                    }
                }
            }
            else
            {
                if (line[0] == 'd')
                {
                    // Ikke gjør noe for dirs?
                    std::cout << "Finner abspath for hvor den nye folderen skal havne" << std::endl;
                    std::string absPath = getPath(path);
                    std::cout << "Henter parentFolder basert på denne absPath" << std::endl;
                    Folder *parentFolder = fs[absPath];
                    std::cout << "Denne parent er " << parentFolder << std::endl;
                    std::string newFolderName = getFolderNameFromLine(line);
                    std::string newPath = absPath + "/" + newFolderName;
                    // std::string newPath = absPath + newFolderName;
                    std::cout << "Skal lage en ny folder på stien " << newPath << std::endl;
                    Folder *newFolder = new Folder(&absPath);
                    std::cout << "Skal legge den nye folderen i subolders til parent" << std::endl;
                    parentFolder->subfolders.push_back(*newFolder);
                    std::cout << "Skal lagre nye folderen i fs" << std::endl;
                    fs[newPath] = newFolder;
                    std::cout << "Pusher ny folder til allFolders" << std::endl;
                    allFolders.push_back(*newFolder);
                }
                else
                {
                    std::string absPath = getPath(path);
                    Folder *folder = fs[absPath];

                    std::string fileName = getFileNameFromLine(line);
                    int fileSize = getFileSizeFromLine(line);
                    std::string filePath = absPath + "/" + fileName;
                    File *newFile = new File(&filePath, fileSize);
                    folder->files.push_back(*newFile);
                }
            }
        }
    }

    std::vector<int> cands;
    int roof = 100000;
    // Finn cands
    int part1Res = 0;
    for (int i = 0; i < allFolders.size(); i++)
    {
        Folder f = allFolders.at(i);
        int size = f.getSize();
        std::cout << "Size er " << size << std::endl;
        if (size <= roof)
        {
            // cands.push_back(size);
            part1Res += size;
        }
    }
    std::cout << "Part 1: " << part1Res << std::endl;
    /*
        for (int i = 0; i < cands.size(); i++)
        {
            int curr = cands.at(i);
            if (curr < roof)
            {
                // currMin = curr;
            }
        }

        for (int i = 0; i < allFolders.size(); i++)
        {
            Folder f = allFolders.at(i);
            int size = f.getSize();
            if (size <= roof)
            {
                cands.push_back(size);
            }
        }
        // Finn minste cand
        int currMin = 999999;
        for (int i = 0; i < cands.size(); i++)
        {
            int curr = cands.at(i);
            if (curr < currMin)
            {
                currMin = curr;
            }
        }
    */
    return 0;
}