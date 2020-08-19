// LeetCode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Solution[001-010].hpp"
#include "Solution[011-020].hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	//string s = "misssssisppi";
	//string p = "mis*is*p*i";
	//bool m = isMatch(s, p);
	//cout << m << endl;

	int nums[6] = {-1, 0, 1, 2, -1, -4};
	vector<int> h(nums, nums+6);
	vector<vector<int>> ans = threeSum(h);
	for (int i = 0; i < ans.size(); i++)
	{
		for (int j = 0; j < ans[i].size(); j++)
		{
			cout << ans[i][j] << "\t";
		}
		cout << endl;
	}
	getchar();
	return 0;
}

