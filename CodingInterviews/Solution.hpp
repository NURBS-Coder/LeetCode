#include "Public.hpp"
using namespace std;
/////////////////////////////////////////题目解答/////////////////////////////////////////

//*********************************剑指 Offer 03. 数组中重复的数字【哈希、排序、鸽巢】
/*
//描述：找出数组中重复的数字。
vector<int> nums = { 2, 3, 1, 0, 2, 5, 3 };
int ans = findRepeatNumber(nums);
cout << ans << endl;
//*/
//*//*/
int findRepeatNumber(vector<int>& nums) 
{
//* 
    //时间优先，时间O(n)，空间O（n）
    unordered_map<int, int> map;
    for (auto iter = nums.begin(); iter != nums.end(); ++iter)
    {
        map[*iter]++;
        if (map[*iter] > 1)
        {
            return *iter;
        }
    }
    return -1;
//*/

//* 
    //空间优先，时间O(nlogn)，空间O(1)
    sort(nums.begin(), nums.end());
    for (auto iter = nums.begin(); iter != nums.end(); ++iter)
    {
        iter++;
        if (*iter == *(--iter))
        {
            return *iter;
        }
    }
    return -1;
//*/

//* 
    //鸽巢原理，时间O(n)，空间O(1)[看作原地hash,下标为key,值为value]
    for (size_t i = 0; i < nums.size(); ++i)
    {
        while (nums[i] != i)
        {
            if (nums[nums[i]] == nums[i])
            {
                return nums[i];
            }
            int temp = nums[i];
            nums[i] = nums[temp];
            nums[temp] = temp;
        }
    }
    return -1;
//*/

}

//*********************************剑指 Offer 04. 二维数组中的查找【二叉搜索树】
/*
//描述：在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
        请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
vector<vector<int>> nums = {
    {1,   4,  7, 11, 15},
    {2,   5,  8, 12, 19},
    {3,   6,  9, 16, 22},
    {10, 13, 14, 17, 24},
    {18, 21, 23, 26, 30}
};
bool ans = findNumberIn2DArray(nums, 5);
cout << ans << endl;
//*/
//*//*/
bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) 
{
    int row_size = matrix.size();
    if (row_size == 0)
    {
        return false;
    }
    int col_size = matrix[0].size();
    if (col_size == 0)
    {
        return false;
    }
/*
    // 思路有问题！！！！（我好蠢！！！）
    //[ [ 1, 3, 5, 7, 9],
    //  [ 2, 4, 6, 8,10],
    //  [11,13,15,17,19],
    //  [12,14,16,18,20],
    //  [21,22,23,24,25]]
    //13  直接hack
    if (target < matrix[0][0])
    {
        return false;
    }
    int j, k;
    j = 0;
    for (; j < col_size; j++)
    {
        if (target == matrix[0][j])
        {
            return true;
        }
        if (target < matrix[0][j])
        {
            break;
        }
    }
    k = 0;
    for (; k < row_size; k++)
    {
        if (target == matrix[k][j - 1])
        {
            return true;
        }
    }

    j = 0;
    for (; j < row_size; j++)
    {
        if (target == matrix[j][0])
        {
            return true;
        }
        if (target < matrix[j][0])
        {
            break;
        }
    }
    k = 0;
    for (; k < col_size; k++)
    {
        if (target == matrix[j - 1][k])
        {
            return true;
        }
    }

    return false;
//*/

//*
    // 我真的好蠢
    int row = 0;
    int col = col_size - 1;
    while (row < row_size && col >= 0)
    {
        if (matrix[row][col] == target)
        {
            return true;
        }
        if (matrix[row][col] > target)
        {
            --col;
        }
        else
        {
            ++row;
        }
    }
    return false;
//*/
}

//*********************************剑指 Offer 05. 替换空格【replace库函数】
/*
//描述：请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
string ans = replaceSpace("");
cout << ans << endl;
//*/
//*//*/
string replaceSpace(string s) 
{
/*
    //std的replace只能替换一个字符
    replace(s.begin(), s.end(), ' ', '%');
//*/  

//*
    //std::string的replace有11个重载
    string::size_type pos = 0;
    while ((pos = s.find(" ", pos)) != string::npos)
    {
        //从pos处将1个字符换为%20
        s.replace(pos, 1, "%20");
        pos += 3;
    }
//*/


    return s;
}

//*********************************剑指 Offer 06. 从尾到头打印链表【递归、辅助栈】
/*
//描述：输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）

vector<int> ans = reversePrint(nums);
cout << ans << endl;
//*/
//*//*/
vector<int> reversePrint(ListNode* head) 
{
//*
    //递归
    vector<int> ans;
    function<void(ListNode*)> recursion = [&](ListNode* head)
    {
        if (head == NULL)
        {
            return;
        }
        recursion(head->next);
        ans.push_back(head->val);
    };
    recursion(head);
    return ans;
//*/

/*
    //辅助栈
    stack<int> stk;
    while (head != NULL)
    {
        stk.push(head->val);
        head = head->next;
    }

    vector<int> ans;
    while (stk.size() != 0)
    {
        ans.push_back(stk.top());
        stk.pop();
    }
    return ans;
//*/
}

//*********************************剑指 Offer 07. 重建二叉树【递归、迭代】
/*
//描述：输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。
        假设输入的前序遍历和中序遍历的结果中都不含重复的数字
vector<int> pre = { 3,9,20,15,7 };
vector<int> in = { 9,3,15,20,7 };
TreeNode* ans = buildTree(pre, in);
cout << ans << endl;
//*/
//*//*/
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
{
    int size = preorder.size();
    if (size == 0)
    {
        return NULL;
    }
/*
    //递归
    //时间复杂度：O(n)。对于每个节点都有创建过程以及根据左右子树重建过程。
    //空间复杂度：O(n)。存储整棵树的开销。
    TreeNode* root = new TreeNode(preorder[0]);

    int pre_count = 0;
    for (auto iter = inorder.begin(); iter != inorder.end(); ++iter)
    {
        if (*iter == root->val)
        {
            break;
        }
        ++pre_count;
    }
    //左子树
    vector<int> pre_left(preorder.begin() + 1, preorder.begin() + pre_count + 1);
    vector<int> in_left(inorder.begin(), inorder.begin() + pre_count);
    root->left = buildTree(pre_left, in_left);

    //右子树
    vector<int> pre_right(preorder.begin() + pre_count + 1, preorder.end());
    vector<int> in_right(inorder.begin() + pre_count + 1, inorder.end());
    root->right = buildTree(pre_right, in_right);

    return root;
//*/

//*
    //迭代--(没懂)
    //时间复杂度：O(n)。前序遍历和后序遍历都被遍历。
    //空间复杂度：O(n)。额外使用栈存储已经遍历过的节点。
    TreeNode *root = new TreeNode(preorder[0]);
    int length = preorder.size();
    stack<TreeNode*> stack;
    stack.push(root);
    int inorderIndex = 0;
    for (int i = 1; i < length; i++) {
        int preorderVal = preorder[i];
        TreeNode* node = stack.top();
        if (node->val != inorder[inorderIndex]) {
            node->left = new TreeNode(preorderVal);
            stack.push(node->left);
        }
        else {
            while (!stack.empty() && stack.top()->val == inorder[inorderIndex]) {
                node = stack.top();
                stack.pop();
                inorderIndex++;
            }
            node->right = new TreeNode(preorderVal);
            stack.push(node->right);
        }
    }
    return root;

//*/
}

//*********************************剑指 Offer 09. 用两个栈实现队列【栈】
/*
//描述：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数：
        appendTail，完成在队列尾部插入整数的功能。
        deleteHead，完成在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
CQueue* obj = new CQueue();
obj->appendTail(5);
int ans = obj->deleteHead();
cout << ans << endl;
//*/
//*//*/
class CQueue {
public:
    stack<int> a, b;
    CQueue() {

    }

    void appendTail(int value) {
        a.push(value);
    }

    int deleteHead() {
        if (b.empty())
        {
            while (a.size() != 0)
            {
                b.push(a.top());
                a.pop();
            }
        }
        if (b.empty())
        {
            return -1;
        }

        int ret = b.top();
        b.pop();
        return ret;
    }
};

//*********************************剑指 Offer 10- I. 斐波那契数列【动态规划】
/*
//描述：写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。
int ans = fib(nums);
cout << ans << endl;
//*/
//*//*/
int fib(int n) 
{
    if (n == 0 || n == 1)
    {
        return n;
    }
/*
    //单纯递归-->超时 --> 大量重复计算
    //记忆化递归法-->存储需要使用 O(N)O(N) 的额外空间
    return fib(n - 1) + fib(n - 2);
//*/

//*
    //我这个是动态规划？？？哈哈哈哈哈
    int a = 0;
    int b = 1;
    int c = 1;
    for(int i = 2; i <= n; ++i)
    {
        c = (a + b) % 1000000007;
        a = b;
        b = c;
        //cout << i << ":" << c << endl;
    }
    return c;
//*/

}

//*********************************剑指 Offer 10 - II.青蛙跳台阶问题【动态规划】
/*
//描述：一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
int ans = numWays(nums);
cout << ans << endl;
//*/
//*//*/
int numWays(int n) 
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    int n_2 = 1;
    int n_1 = 1;
    int now = 0;
    for (int i = 2; i <= n; ++i)
    {
        now = (n_1 + n_2) % 1000000007;
        n_2 = n_1;
        n_1 = now;
    }
    return now;
}

//*********************************剑指 Offer 11. 旋转数组的最小数字【二分查找】
/*
//描述：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
        输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
        例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

vector<int> nums = {3,4,5,1,2};
int ans = minArray(nums);
cout << ans << endl;
//*/
//*//*/
int minArray(vector<int>& numbers)
{
    if (numbers.size() == 0)
    {
        return 0;
    }
    //*
        //直接遍历，查找慢
    for (auto iter = numbers.begin() + 1; iter != numbers.end(); ++iter)
    {
        if (*iter < *(iter - 1))
        {
            return *iter;
        }
    }
    return numbers.front();
    //*/

    /*
        //二分查找
        //考虑数组中的最后一个元素 x：
        //在最小值右侧的元素，它们的值一定都小于等于 x。
        //在最小值左侧的元素，它们的值一定都大于等于 x。
        int low = 0;
        int high = numbers.size() - 1;
        while (low < high)
        {
            int pivot = low + (high - low) / 2;
            if (numbers[pivot] < numbers[high])
            {
                high = pivot;
            }
            else if (numbers[pivot] > numbers[high])
            {
                low = pivot + 1;
            }
            else
            {
                --high;
            }
        }
        return numbers[low];
    //*/
}

//*********************************剑指 Offer 12. 矩阵中的路径【DFS + 剪枝】
/*
//描述：请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
vector<vector<char>> nums = {
    {'a','b','c','e'},
    {'s','f','c','s'},
    {'a','d','e','e'}
};
bool ans = exist(nums, "");
cout << ans << endl;
//*/
//*//*/
bool exist(vector<vector<char>>& board, string word) 
{
    int row_size = board.size();
    int col_size = board[0].size();
    int str_size = word.size();
    function<bool(int, int, int)> dfs = [&](int i, int j, int k) -> bool
    {
        if (i >= row_size || i < 0 ||
            j >= col_size || j < 0 ||
            board[i][j] != word[k] 
            )
        {
            //剪枝：在搜索中，遇到 这条路不可能和目标字符串匹配成功 的情况
            //例如：此矩阵元素和目标字符不同、此元素已被访问、超出范围
            //则应立即返回，称之为 可行性剪枝 。
            return false;
        }
        if (k == str_size - 1)
        {
            return true;
        }
        char temp = board[i][j];
        board[i][j] = '/';
        //深度优先搜索： 可以理解为暴力法遍历矩阵中所有字符串可能性。
        //DFS 通过递归，先朝一个方向搜到底，再回溯至上个节点，沿另一个方向搜索，以此类推。
        bool ret = dfs(i, j + 1, k + 1) || dfs(i, j - 1, k + 1) || 
                   dfs(i + 1, j, k + 1) || dfs(i - 1, j, k + 1);
        board[i][j] = temp;
        return ret;
    };

    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < col_size; j++)
        {
            if (dfs(i, j, 0))
            {
                return true;
            }
        }
    }
    return false;
}

//*********************************剑指 Offer 13. 机器人的运动范围【DFS、BFS + 剪枝】
/*
//描述：
int ans = movingCount(2, 3, 1);
cout << ans << endl;
//*/
//*//*/
int movingCount(int m, int n, int k) {

    int ans = 0;
    vector<vector<char>> flag(m, vector<char>(n, '0'));

    auto getsum = [](int i, int j) -> int
    {
        int sum = 0;
        while (i > 0)
        {
            sum += i % 10;
            i /= 10;
        }
        while (j > 0)
        {
            sum += j % 10;
            j /= 10;
        }
        return sum;
    };

/*
    // DFS（递归，栈，回溯） + 剪枝
    function<void(int, int, int&)> dfs = [&](int i, int j, int &a)
    {
        if (i >= m || i < 0 || j >= n || j < 0 || flag[i][j] == 'i' || getsum(i,j) > k)
        {
            return;
        }
        a++;
        flag[i][j] = 'i';
        dfs(i + 1, j, a);
        dfs(i, j + 1, a);
    };
    dfs(0, 0, ans);
    return ans;
//*/
//*
    // BFS（循环，队列，重放） + 剪枝
    queue<pair<int, int>> que;
    que.push({0, 0});
    while (!que.empty())
    {
        pair<int, int> t = que.front();
        int i = t.first;
        int j = t.second;
        que.pop();
        if (i >= m || i < 0 || j >= n || j < 0 || flag[i][j] == 'i' || getsum(i, j) > k)
        {
            continue;
        }
        ans++;
        flag[i][j] = 'i';
        que.push({ i + 1, j });
        que.push({ i, j + 1 });
    }
    return ans;
//*/
}

//*********************************剑指 Offer 14 - I.剪绳子【数论、动态规划】
//*********************************剑指 Offer 14- II.剪绳子 II【】
/*
//描述：给你一根长度为 n 的绳子
        请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1）
        每段绳子的长度记为 k[0],k[1]...k[m-1] 。
        请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
int ans = cuttingRope(10);
cout << ans << endl;
//*/
//*//*/
int cuttingRope(int n) 
{
    if (n <= 3)
    {
        return n - 1;
    }
//*
    auto MyPow = [](int a, int b) -> long
    {
        long ret = 1;
        for (int i = 0; i < b; ++i)
        {
            ret = (ret * a) % 1000000007;
        }
        return ret;
    };
    // 数学推导
    int a = n / 3;
    int b = n % 3;
    long ans = 0;
    switch (b)
    {
    case 0:
        ans = MyPow(3, a);
        break;
    case 1:
        ans = MyPow(3, a - 1) * 4;
        break;
    case 2:
        ans = MyPow(3, a) * 2;
        break;
    default:
        break;
    }
    return (ans % 1000000007);
//*/

/*
    //动态规划-->剪绳子 II不适用，不能取余，值会变，不能递推
    vector<long> dp;
    dp.push_back(0);
    dp.push_back(1);
    dp.push_back(2);
    dp.push_back(3);
    for (int i = 4; i < n + 1; i++)
    {
        long max = 0;
        int len = (i >> 1) + 2;
        for (int j = 1; j < len; j++)
        {
            long temp = j * dp[i - j];
            max = (temp > max) ? temp : max;
        }
        dp.push_back(max);
    }

    return dp.back();
//*/
}

//*********************************【】
/*
//描述：
int ans = xxxx(nums);
cout << ans << endl;
//*/
//*//*/