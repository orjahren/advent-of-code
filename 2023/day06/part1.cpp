#include <bits/stdc++.h>
using namespace std;
int main()
{
    cout << "Hello World!" << endl;
    vector<int> times(3);
    vector<int> distances(3);
    string devNull;
    cin >> devNull;
    for (int i = 0; i < 3; i++)
        cin >> times[i];
    cin >> devNull;
    for (int i = 0; i < 3; i++)
        cin >> distances[i];
    cout << "Times: ";
    for (int i = 0; i < 3; i++)
        cout << times[i] << " ";
    cout << endl;
    cout << "Distances: ";
    for (int i = 0; i < 3; i++)
        cout << distances[i] << " ";
    cout << endl;
    return 0;
}