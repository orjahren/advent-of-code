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

int main()
{
    string inp;

    vector<vector<int>> nums;

    vector<pair<int, int>> dimensions;
    while (cin >> inp)
    {
        if (inp.find(":") != string::npos)
        {
            if (inp.find("x") != string::npos)
            {
                cout << inp << endl;
                nums.push_back(vector<int>());

                size_t pos = inp.find(":");
                string dimStr = inp.substr(0, pos);
                size_t xPos = dimStr.find("x");
                int dim1 = stoi(dimStr.substr(0, xPos));
                int dim2 = stoi(dimStr.substr(xPos + 1));
                dimensions.push_back(make_pair(dim1, dim2));
            }
            else
            {
                // Ignore the actual shapes or now. What could go wrong?
            }
        }
        else
        {
            if (!nums.empty())
            {
                nums.back().push_back(stoi(inp));
            }
        }
    }

    // print nums
    for (const auto &v : nums)
    {
        for (const auto &n : v)
        {
            cout << n << " ";
        }
        cout << endl;
    }

    ll p1 = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        const auto &v = nums[i];
        const auto &dim = dimensions[i];
        int dim1 = dim.first;
        int dim2 = dim.second;

        int accumulatedArea = 0;
        for (const auto &n : v)
        {
            accumulatedArea += (8 * n);
        }

        int area = dim1 * dim2;

        if (area >= accumulatedArea)
        {
            p1 += 1;
        }
    }
    cout << "Part 1: " << p1 << endl;

    return 0;
}
