#include "Public.hpp"
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

/////////////////////////////////////////��Ŀ���/////////////////////////////////////////

//*********************************��ָ Offer 03. �������ظ������֡���ϣ�����򡢸볲��
/*
//�������ҳ��������ظ������֡�
vector<int> nums = { 2, 3, 1, 0, 2, 5, 3 };
int ans = findRepeatNumber(nums);
cout << ans << endl;
//*/
//*//*/
int findRepeatNumber(vector<int>& nums) 
{
//* 
    //ʱ�����ȣ�ʱ��O(n)���ռ�O��n��
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
    //�ռ����ȣ�ʱ��O(nlogn)���ռ�O(1)
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
    //�볲ԭ��ʱ��O(n)���ռ�O(1)[����ԭ��hash,�±�Ϊkey,ֵΪvalue]
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

//*********************************��ָ Offer 04. ��ά�����еĲ��ҡ�������������
/*
//��������һ�� n * m �Ķ�ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳������
        �����һ������������������һ����ά�����һ���������ж��������Ƿ��и�������
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
    // ˼·�����⣡���������Һô���������
    //[ [ 1, 3, 5, 7, 9],
    //  [ 2, 4, 6, 8,10],
    //  [11,13,15,17,19],
    //  [12,14,16,18,20],
    //  [21,22,23,24,25]]
    //13  ֱ��hack
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
    // ����ĺô�
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

//*********************************��ָ Offer 05. �滻�ո�replace�⺯����
/*
//��������ʵ��һ�����������ַ��� s �е�ÿ���ո��滻��"%20"��
string ans = replaceSpace("");
cout << ans << endl;
//*/
//*//*/
string replaceSpace(string s) 
{
/*
    //std��replaceֻ���滻һ���ַ�
    replace(s.begin(), s.end(), ' ', '%');
//*/  

//*
    //std::string��replace��11������
    string::size_type pos = 0;
    while ((pos = s.find(" ", pos)) != string::npos)
    {
        //��pos����1���ַ���Ϊ%20
        s.replace(pos, 1, "%20");
        pos += 3;
    }
//*/


    return s;
}


//*********************************����
/*
//������
vector<int> nums = { 2, 3, 1, 0, 2, 5, 3 };
int ans = findRepeatNumber(nums);
cout << ans << endl;
//*/
//*//*/