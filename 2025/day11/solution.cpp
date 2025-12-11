#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <unordered_set>
#include <queue>
#include <unordered_map>

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

ll countPathsMemo(Node *from, Node *target, map<string, Node *> &nodeMap, unordered_map<string, ll> &memo, unordered_set<string> &visiting)
{
    if (from == nullptr || target == nullptr)
        return 0;

    string key = from->name + "|" + target->name;
    if (memo.count(key))
        return memo[key];

    if (from->name == target->name)
        return memo[key] = 1;

    if (visiting.count(from->name))
        return 0;

    visiting.insert(from->name);

    ll total = 0;
    for (const auto &childName : from->childNames)
    {
        auto it = nodeMap.find(childName);
        if (it == nodeMap.end())
            continue;

        total += countPathsMemo(it->second, target, nodeMap, memo, visiting);
    }

    visiting.erase(from->name);
    memo[key] = total;
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
        unordered_map<string, ll> memo;
        unordered_set<string> visiting;
        return countPathsMemo(nodeMap[fromName], nodeMap[toName], nodeMap, memo, visiting);
    };

    ll p1 = countPaths("you", "out");
    cout << "Part 1: " << p1 << endl;

    ll p2 = countPaths("svr", "fft") * countPaths("fft", "dac") * countPaths("dac", "out");
    cout << "Part 2: " << p2 << endl;

    return 0;
}
