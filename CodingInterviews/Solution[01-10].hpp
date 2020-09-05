#include "Public.hpp"
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

/////////////////////////////////////////题目解答/////////////////////////////////////////

//*********************************剑指 Offer 03. 数组中重复的数字【哈希、排序、鸽巢】
/*
//描述：找出数组中重复的数字。
vector<int> nums = { 2, 3, 1, 0, 2, 5, 3 };
int ans = findRepeatNumber(nums);
cout << ans << endl;
//*/
//*//*/
int findRepeatNumber(vector<int>& nums) 
{
//* 
    //时间优先，时间O(n)，空间O（n）
    unordered_map<int, int> map;
    for (auto iter = nums.begin(); iter != nums.end(); ++iter)
    {
        map[*iter]++;
        if (map[*iter] > 1)
        {
            return *iter;
        }
    }
    return -1;
//*/

//* 
    //空间优先，时间O(nlogn)，空间O(1)
    sort(nums.begin(), nums.end());
    for (auto iter = nums.begin(); iter != nums.end(); ++iter)
    {
        iter++;
        if (*iter == *(--iter))
        {
            return *iter;
        }
    }
    return -1;
//*/

//* 
    //鸽巢原理，时间O(n)，空间O(1)[看作原地hash,下标为key,值为value]
    for (size_t i = 0; i < nums.size(); ++i)
    {
        while (nums[i] != i)
        {
            if (nums[nums[i]] == nums[i])
            {
                return nums[i];
            }
            int temp = nums[i];
            nums[i] = nums[temp];
            nums[temp] = temp;
        }
    }
    return -1;
//*/

}

//*********************************剑指 Offer 04. 二维数组中的查找【二叉搜索树】
/*
//描述：在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
        请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
vector<vector<int>> nums = {
    {1,   4,  7, 11, 15},
    {2,   5,  8, 12, 19},
    {3,   6,  9, 16, 22},
    {10, 13, 14, 17, 24},
    {18, 21, 23, 26, 30}
};
bool ans = findNumberIn2DArray(nums, 5);
cout << ans << endl;
//*/
//*//*/
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) 
{
    int row_size = matrix.size();
    if (row_size == 0)
    {
        return false;
    }
    int col_size = matrix[0].size();
    if (col_size == 0)
    {
        return false;
    }
/*
    // 思路有问题！！！！（我好蠢！！！）
    //[ [ 1, 3, 5, 7, 9],
    //  [ 2, 4, 6, 8,10],
    //  [11,13,15,17,19],
    //  [12,14,16,18,20],
    //  [21,22,23,24,25]]
    //13  直接hack
    if (target < matrix[0][0])
    {
        return false;
    }
    int j, k;
    j = 0;
    for (; j < col_size; j++)
    {
        if (target == matrix[0][j])
        {
            return true;
        }
        if (target < matrix[0][j])
        {
            break;
        }
    }
    k = 0;
    for (; k < row_size; k++)
    {
        if (target == matrix[k][j - 1])
        {
            return true;
        }
    }

    j = 0;
    for (; j < row_size; j++)
    {
        if (target == matrix[j][0])
        {
            return true;
        }
        if (target < matrix[j][0])
        {
            break;
        }
    }
    k = 0;
    for (; k < col_size; k++)
    {
        if (target == matrix[j - 1][k])
        {
            return true;
        }
    }

    return false;
//*/

//*
    // 我真的好蠢
    int row = 0;
    int col = col_size - 1;
    while (row < row_size && col >= 0)
    {
        if (matrix[row][col] == target)
        {
            return true;
        }
        if (matrix[row][col] > target)
        {
            --col;
        }
        else
        {
            ++row;
        }
    }
    return false;
//*/
}

//*********************************剑指 Offer 05. 替换空格【replace库函数】
/*
//描述：请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
string ans = replaceSpace("");
cout << ans << endl;
//*/
//*//*/
string replaceSpace(string s) 
{
/*
    //std的replace只能替换一个字符
    replace(s.begin(), s.end(), ' ', '%');
//*/  

//*
    //std::string的replace有11个重载
    string::size_type pos = 0;
    while ((pos = s.find(" ", pos)) != string::npos)
    {
        //从pos处将1个字符换为%20
        s.replace(pos, 1, "%20");
        pos += 3;
    }
//*/


    return s;
}


//*********************************【】
/*
//描述：
vector<int> nums = { 2, 3, 1, 0, 2, 5, 3 };
int ans = findRepeatNumber(nums);
cout << ans << endl;
//*/
//*//*/