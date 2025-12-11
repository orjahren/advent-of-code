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

ll countPathsDfs(Node *from, Node *target, map<string, Node *> &nodeMap, unordered_set<string> &visiting)
{
    if (from == nullptr || target == nullptr || visiting.count(from->name))
        return 0;

    if (from->name == target->name)
        return 1;

    visiting.insert(from->name);

    ll total = 0;
    for (const auto &childName : from->childNames)
    {
        auto it = nodeMap.find(childName);
        if (it == nodeMap.end())
            continue;

        total += countPathsDfs(it->second, target, nodeMap, visiting);
    }

    visiting.erase(from->name);
    return total;
}

int main()
{
    string inp;
    int i = 0;

    // Edge case.
    Node *out = new Node();
    out->name = "out";

    map<string, Node *> nodeMap;
    nodeMap["out"] = out;
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

    for (auto n : nodes)
    {
        printNode(n, 0);
        nodeMap[n->name] = n;
    }

    auto countPaths = [&](const string &fromName, const string &toName) -> ll
    {
        unordered_set<string> visiting;
        return countPathsDfs(nodeMap[fromName], nodeMap[toName], nodeMap, visiting);
    };

    ll p1 = countPaths("you", "out");
    cout << "Part 1: " << p1 << endl;

    cout << "Beginning Part 2 computation..." << endl;

    ll a = countPaths("svr", "fft");
    cout << "Paths from 'svr' to 'fft': " << a << endl;

    ll b = countPaths("fft", "dac");
    cout << "Paths from 'fft' to 'dac': " << b << endl;

    ll c = countPaths("dac", "out");
    cout << "Paths from 'dac' to 'out': " << c << endl;

    ll p2 = a * b * c;
    cout << "Total paths from 'svr' to 'out': " << p2 << endl;
    cout << "Part 2: " << p2 << endl;

    return 0;
}
