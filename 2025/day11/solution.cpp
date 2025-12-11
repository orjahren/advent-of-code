#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <unordered_set>

typedef long long ll;

using namespace std;

struct Node
{
    string name;
    vector<string> childNames;
};

void printNode(Node *n, int depth)
{
    for (int i = 0; i < depth; i++)
        cout << "  ";
    cout << n->name << endl;
    for (auto c : n->childNames)
    {
        for (int i = 0; i < depth + 1; i++)
            cout << "  ";
        cout << c << endl;
    }
}

vector<vector<string>> getAllPathsDfs(Node *from, Node *target, map<string, Node *> &nodeMap, vector<string> &path, unordered_set<string> &visiting)
{
    if (visiting.count(from->name))
        return {};

    visiting.insert(from->name);
    path.push_back(from->name);

    vector<vector<string>> paths;

    if (from->name == target->name)
    {
        paths.push_back(path);
    }
    else
    {
        for (auto &childName : from->childNames)
        {
            auto it = nodeMap.find(childName);
            if (it == nodeMap.end())
                continue;

            Node *childNode = it->second;
            auto childPaths = getAllPathsDfs(childNode, target, nodeMap, path, visiting);
            paths.insert(paths.end(), childPaths.begin(), childPaths.end());
        }
    }

    path.pop_back();
    visiting.erase(from->name);

    return paths;
}

int main()
{
    string inp;
    int i = 0;

    // Edge case.
    Node *out = new Node();
    out->name = "out";

    vector<Node *> nodes{out};

    Node *n;
    while (cin >> inp)
    {
        if (inp.find(":") != string::npos)
        {
            n = new Node();
            string name = inp.substr(0, inp.find(":"));
            n->name = name;
            nodes.push_back(n);
        }
        else
        {
            n->childNames.push_back(inp);
        }
    }

    map<string, Node *> nodeMap;
    nodeMap["out"] = out;

    for (auto n : nodes)
    {
        printNode(n, 0);
        nodeMap[n->name] = n;
    }

    vector<string> path;
    unordered_set<string> visiting;

    int p2 = 0;
    cout << "Beginning Part 2 computation..." << endl;
    auto pathsP2 = getAllPathsDfs(nodeMap["svr"], nodeMap["out"], nodeMap, path, visiting);
    cout << "Total paths from 'svr' to 'out': " << pathsP2.size() << endl;
    vector<string> mustContain{"dac", "fft"};
    for (auto p : pathsP2)
    {
        cout << "Checking path: ";
        for (auto pn : p)
        {
            cout << pn << " ";
        }
        cout << endl;
        bool containsAll = true;
        for (auto mc : mustContain)
        {
            if (find(p.begin(), p.end(), mc) == p.end())
            {
                containsAll = false;
                break;
            }
        }
        if (containsAll)
        {
            p2++;
        }
    }
    cout << "Part 2: " << p2 << endl;

    return 0;
    auto paths = getAllPathsDfs(nodeMap["you"], nodeMap["out"], nodeMap, path, visiting);
    cout << "All paths from 'you' to 'out':" << endl;
    for (auto p : paths)
    {
        for (int j = 0; j < p.size(); j++)
        {
            string nodeName = p[j];
            if (j < p.size() - 1)
                cout << nodeName << " -> ";
            else
                cout << nodeName;
        }
        cout << endl;
    }
    cout << endl;

    cout << "Total paths: " << paths.size() << endl;

    int p1 = 0;

    cout << "Part 1: " << p1 << endl;
}
