#include <algorithm>
#include <vector>
#include <set>
/////////////////////////////////////////��Ŀ���/////////////////////////////////////////

//*********************************11. ʢ���ˮ��������˫ָ�롿
/*
//���������� n ���Ǹ����� a1��a2��...��an��ÿ�������������е�һ���� (i, ai) ��
		�������ڻ� n ����ֱ�ߣ���ֱ�� i �������˵�ֱ�Ϊ (i, ai) �� (i, 0)��
		�ҳ����е������ߣ�ʹ�������� x �Ṳͬ���ɵ�����������������ˮ��
//˵�����㲻����б�������� n ��ֵ����Ϊ 2��
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
	//������������ --> ��Ȼ��ʱ
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
	//˫ָ��
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

//*********************************12. ����ת�������֡�̰�ġ�
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
		//�Ӵ�С��ÿ�ζ�ȡ�����������
		while (iter->first <= num)
		{
			ans += iter->second;
			num -= iter->first;
		}
	}

//*/

	return ans;
}

//*********************************13. ��������ת��������ϣ��
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

//*********************************14. �����ǰ׺��������ҡ�������ҡ���ֵ�����֡�
/*
//��������дһ�������������ַ��������е������ǰ׺��
		��������ڹ���ǰ׺�����ؿ��ַ��� ""��
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

//*********************************15. ����֮�͡�˫ָ�롿
/*
//����������һ������ n ������������ nums���ж� nums ���Ƿ��������Ԫ�� a��b��c ��ʹ�� a + b + c = 0 �������ҳ��������������Ҳ��ظ�����Ԫ�顣
  ע�⣺���в����԰����ظ�����Ԫ�顣
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
	
/*  //��ʱ
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

///*  //�Ż�ѭ����˫ָ�롿
	//i�ǵ�һ����a
	for (int i = 0; i < size; i++)
	{
		//ȥ�أ�a���ܺ�֮ǰ��һ��
		if (i > 0 && nums[i] == nums[i-1])
		{
			continue;	//����ѭ��
		}

		//k�ǵ�������c����������
		int k = size - 1;

		//j�ǵڶ�����b����������
		for (int j = i + 1; j < size; j++)
		{
			//ȥ�أ�b���ܺ�֮ǰ��һ��
			if (j > i + 1 && nums[j] == nums[j-1])
			{
				continue;	//����ѭ��
			}

			while (j < k && nums[i] + nums[j] + nums[k] > 0)
			{
				k--;		//nums������ģ���������j���ӣ�kӦ�ü�С���ҵ��ٽ��k
			}

			if (j == k)
			{
				break;		//ָ���غ϶�û�к��ʵ�,��һѭ��
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

//*********************************16. ��ӽ�������֮�͡���
/*
//����������һ������ n ������������ nums �� һ��Ŀ��ֵ target���ҳ� nums �е�����������ʹ�����ǵĺ��� target ��ӽ����������������ĺ͡��ٶ�ÿ������ֻ����Ψһ�𰸡�
int nums[6] = {-1, 0, 1, 2, -1, -4};
vector<int> h(nums, nums+6);
int ans = threeSumClosest(h, 1);
cout << ans << endl;
//*/
int threeSumClosest(vector<int>& nums, int target) 
{
	int ans = 0;
	sort(nums.begin(),nums.end());
	int size = nums.size();

///*  

//*/

	return ans;
}