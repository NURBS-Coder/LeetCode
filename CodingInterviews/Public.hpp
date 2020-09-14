#ifndef _PUBLIC_HPP_
#define _PUBLIC_HPP_

#include <algorithm>
#include <vector>
#include <stack>
#include <functional>
#include <unordered_map>
#include <queue>
#include <string>

struct ListNode { //06¡¢18¡¢22
	int val;
	ListNode* next;
	ListNode(int x, ListNode* nex = nullptr) : val(x), next(nex) {}
};

struct TreeNode { //07¡¢26
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x, TreeNode* lef = nullptr, TreeNode* righ = nullptr) : val(x), left(lef), right(righ) {}
};

#endif // !_PUBLIC_HPP_