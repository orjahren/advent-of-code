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

#define N_CONNECTIONS 1000
#define K_BIGGEST 3

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

ll getEuclideanDistance(Node *a, Node *b)
{
    ll dx = a->x - b->x;
    ll dy = a->y - b->y;
    ll dz = a->z - b->z;

    return dx * dx + dy * dy + dz * dz;
}

int root(Node *n, vector<int> &parent, map<int, Node *> &nodeMap)
{
    if (parent[n->id] == n->id)
    {
        return n->id;
    }
    parent[n->id] = root(nodeMap[parent[n->id]], parent, nodeMap);
    return parent[n->id];
}

void merge(Node *a, Node *b, vector<int> &parent, map<int, Node *> &nodeMap)
{
    int rootA = root(a, parent, nodeMap);
    int rootB = root(b, parent, nodeMap);

    if (rootA != rootB)
    {
        // parent[rootB] = rootA;
        parent[rootA] = rootB;
    }
}

int main()
{
    string inp;

    map<int, Node *> nodeMap;

    vector<Node *> nodes;

    string s;
    int idCounter = 0;
    vector<int> parent, sizes;

    while (cin >> s)
    {
        cout << "s: " << s << endl;
        // cin >> y >> z;
        Node *n = lineToNode(s, idCounter++);
        nodes.push_back(n);
        nodeMap[n->id] = n;
        parent.push_back(n->id);
        sizes.push_back(0);
    }

    for (auto n : nodes)
    {
        cout << "node " << n->id << ": " << nodeToString(n) << endl;
    }

    vector<pair<int, int>> edges;
    // genererer alle mulige kanter
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            auto p = make_pair(i, j);
            edges.push_back(p);
        }
    }

    // sorterer kanter utifra avstand
    sort(edges.begin(), edges.end(), [&](pair<int, int> &a, pair<int, int> &b)
         {
             Node *n1 = nodes[a.first];
             Node *n2 = nodes[a.second];
             Node *m1 = nodes[b.first];
             Node *m2 = nodes[b.second];

             ll distA = getEuclideanDistance(n1, n2);
             ll distB = getEuclideanDistance(m1, m2);

             return distA < distB; });

    // print edges
    cout << "Edges sorted by distance:" << endl;
    for (auto &e : edges)
    {
        Node *n1 = nodes[e.first];
        Node *n2 = nodes[e.second];
        ll dist = getEuclideanDistance(n1, n2);
        cout << "Edge: (" << n1->id << ", " << n2->id << ") - Distance: " << dist << endl;
    }

    for (int i = 0; i < N_CONNECTIONS && i < edges.size(); i++)
    {
        auto &e = edges[i];
        Node *n1 = nodes[e.first];
        Node *n2 = nodes[e.second];
        cout << "Connecting nodes " << n1->id << " and " << n2->id << endl;
        merge(n1, n2, parent, nodeMap);
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        int rootId = root(nodes[i], parent, nodeMap);
        sizes[rootId]++;
    }

    // sort(sizes.begin(), sizes.end(), greater<int>());
    sort(sizes.begin(), sizes.end(), [](int a, int b)
         { return a > b; });

    // print sizes
    cout << "Component sizes:" << endl;
    for (int i = 0; i < sizes.size(); i++)
    {
        cout << "Component " << i << ": Size " << sizes[i] << endl;
    }

    ll p1 = 1;
    for (int i = 0; i < K_BIGGEST; i++)
    {
        p1 *= sizes[i];
    }
    cout << "Part 1: " << p1 << endl;

    return 0;
}
