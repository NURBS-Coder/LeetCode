#include "stdafx.h"
#ifndef _PUBLIC_HPP_
#define _PUBLIC_HPP_

struct ListNode {		//2¡¢19¡¢21
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};


#endif // !_PUBLIC_HPP_