// CodingInterviews.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Solution.hpp"

template <class Type>
ostream& operator << (ostream& os, const vector<Type>& c)
{
    for (auto iter = c.begin(); iter != c.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return os;
}

ostream& operator << (ostream& os, const ListNode* c)
{
    while (c != nullptr)
    {
        cout << c->val << endl;
        c = c->next;
    }
    return os;
}

int main()
{
    TreeNode* tree1 = new TreeNode(3, &TreeNode(4, &TreeNode(1), &TreeNode(2)), &TreeNode(5));
    TreeNode* tree2 = new TreeNode(4, &TreeNode(1));
    bool ans = isSubStructure(tree1, tree2);
    cout << ans << endl;
    
    return 0;
}
