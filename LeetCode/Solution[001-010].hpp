#include "Public.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <string> 
using namespace std;

/////////////////////////////////////////新知识点/////////////////////////////////////////
//********************************c++ map与unordered_map********************************//
/*{ 
	//内部实现了一个红黑树,有序，但空间占用率高
	map<int, string> myMap;	
	//内部实现了一个哈希表,无序，查找快，查找的时间复杂度可达到O(1)，但哈希表的建立比较耗费时间
	//unordered_map<int, string> myMap;		
	myMap[5] = "张大";
	myMap[6] = "李五";
    myMap[2] = "李四";  //使用[ ]进行单个插入，若已存在键值2，则赋值修改，若无则插入。
    myMap.insert(pair<int, string>(3, "陈二"));					//使用insert和pair插入
  
	//遍历输出+迭代器的使用
    auto iter = myMap.begin();//auto自动识别为迭代器类型unordered_map<int,string>::iterator
    while (iter!= myMap.end())
    {  
        cout << iter->first << "," << iter->second << endl;  
        ++iter;  
    }  
	
	//查找元素并输出+迭代器的使用
    auto iterator = myMap.find(2);//find()返回一个指向2的迭代器
    if (iterator != myMap.end())
	    cout << endl<< iterator->first << "," << iterator->second << endl; 

	
	//判断键存不存在：
	//1.iterator find ( const key_type& key );
	//如果key存在，则find返回key对应的迭代器，如果key不存在，则find返回unordered_map::end。因此可以通过
	//map.find(key) == map.end()，来判断，key是否存在于当前的unordered_map中。

	//2.Count函数：用以统计key值在unordered_map中出现的次数
	//size_type count ( const key_type& key ) const
	//实际上，c++ unordered_map不允许有重复的key。因此，如果key存在，则count返回1，如果不存在，则count返回0.
}//*/

/////////////////////////////////////////题目解答/////////////////////////////////////////

//*********************************1.两数之和【双指针、哈希表】
/*
//描述：给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。
int b[3] = {3 , 2, 4};
twoSum(vector<int>(b, b+3), 6);
//*/
vector<int> twoSum(vector<int>& nums, int target) 
{
	vector<int> ret;

	//暴力法
	//时间复杂度O（n²），空间复杂度O（1）
/*
	
	for (int i = nums.size() - 1 ; i > 0; i--)
    {	//nums.size()：少用，尽量减少调用次数，降低运算时间
        for (int j = i-1 ; j >= 0; j--)
        {
            if((nums[i] + nums[j]) == target)
            {
                ret.push_back(j);
                ret.push_back(i);
                return ret;
            }
        }
    }
//*/
	//双指针法，收尾指针向中靠拢，先排序，后查找
	//时间复杂度O（nlogn），空间复杂度O（n）
/*
    int len = nums.size();
    int i = 0;
    int j = len - 1;
    vector<int> temp;					//----->空间复杂度
    temp = nums;					
    sort(temp.begin(),temp.end());		//----->时
	间复杂度

    while (i < j)
    {
        if (temp[i] + temp[j] < target)
        {
            ++i; 
        }
        else if (temp[i] + temp[j] > target)
        {
            --j; 
        }
        else if (temp[i] + temp[j] == target)
        {
            break; 
        }
    }

    //查找对应值在原数组中的下标，且不应重复
        
    ret.resize(2,-1);
    for(int k=0; k < len; k++){
        if (nums.at(k) == temp[i] && ret[0] == -1)
        {
            ret[0] = k;
        }
        else if (nums.at(k) == temp[j] && ret[1] == -1)
        {
            ret[1] = k;
        }
        else if (ret[0] != -1 && ret[1] != -1)
        {
            break;
        }
    }
	//*/
	//两遍哈希表，遍历nums[i]时，看target-nums[i]是否存在hash表中
	//时间复杂度O（n），空间复杂度O（n）
/*
	unordered_map<int,int>hashmap;
	//第一遍赋值
    for(int i=0;i<nums.size();i++)
	{
		hashmap[nums[i]] = i;
    }
	//第二遍判断
	for(int i=0;i<nums.size();i++)
	{
		if (hashmap.count(target - nums[i]) && hashmap[target - nums[i]] != i)
		{
			ret.push_back(i);
            ret.push_back(hashmap[target-nums[i]]);
			break;
		}
    }
	//*/
	//一遍哈希表，遍历nums[i]时，看target-nums[i]是否存在hash表中
	//时间复杂度O（n），空间复杂度O（n）
///*
	unordered_map<int,int>hashmap;
    for(size_t i=0;i<nums.size();i++)
	{
		//查看target-nums[i]在表中的值<nums中nums[i]的下标>
		//不为零<target-nums[i]存在于表中，也就是曾经有一个nums[i]等于target-nums[i]>
		//不为i+1<不是同一个元素>
        if(hashmap[target-nums[i]] && hashmap[target-nums[i]]!=i+1)
		{
			//防止利用同个元素
            ret.push_back(i);
            ret.push_back(hashmap[target-nums[i]]-1);
            break;
        }
		//将当前元素<键>和其下标+1<值>，保存在表中,map默认赋值为0；
		//将hash表对应下标＋1，防止处理下标为0的情况<区别默认赋值，用于后来判断>
		hashmap[nums[i]]=i+1;
    }
	//*/
	for (auto r : ret)
	{
		cout << r << endl;
	}
    return ret;
}

//*********************************2.两数相加
/*
//描述：给出两个非空的链表用来表示两个非负的整数。
//其中，它们各自的位数是按照逆序的方式存储的，并且它们的每个节点只能存储一位数字。
//如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
//您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
//输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
//输出：7 -> 0 -> 8
//原因：342 + 465 = 807
ListNode a1(9);
ListNode a2(1),b2(9),c2(9);
a2.next = &b2;
b2.next = &c2;
addTwoNumbers(&a1, &a2); 
//*/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
	ListNode *ret = new ListNode(0);
	//用int等数据类型，会有最大值限制，int不能超过11位.....
/*
	int n = 0, m = 0;
	int lenA = 1, lenB = 1;
	ListNode *a = l1, *b = l2;

	while (NULL != a->next)
	{
		n += a->val * pow(10, lenA-1);
		++lenA;
		a = a->next;
	}
	n += a->val * pow(10, lenA-1);

	while (NULL != b->next)
	{
		m += b->val * pow(10, lenB-1);
		++lenB;
		b = b->next;
	}
	m += b->val * pow(10, lenB-1);

	int r = n + m;
	ret->val = r%10;
	r = r/10;
	ListNode *pre = ret;
	ListNode *cur = ret;
	while (r > 0)
	{
		cur = new ListNode(r%10);
		r = r/10;
		pre->next = cur;
		pre = cur;
	}
//*/
	//改进
/*
	int n = 0;
	int d = 0,e = 0,f = 0;
	ListNode *a = l1, *b = l2;
	n = a->val + b->val;
	ret->val=n%10;
	if (n >= 10)
	{
		f = 1;
	}
	else
	{
		f = 0;
	}
	ListNode *pre = ret;
	ListNode *cur = ret;
	while (NULL != a->next || NULL != b->next)
	{
		if (NULL != a->next)
		{
			a = a->next;
			d = a->val;
		}
		else
		{
			d = 0;
		}

		if ( NULL != b->next)
		{
			b = b->next;
			e = b->val;
		}
		else
		{
			e = 0;
		}

		n = d + e + f;
		cur = new ListNode(n%10);
		if (n >= 10)
		{
			f = 1;
		}
		else
		{
			f = 0;
		}

		pre->next = cur;
		pre = cur;
	}
	if (f == 1)
	{
		cur = new ListNode(f);
		pre->next = cur;
	}
//*/
	//优化
	//时间复杂度：O(max⁡(m,n))，假设m和n分别表示l1和l2的长度，上面的算法最多重复max⁡(m,n)次。
	//空间复杂度：O(max⁡(m,n))，新列表的长度最多为max⁡(m,n)+1。
	int n = 0,d = 0,e = 0,carry = 0;
	ListNode *a = l1, *b = l2;
	//使用哑结点来简化代码。如果没有哑结点，则必须编写额外的条件语句来初始化表头的值。
	ListNode *cur = ret;	
	while (NULL != a || NULL != b)
	{
		//简化判断
		d = (NULL != a) ? a->val : 0;
		e = (NULL != b) ? b->val : 0;
		n = d + e + carry;
		cur->next = new ListNode(n%10);
		carry = (n >=10) ? 1 : 0;
		cur = cur->next;
		if (NULL != a)
		{
			a = a->next;
		}
		if (NULL != b)
		{
			b = b->next;
		}
	}
	if (carry == 1)
	{
		cur->next = new ListNode(carry);
	}
	return ret->next;
}

//*********************************3.无重复字符的最长子串【滑动窗口、散列表（unordered_set哈希集合）】
/*
//描述：给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
string a = "bbbbbbabbcbcbbbb";
lengthOfLongestSubstring(a); 
//*/
int lengthOfLongestSubstring(string s) 
{
	int ans = 0;
///*
	//没做出来，unordered_map，不好搞啊！！--->看完解析再来一遍<升级解析>
	unordered_map<char,int> occ;

	int cur = 0;
	int start = 0;					//用来储存左“指针”，不要一步一步移，直接移动到重复字符上一次出现的位置
	int n = s.size();
	for (int i = 0; i < n; i++)		//i相当于右“指针”，一直往字符串尾部移动
	{
		cur = occ.count(s[i]) ? occ[s[i]] : -1;
		if (start <= cur)			//当前字符位置在start的右边或不在hashmap中就跳过
		{
			ans = (ans > i - start) ? ans : i - start;
			start = cur + 1;		//直接从重复字符的下一个字符开始
		}
		occ[s[i]] = i;	//hashmap中没有s[i],将其加入，并存入下标
	}
	ans = (ans > n - start) ? ans : n - start;
	//*/
/*
	//分析：--出现次数--->散列表<构造字串，存下标>
	//		--子串问题--->滑动窗口
	//需要使用一种数据结构来判断 是否有重复的字符，常用的数据结构为哈希集合
	//c++ 中的 std::unordered_set 
	// 哈希集合，记录每个字符是否出现过
    unordered_set<char> occ;
    int n = s.size();
    // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
    int rk = -1;
    // 枚举左指针的位置，初始值隐性地表示为 -1
    for (int i = 0; i < n; ++i) {
        if (i != 0) {
            // 左指针向右移动一格，移除一个字符
            occ.erase(s[i - 1]);
        }
        while (rk + 1 < n && !occ.count(s[rk + 1])) {  //这个判断使得，右指针只能在左指针把重复值erase后才能继续移动
            // 不断地移动右指针
            occ.insert(s[rk + 1]);
            ++rk;
        }
        // 第 i 到 rk 个字符是一个极长的无重复字符子串
        ans = max(ans, rk - i + 1);
    }
	//*/
	cout << ans << endl;
	return ans;
}

//*********************************4.寻找两个正序数组的中位数【二分查找】
/*
//描述：给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。
//请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。
//你可以假设 nums1 和 nums2 不会同时为空。
int a[2] = {2,3};
vector<int> nums1; 
int b[3] = {2,3,4};
vector<int> nums2(b,b+3);
findMedianSortedArrays(nums1, nums2); 
//*/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
{
    double ans = 0;
///*
	int len = nums1.size() + nums2.size();
	int t1 = (len + 1)/2;
	int t2 = (len + 2)/2;
	cout << t1 << "<---->" << t2 << endl;
	int num1 = 0;
	int num2 = 0;
	int nMax = 0;
	int nCount = 0;
	auto iter1 = nums1.begin();
	auto iter2 = nums2.begin();
	num1 = (iter1 != nums1.end()) ? nums1[0] : nums2[nums2.size()-1] + 1;
	num2 = (iter2 != nums2.end()) ? nums2[0] : nums1[nums1.size()-1] + 1;
	if (iter1 != nums1.end() && iter2 != nums2.end())
	{
		nMax = max(nums2[nums2.size()-1],nums1[nums1.size()-1]) + 1;
	}
	else
	{
		nMax = max(num1, num2);
	}
	
	while (iter1 != nums1.end() || iter2 != nums2.end())
	{
		if (num1 < num2)
		{
			++iter1;
			++nCount;
			cout << nCount << "<1>:" << num1 << endl;

			if (nCount == t1 || nCount == t2)
			{
				ans += (t1 != t2) ? num1 : 2*num1;
			}

			num1 = (iter1 != nums1.end()) ? *iter1 : nMax;
		}
		else
		{
			++iter2;
			++nCount;
			cout << nCount << "<2>:" << num2 << endl;

			if (nCount == t1 || nCount == t2)
			{
				ans += (t1 != t2) ? num2 : 2*num2;
			}

			num2 = (iter2 != nums2.end()) ? *iter2 : nMax;
		}
	}
 
	ans /= 2;
	//*/
	cout << ans << endl;
    return ans;
}

//*********************************5.最长回文子串【动态规划Dynamic Programming，DP】
/*
//描述：给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
string s = "zudfweormatjycujjirzjpyrmaxurectxrtqedmmgergwdvjmjtstdhcihacqnothgttgqfywcpgnuvwglvfiuxteopoyizgehkwuvvkqxbnufkcbodlhdmbqyghkojrgokpwdhtdrwmvdegwycecrgjvuexlguayzcammupgeskrvpthrmwqaqsdcgycdupykppiyhwzwcplivjnnvwhqkkxildtyjltklcokcrgqnnwzzeuqioyahqpuskkpbxhvzvqyhlegmoviogzwuiqahiouhnecjwysmtarjjdjqdrkljawzasriouuiqkcwwqsxifbndjmyprdozhwaoibpqrthpcjphgsfbeqrqqoqiqqdicvybzxhklehzzapbvcyleljawowluqgxxwlrymzojshlwkmzwpixgfjljkmwdtjeabgyrpbqyyykmoaqdambpkyyvukalbrzoyoufjqeftniddsfqnilxlplselqatdgjziphvrbokofvuerpsvqmzakbyzxtxvyanvjpfyvyiivqusfrsufjanmfibgrkwtiuoykiavpbqeyfsuteuxxjiyxvlvgmehycdvxdorpepmsinvmyzeqeiikajopqedyopirmhymozernxzaueljjrhcsofwyddkpnvcvzixdjknikyhzmstvbducjcoyoeoaqruuewclzqqqxzpgykrkygxnmlsrjudoaejxkipkgmcoqtxhelvsizgdwdyjwuumazxfstoaxeqqxoqezakdqjwpkrbldpcbbxexquqrznavcrprnydufsidakvrpuzgfisdxreldbqfizngtrilnbqboxwmwienlkmmiuifrvytukcqcpeqdwwucymgvyrektsnfijdcdoawbcwkkjkqwzffnuqituihjaklvthulmcjrhqcyzvekzqlxgddjoir";
string str = longestPalindrome(s);
cout << str.size()<< ":" << str << endl;
//*/
bool IsPalindrome(string text)
{
	int len = text.size();
	int nCount = len/2;
	int n = -1;
	while (++n < nCount)
	{
		if (text[n] != text[len-n-1])
		{
			return false;
		}
	}
	return true;
}
string longestPalindrome(string s) 
{
	string ans = "";
	int len = s.size();
	int start = 0;		//最长子串首地址
	int nMax = 0;		//最长子串长
/*
	//尝试：暴力法--->尴尬，超出时间限制
	string sub;
	for (int i = 0; i < len; i++)					//左指针
	{
		for (int j = nMax; j < len - i + 1; j++)	//右指针
		{
			sub = s.substr(i,j);
			if (IsPalindrome(sub) && nMax < sub.size())
			{
				nMax = sub.size();
				ans = sub;
			}
			cout << sub.size()<< ":" << sub << endl;
		}
	}
////////////////////////////////////////////////////////////////*/

/*
	//不取所有字串，以每个字符为中心向外扩展
	for (int i = 0; i < len; i++)
	{
		int jLen = min(i,len - i - 1);
#ifdef _DEBUG
		string sub;
		//以i为中心的最长子串<奇数串>
		sub = s.substr(i - jLen,2*jLen + 1);
		cout << sub.size()<< "<2>:" << sub << endl;
#endif
		for (int j = 0; j <= jLen; j++)
		{
#ifdef _DEBUG
			//以i为中心的2*j+1长的子串<奇数串>
			sub = s.substr(i - j,2*j + 1);
			cout << sub.size()<< ":" << sub << endl;
			cout << s[i - j]<< ":" << s[i + j] << endl;
#endif
			if (s[i - j] == s[i + j])
			{
				if (nMax < 2*j + 1)
				{
					nMax = 2*j+1;
					ans = s.substr(i - j,2*j + 1);
				}
			}
			else
			{
				break;
			}
		}
	}

	//查找偶数串
	for (int i = 0; i < len; i++)
	{
		int jLen = min(i,len - i - 1);
#ifdef _DEBUG
		string sub;
		//以i为中心的最长子串<偶数串>
		sub = s.substr(i - jLen,2*jLen + 2);
		cout << sub.size()<< "<1>:" << sub << endl;
#endif
		for (int j = 0; j <= jLen; j++)
		{
#ifdef _DEBUG
			//以i为中心的2*j+2长的子串<偶数串>
			sub = s.substr(i - j,2*j + 2);
			cout << sub.size()<< ":" << sub << endl;
			cout << s[i - j]<< ":" << s[i + j + 1] << endl;
#endif	
			if (s[i - j] == s[i + j + 1])
			{
				if ( nMax < 2*j + 2)
				{
					nMax = 2*j+2;
					ans = s.substr(i - j,2*j + 2);
				}
			}
			else
			{
				break;
			}
		}
	}
	
//*/
	
	//dp[i][j] 表示strsub{i--j}是不是回文
	vector<vector<bool>> dp(len, vector<bool>(len));
	for (int i = len - 1; i >= 0; i--)
	{
		for (int j = i; j < len; j++)
		{
			if (i == j)
			{
				dp[i][j] = true;
			}
			else if (j - i == 1)
			{
				dp[i][j] = (s[i] == s[j]);
			}
			else 
			{
				dp[i][j] = (s[i] == s[j] && dp[i+1][j-1]);
			}
			
			if (dp[i][j] && j - i + 1 > nMax)
			{
				nMax = j - i + 1;
				start = i;
			}
		}
	}
	ans = s.substr(start, nMax);

	return ans;
}

//*********************************6.Z 字形变换
/*
//描述：将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。之后，你的输出需要从左往右逐行读取，产生出一个新的字符串
string s = "LEETCODEISHIRING";
int numRows = 3;
convert(s, numRows);
//*/
string convert(string s, int numRows) 
{
	if (numRows == 1)
	{
		return s;
	}

	string ans;
	int len = s.length();
	int m = 2*numRows - 2;
	int k = (len % m) ? len/m + 1 : len/m;
	int r = 0,l = 0;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < 2*k; j++)
		{
			if (j%2 == 1 && (i == 0 || i == numRows-1))
			{
				continue;
			}
			l = j/2;
			if (j%2 == 0)
			{
				r = l * m + i;
			}
			else
			{
				r = l * m + m - i;
			}
			if (r > len - 1)
			{
				continue;
			}
			ans.push_back(s[r]);
		}
	}

	cout << ans << endl;
	return ans;
}

//*********************************7. 整数反转
/*
//描述：给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
int n = 456;
int m = reverse(n);
cout << m << endl;
//*/
int reverse(int x) 
{
	int recv = 0;
	string Max1 = "2147483647";
	string Max2 = "-2147483648";
/*
	//字符分析
	stringstream s;
	s << x;
	string str;
	s >> str;
	s.clear();
	int n = str.length();

	vector<char> temp;
	for (int i = 0; i < n; i++)
	{
		temp.push_back(str[i]);
	}

	int k = 0;
	for (int i = n - 1; i >= 0;  --i)
	{
		char a = temp[i];
		if (a == '0' )
		{
			++k;
		}
		else
		{
			break;
		}
	}

	string ans;
	if (temp[0] == '-')
	{
		ans+=temp[0];
		for (int i = n - k - 1; i > 0;  --i)
		{
			ans+=temp[i];
		}
	}
	else
	{
		for (int i = n - k - 1; i >= 0;  --i)
		{
			ans+=temp[i];
		}
	}

	n = ans.length();
	if (temp[0] != '-') 
	{
		if (n > 10)
		{
			return 0;
		}

		if(n == 10  && strcmp(ans.c_str(), Max1.c_str()) > 0)
		{
			return 0;
		};
	}
	else
	{
		if (n > 11)
		{
			return 0;
		}

		if(n == 11  && strcmp(ans.c_str(), Max2.c_str()) > 0)
		{
			return 0;
		};
	}
	s << ans;
	s >> recv; 
//*/

///*
	//不用库
	int pop = 0;
	int temp = 0;

	while (x != 0)
	{
		pop = x%10;

		//其实int输入值，在recv == INT_MAX/10时第一位只能是2和1，不会大于7或者小于-8
		//可以省略第二个判断
		if (recv > INT_MAX/10 || (recv == INT_MAX/10 && pop > 7))
		{
			return 0;
		}

		
		if (recv < INT_MIN/10 || (recv == INT_MIN/10 && pop < -8))
		{
			return 0;
		}

		recv =   recv * 10 + pop;
		x /=10;
	}


//*/
	return recv;
}

//*********************************8. 字符串转换整数 (atoi)【确定有限状态机（deterministic finite automaton, DFA）】
/*
//描述：请你来实现一个 atoi 函数，使其能将字符串转换成整数。
string str = "  -123";
int m = myAtoi(str);
cout << m << endl;
//*/
//状态机
class Automaton {  
public:
	Automaton()
	{
		sign = 1;
		ans = 0;
		state = "start";
		char a[][10] = {"start","signed", "in_number", "end"};
		table["start"] = vector<string>(a, a+4);
		char b[][10] = {"end", "end", "in_number", "end"};
		table["signed"] = vector<string>(b, b+4);
		char c[][10] = {"end", "end", "in_number", "end"};
		table["in_number"] = vector<string>(c, c+4);
		char d[][10] = {"end", "end", "end", "end"};
		table["end"] = vector<string>(d, d+4);
	}

    int get_col(char c) //通过字符判断下一状态
	{
        if (isspace(c)) return 0;
        if (c == '+' || c == '-') return 1;
        if (isdigit(c)) return 2;
        return 3;
    }

	void get(char c)	//通过状态进行不同操作
	{
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }

public:
    int sign;		//正负号标识
    long long ans;	//当前转换的值
	string state;	//当前状态机状态
	unordered_map<string, vector<string>> table;	//状态转换表
};
int myAtoi(string str) 
{
/*
	//臃肿复杂的代码
	int k = 1;
	int ans = 0;
	int pop = 0;
	char temp;
	auto iter = str.begin();
	while (iter != str.end())
	{
		temp = *iter;
		if (temp != ' ')
		{
			break;
		}
		++iter;
	}

	if (iter == str.end() )
	{
		return 0;
	}

	if (temp == '+' || temp == '-')
	{
		++iter;
		if (iter != str.end())
		{
			if ('0' <= *(iter) || *(iter) <= '9')
			{
				k = temp == '+' ? 1 : -1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else if ('0' > temp || temp > '9')
	{
		return 0;
	}

	while (iter != str.end())
	{
		temp = *iter;
		if ('0' > temp || temp > '9')
		{
			break;
		}

		pop = k * (temp - '0');

		if (ans > INT_MAX/10 || (ans == INT_MAX/10 && pop > 7))
		{
			return INT_MAX ;
		}
		if (ans < INT_MIN/10 || (ans == INT_MIN/10 && pop < -8))
		{
			return INT_MIN ;
		}

		ans = ans *10  + pop;
		++iter;
	}
	return ans;
//*/

//*
	//确定有限状态机（deterministic finite automaton, DFA）
//				' ' 	+/- 	number 		other
//	start 		start 	signed 	in_number 	end
//	signed 		end 	end 	in_number 	end
//	in_number 	end 	end 	in_number 	end
//	end 		end 	end 	end 		end
	Automaton automaton;
    for (char c : str)
	{
         automaton.get(c);
	}
    return automaton.sign * automaton.ans;
//*/
}

//*********************************9. 回文数
/*
//描述：判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
int n = -123;
bool m = isPalindrome(n);
cout << m << endl;
//*/
bool strIsPalindrome(string str)
{
	int len = str.length();
	if (len < 2)
	{
		return true;
	}
	if (len == 2)
	{
		if (str[0] == str[1])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (str[0] == str[len - 1])
		{
			return strIsPalindrome(str.substr(1,len - 2));
		}
		else
		{
			return false;
		}
	}
}
bool isPalindrome(int x) 
{
/*
	//转换字符串，太影响性能
	stringstream strstr;
	strstr << x;
	return strIsPalindrome(strstr.str());
//*/

/*
	//性能越改越烂。。。。。用了vector
	//不用vector 为什么时间和内存少了这么多！！！
	if (x < 0)
	{
		return false;
	}

	//vector<char> nums;
	int len = 0;
	char nums[11];
	while (x != 0)
	{
		//nums.push_back(x%10);
		nums[len] = ('0' + x%10);
		len++;
		x /= 10;
	}

	int i = 0;
	//int j = nums.size() - 1;
	int j = len - 1;
	while (i <= j)
	{
		if (nums[i] == nums[j])
		{
			++i;
			--j;
		}
		else
		{
			return false;
		}
	}
	return true;
//*/

//*
	//折半比较-->巧妙-->效率还不如上面，为啥？
	if (x < 0 || (x!=0 && x%10 == 0))
	{
		return false;
	}
	int reversal = 0;
	while (x > reversal)
	{
		reversal = reversal * 10 + x % 10;
		x /= 10;
	}
	return x == reversal || x == reversal/10;
//*/
}

//*********************************10. 正则表达式匹配【DP】
/*
//描述：给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配
string s = "mississippi";
string p = "mis*is*p*.";
bool m = isMatch(s, p);
cout << m << endl;
//*/

bool isMatch(string s, string p)
{
	int m = s.size();
	int n = p.size();
	if (m == 0 || n == 0)
	{
		return false;
	}

	auto matches = [&](int i, int j) -> bool
	{
		if (i == 0)
		{
			return false;
		}
		if (p[j - 1] == '.')
		{
			return true;
		}
		return p[i - 1] == p[j - 1];
	};

	//f(i,j)表示s的前i个和p的前j个是否匹配

	vector<vector<int>> f(m + 1, vector<int>(n + 1));
	f[0][0] = true;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (p[j - 1] == '*')
			{
				f[i][j] |= f[i][j - 2];
				if (matches(i, j - 1))
				{
					f[i][j] |= f[i - 1][j];
				}
			}
			else
			{
				if (matches(i, j))
				{
					f[i][j] |= f[i - 1][j - 1];
				}
			}
		}
	}

	return f[m][n];
}