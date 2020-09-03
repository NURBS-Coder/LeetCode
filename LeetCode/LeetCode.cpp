// LeetCode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Solution[001-010].hpp"
#include "Solution[011-020].hpp"
#include "Solution[021-030].hpp"

int _tmain(int argc, _TCHAR* argv[])
{
	//string s = "misssssisppi";
	//string p = "mis*is*p*i";
	//bool m = isMatch(s, p);
	//cout << m << endl;

	vector<string> str = { "fooo", "barr", "wing", "ding", "wing" };
	vector<int> ans = findSubstring("lingmindraboofooowingdingbarrwingmonkeypoundcake", str);
	for (auto i : ans)
	{
		cout << i << endl;
	}

	int ret = getchar();
	return 0;
}

