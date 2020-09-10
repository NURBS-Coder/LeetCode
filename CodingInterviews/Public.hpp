#ifndef _PUBLIC_HPP_
#define _PUBLIC_HPP_

#include <algorithm>
#include <vector>
#include <stack>
#include <functional>
#include <unordered_map>
#include <queue>

struct ListNode { //06
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode { //07
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

#endif // !_PUBLIC_HPP_