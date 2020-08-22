#include "Public.hpp"
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <stack>
/////////////////////////////////////////题目解答/////////////////////////////////////////

//*********************************11. 盛最多水的容器【双指针】
/*
//描述：给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
		在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。
		找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
//说明：你不能倾斜容器，且 n 的值至少为 2。
int a[9] = {1,8,6,2,5,4,8,3,7};
vector<int> h(a, a + 9);
int n = maxArea(h);
cout << n << endl;
//*/
int maxArea(vector<int>& height) 
{
	int ans = 0;
	int len = height.size();
	if (len < 2)
	{
		return 0;
	}
/*
	//暴力滑动窗口 --> 果然超时
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			int area = min(height[i], height[j]) * (j - i);
			ans = (area > ans ) ? area :ans;
		}
	}
//*/ 

///*
	//双指针
	int i = 0;
	int j = len - 1;
	int temp = 0;
	while (i <= j)
	{
		temp = min(height[i], height[j]) * (j - i);
		ans = max(ans, temp);
		if (height[i] < height[j])
		{
			++i;
		}
		else
		{
			--j;
		}
	}
	
//*/ 
	return ans;
}

//*********************************12. 整数转罗马数字【贪心】
/*
int a = 3;
string str = intToRoman(a);
cout << str << endl;
//*/
string intToRoman(int num)
{
	string ans;
/*
	int len = 0;
	while (num > 0)
	{
		int n = num % 10;
		len++;

		string temp;
		if (n >= 1 && n < 4)
		{
			switch (len)
			{
			case 1:
				temp = "I";
				break;
			case 2:
				temp = "X";
				break;
			case 3:
				temp = "C";
				break;
			case 4:
				temp = "M";
				break;
			default:
				break;
			}
			for (int i = 1; i < n; i++)
			{
				switch (len)
				{
				case 1:
					temp = temp + "I";
					break;
				case 2:
					temp = temp + "X";
					break;
				case 3:
					temp = temp + "C";
					break;
				case 4:
					temp = temp + "M";
					break;
				default:
					break;
				}
			}
		}
		if (n == 4)
		{
			switch (len)
			{
			case 1:
				temp = "IV";
				break;
			case 2:
				temp = "XL";
				break;
			case 3:
				temp = "CD";
				break;
				break;
			default:
				break;
			}
		}
		if (n >= 5 && n < 9)
		{
			switch (len)
			{
			case 1:
				temp = "V";
				break;
			case 2:
				temp = "L";
				break;
			case 3:
				temp = "D";
				break;
			default:
				break;
			}
			
			if (n < 9)
			{
				for (int i = 5; i < n; i++)
				{
					switch (len)
					{
					case 1:
						temp = temp + "I";
						break;
					case 2:
						temp = temp + "X";
						break;
					case 3:
						temp = temp + "C";
						break;
					case 4:
						temp = temp + "M";
						break;
					default:
						break;
					}
				}
			}
		}
		if (n == 9)
		{
			switch (len)
			{
			case 1:
				temp = "IX";
				break;
			case 2:
				temp = "XC";
				break;
			case 3:
				temp = "CM";
				break;
			default:
				break;
			}
		}
		ans = temp + ans;
		num = num/10;
	}
//*/

//*
	map<int,string> R;
	R[1] = "I";
	R[4] = "IV";
	R[5] = "V";
	R[9] = "IX";
	R[10] = "X";
	R[40] = "XL";
	R[50] = "L";
	R[90] = "XC";
	R[100] = "C";
	R[400] = "CD";
	R[500] = "D";
	R[900] = "CM";
	R[1000] = "M";

	for (auto iter = R.rbegin(); iter != R.rend(); ++iter)
	{
		//从大到小，每次都取能满足的最大的
		while (iter->first <= num)
		{
			ans += iter->second;
			num -= iter->first;
		}
	}

//*/

	return ans;
}

//*********************************13. 罗马数字转整数【哈希表】
/*
string str = "MCMXCIV";
int n = romanToInt(str);
cout << n << endl;
//*/
int romanToInt(string s) 
{
	int ans = 0;

	unordered_map<char,int> a;
	a['I'] = 1;
	a['V'] = 5;
	a['X'] = 10;
	a['L'] = 50;
	a['C'] = 100;
	a['D'] = 500;
	a['M'] = 1000;

	auto iter = s.begin();
	while(iter != s.end())
	{
		if (a[*iter] >= a[*(iter+1)] )
		{
			ans += a[*iter];
			iter++;
		}
		else
		{
			ans -= a[*iter];
			iter++;
		}
	}

	
	return ans;
}

//*********************************14. 最长公共前缀【横向查找、纵向查找、分值、二分】
/*
//描述：编写一个函数来查找字符串数组中的最长公共前缀。
		如果不存在公共前缀，返回空字符串 ""。
vector<string> h;
h.push_back("flower");
h.push_back("flow");
h.push_back("flight");
string str = longestCommonPrefix(h);
cout << str << endl;
//*/
string longestCommonPrefix(vector<string>& strs) 
{
	string ans;
	int n = strs.size();
	if (n == 0){return ans;}
	vector<int> sizes;
	for (int i = 0; i < n; i++)
	{
		sizes.push_back(strs[i].size());
	}
	int Min = *min_element(sizes.begin(), sizes.end());

	for (int i = 0; i < Min; i++)
	{
		char c = strs[0][i];
		for (int j = 1; j < n; j++)
		{
			if (strs[j][i] != c)
			{
				return ans;
			}
		}
		ans += c;
	}
	return ans;
}

//*********************************15. 三数之和【排序 + 双指针】
/*
//描述：给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
  注意：答案中不可以包含重复的三元组。
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
//*/
vector<vector<int>> threeSum(vector<int>& nums) 
{
	vector<vector<int>> ans;
	sort(nums.begin(),nums.end());
	int size = nums.size();
	
/*  //超时
	set<vector<int>> a;
	for (int i = 0; i < size - 2; i++)
	{
		for (int j = i + 1; j < size - 1; j++)
		{
			for (int k = j + 1; k < size; k++)
			{
				if (nums[i] + nums[j] + nums[k] == 0)
				{
					vector<int> temp;
					temp.push_back(nums[i]);
					temp.push_back(nums[j]);
					temp.push_back(nums[k]);
					a.insert(temp);
				}
			}
		}
	}

	for (auto aa : a)
	{
		ans.push_back(aa);
	}
//*/

///*  //优化循环【双指针】
	//i是第一个数a
	for (int i = 0; i < size; i++)
	{
		//去重，a不能和之前的一样
		if (i > 0 && nums[i] == nums[i-1])
		{
			continue;	//减少循环
		}

		//k是第三个数c，从右往左
		int k = size - 1;

		//j是第二个数b，从左往右
		for (int j = i + 1; j < size; j++)
		{
			//去重，b不能和之前的一样
			if (j > i + 1 && nums[j] == nums[j-1])
			{
				continue;	//减少循环
			}

			while (j < k && nums[i] + nums[j] + nums[k] > 0)
			{
				k--;		//nums是有序的，所以随着j增加，k应该减小，找到临界的k
			}

			if (j == k)
			{
				break;		//指针重合都没有合适的,下一循环
			}

			if (nums[i] + nums[j] + nums[k] == 0)
			{
				vector<int> temp;
				temp.push_back(nums[i]);
				temp.push_back(nums[j]);
				temp.push_back(nums[k]);
				ans.push_back(temp);
			}
		}
	}
//*/
	return ans;
}

//*********************************16. 最接近的三数之和【排序 + 双指针】
/*
//描述：给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
int nums[6] = {-1, 0, 1, 2, -1, -4};
vector<int> h(nums, nums+6);
int ans = threeSumClosest(h, 1);
cout << ans << endl;
//*/
int threeSumClosest(vector<int>& nums, int target) 
{
	int ans = 1000;
	sort(nums.begin(),nums.end());
	int size = nums.size();

/*  
	//i是第一个数a
	for (int i = 0; i < size; i++)
	{
		//去重，a不能和之前的一样
		if (i > 0 && nums[i] == nums[i-1])
		{
			continue;	//减少循环
		}

		//k是第三个数c，从右往左
		int k = size - 1;

		//j是第二个数b，从左往右
		for (int j = i + 1; j < size; j++)
		{
			//去重，b不能和之前的一样
			if (j > i + 1 && nums[j] == nums[j-1])
			{
				continue;	//减少循环
			}

			while (j < k && nums[i] + nums[j] + nums[k] > target)
			{
				k--;		//nums是有序的，所以随着j增加，k应该减小，找到临界的k
			}

			int temp = 0;

			if (k != size - 1)
			{
				//cout << nums[i] << nums[j] << nums[k + 1] << endl;
				temp = nums[i] + nums[j] + nums[k + 1];
				ans = (abs(temp - target) < abs(ans - target)) ? temp : ans;
			}

			if (j != k)
			{
				//cout << nums[i] << nums[j] << nums[k] << endl;
				temp = nums[i] + nums[j] + nums[k];
				ans = (abs(temp - target) < abs(ans - target)) ? temp : ans;
			}
		}
	}
//*/

//*
	for (int i = 0; i < size; i++)
	{
		//去重，a不能和之前的一样
		if (i > 0 && nums[i] == nums[i-1])
		{
			continue;	//减少循环
		}

		int j = i + 1;
		int k = size - 1;
		while (j < k)
		{
			int temp = nums[i] + nums[j] + nums[k];

			if (temp == target)
			{
				return target;
			}

			ans = (abs(temp - target) < abs(ans - target)) ? temp : ans;

			if (temp > target)
			{
				int k0 = k - 1;
				while (j < k0 && nums[k0] == nums[k])
				{
					--k0;
				}
				k = k0;
			}
			else
			{
				int j0 = j + 1;
				while (j0 < k && nums[j0] == nums[j])
				{
					--j0;
				}
				j = j0;
			}
		}
	}
//*/

	return ans;
}

//*********************************17. 电话号码的字母组合【递归、回溯】
/*
//描述：给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
		给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
string a = "23";
vector<string> ans = letterCombinations(a);
for (auto i : ans)
{
	cout << i << endl;
}
//*/
vector<string> letterCombinations(string digits) 
{
	vector<string> ans;
	int size = digits.size();
	if (size == 0)
	{
		return ans;
	}
	//输入数字字符转换为对应的字母字符
	vector<vector<char>> temp;
	for (int i = 0; i < size; i++)
	{
		int n = digits[i] - '0';
		vector<char> t;
		if (n < 8)
		{
			t.push_back('a' + (n-2) * 3 );
			t.push_back('a' + (n-2) * 3 + 1);
			t.push_back('a' + (n-2) * 3 + 2);
			if (n == 7)
			{
				t.push_back('a' + (n-2) * 3 + 3);
			}
		}
		else
		{
			t.push_back('a' + (n-2) * 3 + 1);
			t.push_back('a' + (n-2) * 3 + 2);
			t.push_back('a' + (n-2) * 3 + 3);
			if (n == 9)
			{
				t.push_back('a' + (n-2) * 3 + 4);
			}
		}
		temp.push_back(t);
	}

/*
	for (int i = 0; i < size; i++)
	{
		int len = temp[i].size();
		if (i == 0)
		{
			for (int j = 0; j < len; j++)
			{
				string st;
				st.push_back(temp[i][j]);
				ans.push_back(st);
			}
		}
		else
		{
			string st;
			vector<string> tt;
			for (int k = ans.size() - 1; k >= 0 ; --k)
			{
				st = ans[k];
				ans[k] += temp[i][0];
				for (int j = 1; j < len; j++)
				{
					tt.push_back(st + temp[i][j]);
				}
			} 
			for (auto t : tt)
			{
				ans.push_back(t);
			}
		}
	}
//*/

//* //循环深度不定，和字符串长有关，用递归
	function<void(string str, int Depth)> backtrack = [&](string str, int Depth)
	{
		if (Depth == size)
		{
			//到达深度就直接返回
			ans.push_back(str);
			return;
		}
		int n = temp[Depth].size();
		for (int i = 0; i < n; i++)
		{ 
			//递归调用
			backtrack(str + temp[Depth][i], Depth + 1);
		}
	};

	backtrack("", 0);
//*/

    return ans;
}

//*********************************18. 四数之和【排序 + 双指针】
/*
//描述：给定一个包含 n 个整数的数组 nums 和一个目标值 target
  判断 nums 中是否存在四个元素 a，b，c 和 d 
  使得 a + b + c + d 的值与 target 相等？
  找出所有满足条件且不重复的四元组。
int nums[6] = {1, 0, -1, 0, -2, 2};
vector<int> h(nums, nums+6);
vector<vector<int>> ans = fourSum(h, 0);
for (int i = 0; i < ans.size(); i++)
{
	for (int j = 0; j < ans[i].size(); j++)
	{
		cout << ans[i][j] << "\t";
	}
	cout << endl;
}
//*/

vector<vector<int>> fourSum(vector<int>& nums, int target) 
{
    vector<vector<int>> ans;
	size_t size = nums.size();
	if (size < 4)
	{
		return ans;
	}
	sort(nums.begin(), nums.end());
//* //仿照三数之和【排序 + 双指针】
	for (size_t i = 0; i < size; i++)
	{
		if (i > 0 && nums[i] == nums[i-1])
		{
			continue;
		}
		for (size_t j = i + 1; j < size; j++)
		{
			if (j > i + 1 && nums[j] == nums[j - 1])
			{
				continue;
			}
			for (size_t k = j + 1; k < size; k++)
			{
				if (k > j + 1 && nums[k] == nums[k - 1])
				{
					continue;
				}
				size_t l = size - 1;
				while (k < l && nums[i] + nums[j] + nums[k] + nums[l] > target)
				{
					--l;
				}
				if (k == l)
				{
					break;
				}
				if (nums[i] + nums[j] + nums[k] + nums[l] == target)
				{
					vector<int> t = {nums[i], nums[j], nums[k], nums[l]};
					ans.push_back(t);
				}
			}
		}
	}
//*/
	return ans;
}

//*********************************19. 删除链表的倒数第N个节点【链表遍历】
/*
//描述：给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
int n = 2;
ListNode head(1);
head.next = &ListNode(2);
head.next->next = &ListNode(3);
head.next->next->next = &ListNode(4);
head.next->next->next->next = &ListNode(5);
ListNode* ans = removeNthFromEnd(&head, 2);
cout << ans->val << endl;
//*/

ListNode* removeNthFromEnd(ListNode* head, int n) 
{
	size_t size = 0;
	ListNode* ans = new ListNode(0);
	ans->next = head;

/*/ 两趟扫描，哑节点
	ListNode* temp = ans;
	while (temp->next != NULL)
	{
		++size;
		temp = temp->next;
	}
	int len = size - n;
	if (len < 0) 
	{
		return NULL;
	}

	ListNode *cur = ans;
	ListNode *pre = ans;
	while (len >= 0)
	{
		pre = cur;
		cur = cur->next;
		--len;
	}
	pre->next = cur->next;
//*/

//* 一趟扫描
	ListNode* first = ans;
	ListNode* second = ans;
	for (size_t i = 0; i < n; i++)
	{
		first = first->next;
	}
	while (first->next != NULL)
	{
		first = first->next;
		second = second->next;
	}
	if (second->next != NULL)
	{
		second->next = second->next->next;
	}
//*/
	return ans->next;
}

//*********************************20. 有效的括号【栈】
/*
//描述：给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
  有效字符串需满足：
  左括号必须用相同类型的右括号闭合。
  左括号必须以正确的顺序闭合。
  注意空字符串可被认为是有效字符串。
string str = "([)]";
bool ans = isValid(str);
cout << ans << endl;
//*/
bool isValid(string s) 
{
	size_t size = s.size();
	stack<char> st;
	for (size_t i = 0; i < size; i++)
	{
		if (s[i] == '(' || s[i] == '[' || s[i] == '{')
		{
			st.push(s[i]);
		}
		if (s[i] == ')')
		{
			if (st.size() == 0)
			{
				return false;
			}
			if (st.top() != '(')
			{
				return false;
			}
			else
			{
				st.pop();
			}
		}
		if (s[i] == ']')
		{
			if (st.size() == 0)
			{
				return false;
			}
			if (st.top() != '[')
			{
				return false;
			}
			else
			{
				st.pop();
			}
		}
		if (s[i] == '}')
		{
			if (st.size() == 0)
			{
				return false;
			}
			if (st.top() != '{')
			{
				return false;
			}
			else
			{
				st.pop();
			}
		}
	}
	if (st.size() != 0)
	{
		return false;
	}
	return true;
}