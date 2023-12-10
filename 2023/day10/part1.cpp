#include <bits/stdc++.h>
using namespace std;
struct Node
{
    char val;
    int posX, posY;
    vector<Node *> edges;
};

void setEdgesForNode(Node *n, vector<vector<Node *>> &grid)
{
    /*
    The pipes are arranged in a two-dimensional grid of tiles:
    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
    */
    if (n->val == '|')
    {
        if (n->posY > 0 && grid[n->posY - 1][n->posX]->val == '|')
        {
            n->edges.push_back(grid[n->posY - 1][n->posX]);
        }
        if (n->posY < grid.size() - 1 && grid[n->posY + 1][n->posX]->val == '|')
        {
            n->edges.push_back(grid[n->posY + 1][n->posX]);
        }
    }
    else if (n->val == '-')
    {
        if (n->posX > 0 && grid[n->posY][n->posX - 1]->val == '-')
        {
            n->edges.push_back(grid[n->posY][n->posX - 1]);
        }
        if (n->posX < grid[n->posY].size() - 1 && grid[n->posY][n->posX + 1]->val == '-')
        {
            n->edges.push_back(grid[n->posY][n->posX + 1]);
        }
    }
    else if (n->val == 'L')
    {
        if (n->posY > 0 && grid[n->posY - 1][n->posX]->val == 'L')
        {
            n->edges.push_back(grid[n->posY - 1][n->posX]);
        }
        if (n->posX < grid[n->posY].size() - 1 && grid[n->posY][n->posX + 1]->val == 'L')
        {
            n->edges.push_back(grid[n->posY][n->posX + 1]);
        }
    }
    else if (n->val == 'J')
    {
        if (n->posY > 0 && grid[n->posY - 1][n->posX]->val == 'J')
        {
            n->edges.push_back(grid[n->posY - 1][n->posX]);
        }
        if (n->posX > 0 && grid[n->posY][n->posX - 1]->val == 'J')
        {
            n->edges.push_back(grid[n->posY][n->posX - 1]);
        }
    }
}

void setEdgesForStartNode(Node *n, vector<vector<Node *>> &grid)
{
    // add potentially missing edges because of them being undirected, particulary for the start node
    if (n->posY > 0 && grid[n->posY - 1][n->posX]->val != '.')
    {
        n->edges.push_back(grid[n->posY - 1][n->posX]);
    }
    if (n->posY < grid.size() - 1 && grid[n->posY + 1][n->posX]->val != '.')
    {
        n->edges.push_back(grid[n->posY + 1][n->posX]);
    }
    if (n->posX > 0 && grid[n->posY][n->posX - 1]->val != '.')
    {
        n->edges.push_back(grid[n->posY][n->posX - 1]);
    }
    if (n->posX < grid[n->posY].size() - 1 && grid[n->posY][n->posX + 1]->val != '.')
    {
        n->edges.push_back(grid[n->posY][n->posX + 1]);
    }
}

void setEdgesForNodes(vector<Node *> nodes, vector<vector<Node *>> &grid)
{
    cout << "Skal sette kanter for alle noder..." << endl;
    for (auto &x : nodes)
    {
        cout << "Setter kanter for node med verdi " << x->val << " på (" << x->posX << ", " << x->posY << ")...";
        setEdgesForNode(x, grid);
        cout << " fikk " << x->edges.size() << " kanter" << endl;
    }
}

int main()
{
    string s;
    int posY = 0;
    vector<Node *> allNodes;
    vector<vector<Node *>> grid;
    Node *startNode;
    while (cin >> s && ++posY)
    {
        cout << s << endl;
        grid.push_back(vector<Node *>());
        for (int i = 0; i < s.size(); i++)
        {
            Node *n = new Node();
            n->val = s[i];
            n->posX = i;
            n->posY = posY - 1;
            grid.back().push_back(n);
            if (s[i] != '.')
            {
                allNodes.push_back(n);
                if (s[i] == 'S')
                {
                    cout << "found S" << endl;
                    startNode = n;
                }
            }
        }
    }
    cout << "allNodes.size() = " << allNodes.size() << endl;
    setEdgesForNodes(allNodes, grid);
    setEdgesForStartNode(startNode, grid);
    cout << "The start node has edges to " << startNode->edges.size() << " other nodes" << endl;
}