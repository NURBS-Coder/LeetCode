// LeetCode.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int ans = threeSumClosest(h, 1);
	cout << ans << endl;

	getchar();
	return 0;
}

