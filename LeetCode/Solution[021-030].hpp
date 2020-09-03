#include "Public.hpp"
#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_set>
/////////////////////////////////////////题目解答/////////////////////////////////////////

//*********************************21. 合并两个有序链表【迭代、递归】
/*
//描述：将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的
ListNode head1(1, &ListNode(2, &ListNode(4)));
ListNode head2(1, &ListNode(3, &ListNode(4)));
ListNode* ans = mergeTwoLists(&head1, &head2);
cout << ans->val << endl;
//*/
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) 
{
//* //遍历比较添加,迭代
	ListNode* ans = new ListNode(0);
	ListNode* temp = ans;
	while (l1 != nullptr && l2 != nullptr)
	{
		if (l1->val < l2->val)
		{
			temp->next = l1;
			temp = temp->next;
			l1 = l1->next;
		}
		else
		{
			temp->next = l2;
			temp = temp->next;
			l2 = l2->next;
		}
	}

	temp->next = l1 == nullptr ? l2 : l1;

	//傻了。。。不该循环
	//while (l1 != nullptr)
	//{
	//	temp->next = l1;
	//	temp = temp->next;
	//	l1 = l1->next;
	//}

	//while (l2 != nullptr)
	//{
	//	temp->next = l2;
	//	temp = temp->next;
	//	l2 = l2->next;
	//}

	return ans->next;
//*/

/*	//递归
	if (l1 == nullptr)
	{
		return l2;
	}
	if (l2 == nullptr)
	{
		return l1;
	}

	if (l1->val < l2->val)
	{
		l1->next = mergeTwoLists(l1->next, l2);
		return l1;
	}
	else
	{
		l2->next = mergeTwoLists(l1, l2->next);
		return l2;
	}

//*/
}

//*********************************22. 括号生成【】
/*
//描述：数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
int n = 3;
vector<string> ans = generateParenthesis(n);
for (auto str : ans)
{
	cout << str << endl;
}
//*/
vector<string> generateParenthesis(int n) 
{
	vector<string> ans;
	
//*
	if (n == 1)
	{
		ans.push_back("()");
		return ans;
	}
	set<string> par;
	vector<string> temp = generateParenthesis(n - 1);
	for each (string var in temp)
	{
		par.insert("()" + var);
		size_t pos = 0;
		while ((pos = var.find('(', pos)) != string::npos)
		{
			string str = var;
			par.insert(str.insert(++pos, "()"));
		}
	}
	for each (string s in par)
	{
		ans.push_back(s);
	}
//*/

	return ans;
}

//*********************************23. 合并K个升序链表【顺序、并归、优先队列】
/*
//描述：给你一个链表数组，每个链表都已经按升序排列。请你将所有链表合并到一个升序链表中，返回合并后的链表。
	vector<ListNode*> lists;
	ListNode head1(1, &ListNode(4, &ListNode(5)));
	lists.push_back(&head1);
	ListNode head2(1, &ListNode(3, &ListNode(4)));
	lists.push_back(&head2);
	ListNode head3(2, &ListNode(6));
	lists.push_back(&head3);
	ListNode* ans = mergeKLists(lists);
	while (ans != nullptr)
	{
		cout << ans->val << endl;
		ans = ans->next;
	}
//*/
ListNode* mergeKLists(vector<ListNode*>& lists) 
{
	size_t size = lists.size();
	if (size == 0)
	{
		return nullptr;
	}
	if (size == 1)
	{
		return lists[0];
	}

	function< ListNode* (ListNode*, ListNode*)> mergeTwoLists = [&](ListNode* l1, ListNode* l2)
	{
		if (l1 == nullptr)
		{
			return l2;
		}
		if (l2 == nullptr)
		{
			return l1;
		}

		if (l1->val < l2->val)
		{
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else
		{
			l2->next = mergeTwoLists(l1, l2->next);
			return l2;
		}
	};

	ListNode* ans = new ListNode(0);
	ListNode* temp = ans;
/*	//顺序合并，时间复杂度高
	for (size_t i = 0; i < size; i++)
	{
		temp->next = mergeTwoLists(temp->next, lists[i]);
	}
//*/

/*	//分治，时间复杂度下降，空间复杂度上升
	function<ListNode* (vector <ListNode*>, int, int)> merge = [&](vector <ListNode*> lists, int l, int r)
	{
		if (l == r) return lists[l];
		if (l > r) return (ListNode*)nullptr;
		int mid = (l + r) >> 1;
		return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
	};

	ans->next = merge(lists, 0, size - 1);
//*/

//*	//优先队列，维护k个链表的首元素
	struct Status {
		int val;
		ListNode* ptr;
		bool operator < (const Status& rhs) const {
			return val > rhs.val;
		}
	};
	priority_queue <Status> q;
	for (auto node : lists) {
		//添加首元素到优先队列
		if (node) q.push({ node->val, node });
	}
	//循环清空队列
	while (!q.empty()) {
		auto f = q.top(); q.pop();
		temp->next = f.ptr;
		temp = temp->next;
		if (f.ptr->next) q.push({ f.ptr->next->val, f.ptr->next });
	}
//*/

	return ans->next;
}

//*********************************24. 两两交换链表中的节点【迭代、递归】
/*
//描述：给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。你不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
	ListNode head(1, &ListNode(2, &ListNode(3, &ListNode(4))));
	ListNode* ans = swapPairs(&head);
	while (ans != nullptr)
	{
		cout << ans->val << endl;
		ans = ans->next;
	}
//*/
ListNode* swapPairs(ListNode* head) 
{
	if (head == nullptr || head->next == nullptr)
	{
		return head;
	}

//*	//循环迭代，一次走两格，保存头节点
	ListNode* ans = new ListNode(0);
	ans->next = head;
	ListNode* pre = ans;
	ListNode* first = head;
	ListNode* second = head->next;

	while (second != nullptr)
	{
		first->next = second->next;
		second->next = first;
		pre->next = second;
		
		pre = pre->next->next;
		ListNode* temp = first;
		first = second->next != nullptr ? second->next->next : nullptr;
		second = temp->next != nullptr ? temp->next->next : nullptr;
	}
	return ans ->next;
//*/

/*	//递归
 	ListNode* first = head;
	ListNode* second = head->next;
	first->next = swapPairs(second->next);		//指向下一组
	second->next = first;						//指向first
	return second;
//*/
}

//*********************************25. K 个一组翻转链表【模拟】
/*
//描述：给你一个链表，每 k 个节点一组进行翻转，请你返回翻转后的链表。
		k 是一个正整数，它的值小于或等于链表的长度。
		如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
  说明：
		你的算法只能使用常数的额外空间。---->不能递归
		你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
	ListNode head(1, &ListNode(2, &ListNode(3, &ListNode(4, &ListNode(5)))));
	ListNode* ans = reverseKGroup(&head, 2);
	while (ans != nullptr)
	{
		cout << ans->val << endl;
		ans = ans->next;
	}
//*/
ListNode* reverseKGroup(ListNode* head, int k) 
{
	ListNode* ans = new ListNode(0);
	ans->next = head;
	ListNode* node = ans;
	vector<ListNode*> temp;		//储存一组要交换的节点
	while (head != nullptr)
	{
		temp.push_back(head);
		head = head->next;
		if (temp.size() == k)
		{
			for (auto iter = temp.rbegin(); iter != temp.rend(); ++iter)
			{
				node->next = *iter;
				node = *iter;
			}
			temp.clear();
		}
	}
	node->next = temp.size() != 0 ? temp[0] : nullptr;

	return ans->next;
}

//*********************************26. 删除排序数组中的重复项【双指针】
/*
//描述：给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
		不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
	vector<int> nums = { 0,0,1,1,1,2,2,3,3,4 };
	int ans = removeDuplicates(nums);
	cout << ans << endl;
//*/
int removeDuplicates(vector<int>& nums) 
{
/*
	//利用set去重
	set<int> s(nums.begin(), nums.end());
	return s.size();
//*/

/*
	// unique()函数将相邻且重复的元素放到vector的尾部,然后返回指向第一个重复元素的迭代器-->也就是非重复元素的尾迭代器
	// erase函数擦除从这个返回的元素到最后元素的所有的元素。
	// 先进行排序，这样重复元素就会堆一起了，调用unique()函数，再调用erase函数删除重复。
	nums.erase(unique(nums.begin(), nums.end()), nums.end());
	return nums.size();
//*/

//*
	//双指针
	size_t size = nums.size();
	if (size == 0 || size == 1)
	{
		return size;
	}

	int slow = 0;
	for (size_t i = 1; i < size; i++)
	{
		if (nums[slow] != nums[i])
		{
			++slow;
			nums[slow] = nums[i];
		}
	}
	return slow + 1;
//*/
}

//*********************************27. 移除元素【双指针】
/*
//描述：给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
		不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
		元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
	vector<int> nums = {0,1,2,2,3,0,4,2 };
	int ans = removeElement(nums, 2);
	cout << ans << endl;
//*/
int removeElement(vector<int>& nums, int val) 
{
	size_t size = nums.size();
	size_t i = 0;
/*
	//双指针(我写的)
	while (i < size)
	{
		int j = i + 1;
		if (nums[i] == val)
		{
			while (j < size && nums[j] == val)
			{
				++j;
			}
			
			for (size_t k = 0; k < size - j; k++)
			{
				nums[i + k] = nums[j + k];
			}
			size -= (j - i);
		}
		++i;
	}
	return size;
//*/

/*
	//双指针-->官方的
	for (int j = 0; j < size; j++) {
		if (nums[j] != val) {
			nums[i] = nums[j];
			i++;
		}
	}
	return i;
//*/

//*
	//双指针-->官方优化
	while (i < size) {
		if (nums[i] == val) {
			nums[i] = nums[size - 1];
			// reduce array size by one
			size--;
		}
		else {
			i++;
		}
	}
	return size;
//*/

}

//*********************************28. 实现 strStr()【不科学】
/*
//描述：实现 strStr() 函数。
		给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

//*/
//*//*/
int strStr(string haystack, string needle) 
{
	int size_h = haystack.size();
	int size_n = needle.size();
	if (size_n == 0)
	{
		return 0;
	}
	int ans = -1;

/* 
	//子串逐一比较
	for (int i = 0; i < size_h - size_n + 1; i++)
	{
		string str = haystack.substr(i, size_n);
		if (str == needle)
		{
			return i;
		}
	}
//*/

//*
	//双指针
	

//*/

	return ans;
}

//*********************************29. 两数相除【位移运算】
/*
//描述：给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
        返回被除数 dividend 除以除数 divisor 得到的商。
	int ans = divide(INT_MIN, -1);
	cout << ans << endl;
//*/
//*//*/

long long multiple(int num1, int num2)
{
	if (num1 == 0 || num2 == 0)
	{
		return 0;
	}

	bool sign = false;
	if (num1 < 0 && num2 < 0 ||
		num1 > 0 && num2 > 0)
	{   //记录结果符号
		sign = true;
	}
	long long first  = abs((long long)num1);
	long long second = abs((long long)num2);

	if (first < second)
	{   //操作小的num2，逐位判断
		long long temp = first;
		first = second;
		second = temp;
	}

	long long ans = 0;
	for (size_t i = 0; i < 32; i++)
	{	//从低位取值
		bool isOne = (second >> i) & 0x01;
		if (isOne)
		{
			ans += first << i;
		}
	}

	return sign ? ans : -ans;
}
int divide(int dividend, int divisor) 
{
	if (dividend == 0 || divisor == 1)
	{
		return dividend;
	}

	if (divisor == -1)
	{
		if (dividend == INT_MIN)
		{
			return INT_MAX;
		}
		else
		{
			return -dividend;
		}
	}

	bool sign = false;
	if (dividend < 0 && divisor < 0 ||
		dividend > 0 && divisor > 0)
	{   //记录结果符号
		sign = true;
	}

	long long first = abs((long long)dividend);
	long long second = abs((long long)divisor);

	if (first < second)
	{
		return 0;
	}

	long long bit_sum = 1;
	int first_bit_count = 0;
	while (bit_sum <= first)
	{   //获取dividend位数
		bit_sum <<= 1;
		++first_bit_count;
	}

	long long ans = 0;
	long long remainder = 0;
	while (first_bit_count--)
	{
		bit_sum >>= 1;
		remainder <<= 1;
		remainder |= (first >> first_bit_count) & 0x01;
		if (remainder >= second)
		{
			remainder -= second;
			ans |= bit_sum;
		}
	}
	
	return sign ? ans : -ans;
}

//*********************************30. 串联所有单词的子串【滑动窗口】
/*
//描述：给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。
		注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。
	vector<string> str = { "foo","bar" };
	vector<int> ans = findSubstring("barfoothefoobarman", str);
	for (auto i : ans)
	{
		cout << i << endl;
	}
//*/
//*//*/
vector<int> findSubstring(string s, vector<string>& words) 
{
	vector<int> ans;
//*
	if (s.empty() || words.empty())
	{
		return ans;
	}

	int s_size = s.size();
	int words_size = words.size();
	int one_size = words[0].size();
	int len = words_size * one_size;

	unordered_map<string, int> map1;
	for (const auto& element : words)
	{
		map1[element]++;
	}

	int i = 0;
	unordered_map<string, int> map2;
	while (i < one_size)
	{
		int first = i;
		int second = i;
		int count = 0;
		map2.clear();
		while (second + one_size <= s_size)
		{
			string strsub = s.substr(second, one_size);
			second += one_size;
			if (map1.count(strsub) == 0)
			{
				map2.clear();
				first = second;
				count = 0;
			}
			else
			{
				map2[strsub]++;
				count++;
				while (map2[strsub] > map1[strsub])
				{
					string tt = s.substr(i, one_size);
					--count;
					--map2[tt];
					first += one_size;
				}
			}

			if (count == words_size)
			{
				ans.push_back(i);
			}
		}
		++i;
	}

//*/
/*
	vector<int> res;
	if (!words.size()) return res;
	int n = s.size(), m = words.size(), w = words[0].size();
	unordered_map<string, int> hash;
	for (const auto& item : words) hash[item] ++;

	for (int i = 0; i <= w - 1; i++)
	{
		unordered_map<string, int> wd;
		int cnt = 0;
		for (int j = i; j + w <= n; j += w)
		{
			if (j >= m * w)
			{
				auto word = s.substr(j - m * w, w);
				wd[word] --;
				if (wd[word] < hash[word]) cnt--;
			}

			auto word = s.substr(j, w);
			wd[word] ++;
			if (wd[word] <= hash[word]) cnt++;

			if (cnt == m) res.push_back(j - (m - 1) * w);
		}
	}
//*/

	return ans;
}

//*********************************【】
/*
//描述：

//*/
//*//*/
