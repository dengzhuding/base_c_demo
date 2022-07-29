/*
给定一个数组，求出奇数和偶数个数相同的最长连续子数组的长度
如：
[1,2,3,4,5,6,7] 最长子数组[1,2,3,4,5,6],[2,3,4,5,6,7]都是奇数偶数各3个
[1,1,2] 最长子数组[1,2]奇数偶数个一个
*/

#include<stdio.h>
#include<vector>
#include<map>
using namespace std;

int get_length(vector<int>& arr, int target)
{
  if (arr.size() == 0)
  {
    return 0;
  }

  map<int, bool> m_exist; // 记录从0开始的所有子数组的和
  map<int, int> m_pos; // 记录对应的子数组结尾位置

  int r = 0;
  int sum = 0; // sum(1,n) 从第一个位置(arr[0])开始累计的和

  m_exist[0] = true;
  m_pos[0] = -1; // 防止最终符合条件的子数组起始位置为0

  for (int i = 0; i < arr.size(); i++)
  {
    sum += arr[i];
    if (!m_exist[sum])
    {
      m_exist[sum] = true; // sum十多少无所谓，记录m_exist中存在这么一个值使得sum(1,i) - target 为true就行
      m_pos[sum] = i; // 当前sum(1, n)长度length
    }
    if (m_exist[sum - target]) { // 如果为true,说明以i为末尾的子数组中存在已经记录的子数组sum(1,m)
      r = max(r, i - m_pos[sum - target]); // m_pos[sum - target] - 存在的子数组长度(如果起始位置为0，则为-1，效果是i+1即为当前遍历的长度)
    }
  }
  return r;
}

int main(void)
{
  // 将问题转换为连续子数组和为0的连续数组长度
  vector<int> arr;
  arr.push_back(-1);
  arr.push_back(-1);
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(1);
  arr.push_back(-1);
  arr.push_back(-1);
  arr.push_back(-1);
  arr.push_back(1);
  int r;
  r = get_length(arr, 0);
  printf("r: %d\n", r);
}