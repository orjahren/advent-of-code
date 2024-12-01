#include <bits/stdc++.h>
using namespace std;
int getFreqCount(vector<int> &list, int val)
{
  int leftIdx = lower_bound(list.begin(), list.end(), val) - list.begin();
  int rightIdx = upper_bound(list.begin(), list.end(), val) - list.begin();
  return rightIdx - leftIdx;
}
int part2(vector<int> &leftList, vector<int> &rightList)
{
  int res = 0;
  for (int i = 0; i < leftList.size(); i++)
  {
    int freqCount = getFreqCount(rightList, leftList[i]);
    res += leftList[i] * freqCount;
  }

  return res;
}

int main()
{
  int part1 = 0, a, b;
  vector<int> leftList, rightList;
  while (cin >> a >> b)
  {
    leftList.push_back(a);
    rightList.push_back(b);
  }
  sort(leftList.begin(), leftList.end());
  sort(rightList.begin(), rightList.end());
  for (int i = 0; i < leftList.size(); i++)
    part1 += abs(leftList[i] - rightList[i]);
  cout << "Part 1: " << part1 << endl;
  cout << "Part 2: " << part2(leftList, rightList) << endl;
}
