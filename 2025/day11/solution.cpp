#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>

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

vector<vector<string>> getAllPathsDfs(Node *from, Node *target, map<string, Node *> &nodeMap, vector<string> &path)
{
    cout << "Visiting node: " << from->name << endl;
    path.push_back(from->name);

    vector<vector<string>> paths;

    if (from->name == target->name)
    {
        paths.push_back(path);
    }
    else
    {
        for (auto childName : from->childNames)
        {
            Node *childNode = nodeMap[childName];
            auto childPaths = getAllPathsDfs(childNode, target, nodeMap, path);
            for (auto cp : childPaths)
            {
                paths.push_back(cp);
            }
        }
    }

    path.pop_back();

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
    auto paths = getAllPathsDfs(nodeMap["you"], nodeMap["out"], nodeMap, path);
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
