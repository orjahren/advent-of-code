#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <sstream>

typedef long long ll;

using namespace std;

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}

struct Node
{
    int x, y, z;
    int id;
};
string nodeToString(Node *node)
{
    stringstream ss;
    ss << "{" << node->x << ", " << node->y << ", " << node->z << "}";
    return ss.str();
}

Node *lineToNode(string &line, int idCounter)
{
    Node *n = new Node();

    auto spl = split(line, ',');
    int x = stoi(spl[0]);
    int y = stoi(spl[1]);
    int z = stoi(spl[2]);

    n->x = x;
    n->y = y;
    n->z = z;
    n->id = idCounter;

    return n;
}

int main()
{
    string inp;

    map<int, Node *> nodeMap;

    vector<Node *> nodes;

    string s;
    int idCounter = 0;
    while (cin >> s)
    {
        cout << "s: " << s << endl;
        // cin >> y >> z;
        Node *n = lineToNode(s, idCounter++);
        nodes.push_back(n);
        nodeMap[n->id] = n;
    }

    for (auto n : nodes)
    {
        cout << "node " << n->id << ": " << nodeToString(n) << endl;
    }

    ll p1 = 0;
    cout << "Part 1: " << p1 << endl;

    return 0;
}
