#include <algorithm>
#include <vector>

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

//*********************************12. 整数转罗马数字【】
/*
int a = 3;
string str = intToRoman(a);
cout << str << endl;
//*/
string intToRoman(int num)
{
	string ans;
//*
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

	return ans;
}

//*********************************13. 罗马数字转整数【】
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

//*********************************14. 最长公共前缀【】
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

//*********************************15. 三数之和【】
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


	return ans;
}