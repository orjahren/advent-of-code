#include <bits/stdc++.h>
using namespace std;
int main()
{
  int res = 0, a, b;
  vector<int> x, y;
  while (cin >> a >> b)
  {
    x.push_back(a);
    y.push_back(b);
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  for (int i = 0; i < x.size(); i++)
    res += abs(x[i] - y[i]);
  cout << res << endl;
}
