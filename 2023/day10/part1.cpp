#include <bits/stdc++.h>
using namespace std;
struct Node
{
    char val;
    int posX, posY;
    vector<Node *> edges;
};

int main()
{
    string s;
    int posY = 0;
    vector<Node *> nodes;
    while (cin >> s && ++posY)
    {
        cout << s << endl;
        for (int i = 0; i < s.size(); i++)
        {
            Node *n = new Node();
            n->val = s[i];
            n->posX = i;
            n->posY = posY;
            nodes.push_back(n);
        }
    }
    cout << "nodes.size() = " << nodes.size() << endl;
}