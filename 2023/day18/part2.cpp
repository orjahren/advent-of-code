#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char getDirFromHex(string arg)
{
    char c = arg[arg.size() - 2];
    char arr[] = {'R', 'D', 'L', 'U'};
    for (int i = 0; i < 4; i++)
    {
        if (c == i + '0')
        {
            return arr[i];
        }
    }
    return -1;
}
ll convHexToDec(string arg)
{
    string hexVal = arg.substr(2, arg.size() - 4);
    cout << "hexVal = " << hexVal << endl;
    stringstream stream;
    stream << hexVal;
    ll y;
    stream >> hex >> y;
    return y;
}

int main()
{
    char dir;
    int val;
    string hash;
    vector<pair<int, int>> borderPoints;
    int currX = 0, currY = 0;
    while (cin >> dir >> val >> hash)
    {
        cout << hash << endl;
        char properDir = getDirFromHex(hash);
        ll num = convHexToDec(hash);
        cout << "num = " << num << endl;
        for (ll i = 0; i < num; i++)
        {
            switch (properDir)
            {
            case 'U':
                currY--;
                break;
            case 'D':
                currY++;
                break;
            case 'R':
                currX++;
                break;
            case 'L':
                currX--;
            }
            borderPoints.push_back(make_pair(currX, currY));
        }
    }
    cout << "borderPoints.size() = " << borderPoints.size() << endl;

    // find all points inside the border
    cout << "Finding border points...";
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
    for (auto point : borderPoints)
    {
        minX = min(minX, point.first);
        maxX = max(maxX, point.first);
        minY = min(minY, point.second);
        maxY = max(maxY, point.second);
    }
    cout << "...done" << endl;
    cout << "Creating hullMatrix...";
    cout.flush();
    char **hullMatrix = new char *[maxX - minX + 1];
    for (int i = 0; i < maxX - minX + 1; i++)
        hullMatrix[i] = new char[maxY - minY + 1];

    cout << "...done" << endl;
    cout << "Tagging items...";
    cout.flush();
    for (int i = 0; i < maxX - minX + 1; i++)
        for (int j = 0; j < maxY - minY + 1; j++)
            hullMatrix[i][j] = '.';
    cout << "...done" << endl;
    cout << "Marking borders...";
    for (auto point : borderPoints)
        hullMatrix[point.first - minX][point.second - minY] = '#';
    cout << "...done" << endl;

    queue<pair<int, int>> q;

    // For test-input:
    q.push(make_pair(1, 1));

    // For prod-input:
    // q.push(make_pair(6, 21));
    cout << "Starting flood fill...";

    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        int x = curr.first;
        int y = curr.second;
        if (x < 0 || x >= maxX - minX + 1 || y < 0 || y >= maxY - minY + 1 || hullMatrix[x][y] == '#')
            continue;
        hullMatrix[x][y] = '#';
        q.push(make_pair(x + 1, y));
        q.push(make_pair(x - 1, y));
        q.push(make_pair(x, y + 1));
        q.push(make_pair(x, y - 1));
    }
    cout << "...done" << endl;

    int part2 = 0;
    for (int i = 0; i < maxX - minX + 1; i++)
    {
        for (int j = 0; j < maxY - minY + 1; j++)
        {
            char c = hullMatrix[i][j];
            part2 += (c == '#');
        }
    }
    cout << "Part 2: " << part2 << endl;
}