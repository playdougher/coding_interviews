# 剑指offer习题 

## 1.赋值运算符函数

```c
/*
 * 编写赋值运算符
 *
 * 4. 判断是否为自身赋值，避免释放自身内存。
 * 1. 返回值为引用，才能允许连续赋值
 * 2. 参数为常量引用，提高效率，避免修改
 * 3. 释放已有空间，避免内存泄露
 */
class CMyString{
public:
    CMyString(char *pData = NULL);
    CMyString(const CMyString& str);
    ~CMyString(void);

private:
    char * m_pData;
};

CMyString& CMyString::operator = (const CMyString &str){
    //&str
    if(this == &str) return *this;
    
    delete []m_pData;
    m_pData = NULL;

    m_pData = new char[strlen(str.m_pData)+1];
    strcpy(m_pData, str.m_pData);
    return *this;

    /*
     * 确保异常安全性
     * 生成临时变量，交换m_pData，若由于内存不足抛出异常，不会影响到原先实例。
    if(this != &str){
        CMyString strTemp(str);
        char *pTemp = strTemp.m_pData;
        strTemp.m_pData = m_pData;
        m_pData = pTemp;
    }
    return *this;
    */
}
```

## 2.实现Singleton模式

[Singleton](https://www.cnblogs.com/cxjchen/p/3148582.html)

## 3.二维数组中的查找

题目：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

解法：
可以发现最右一列大于左边任何列，最上一行小于下方任何行  
若从右上开始查找，比如找7：  
7小于9，9所在列可排除  
7小于8，8所在列可排除   
7大于2，2所在行可排除  
7大于4，则往下走，找到值。

```
1 2 8  9
2 4 9  12
4 7 10 13
6 8 11 15
```

![](assets/img3_1.png)

```c
class Solution {
public:
    bool Find(int target, vector<vector<int>> array) {
        if (array.empty() || array[0].size() == 0 ) {
            return false;
        }
        int row = array.size();
        int col = array[0].size();
        int row_i = 0;
        int col_j = col-1;
        
        while(row_i < row and col_j >=0){
            if(target == array[row_i][col_j]) return true;
            else if (target < array[row_i][col_j]) col_j--;
            else row_i++;
        }
        return false;
    }
};
```

## 4.替换空格

题目：请实现一个函数，把字符串中的每个空格替换成“%20"。例如输入“We are happy.”，则输出“We%20are%20happy.”。

解法：直接在原数组中操作。

```c
/*
 * 从前往后处理复杂度高，而从后往前处理，O(n).
 * 1. 计算空格数
 * 2. 计算新字符串的长度
 * 3. 从后往前替换字符串。
 */

class Solution {
public:
    //length为字符串空间大小，非字符串长度。
	void replaceSpace(char *str,int length) {
	    if(!str or length == 0 ) return;

        int space_cnt =0;
        //str长度
        int char_cnt = 0; 

        int i = 0;
        while(str[i] != '\0'){
            char_cnt++;
            if(str[i] == ' '){
                space_cnt++;
            }
            i++;
        }
        //新字符串长度
        int new_len = char_cnt + space_cnt*2; 
        if(new_len+1 > length) return;

        //从'\0'开始处理
        int p1 = char_cnt;
        int p2 = new_len;

        while(p1 >= 0 and p1 < p2){
            while(str[p1] != ' '){
                str[p2--] = str[p1--];
            }
            str[p2--] = '0';
            str[p2--] = '2';
            str[p2--] = '%';
            p1--;
        }
	}
};
```

## 5.从尾到前打印链表

题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。

解法：将节点进栈再出栈得相反链表

```c
struct ListNode {
      int val;
      struct ListNode *next;
      ListNode(int x) :
            val(x), next(NULL) {
      }
};

class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> ans;
        stack<ListNode> stk;
        ListNode *p_node = head;
        while(p_node){
            stk.push(*p_node);
            p_node = p_node->next;
        }
        while(!stk.empty()){
            ListNode n = stk.top();
            ans.push_back(n.val);
            stk.pop();
        }
        return ans;
    }
};
```
## 6.重建二叉树

题目：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二文树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1，2，4，7，3，5，6，8}和中序遍历序列{4，7，2，1，5，3，8，6}，则重建出图2.6所示的二叉树并输出它的头结点。二叉树结点的定义如下：

解法：前序遍历的第一个元素为该序列的根节点，同时，该节点在中序遍历序列中将其分为左右子树两个序列。通过递归建立该树。

![](assets/img6_1.png)

```c
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* constructCore(vector<int> pre, int pre_beg, int pre_end, vector<int> in, int in_beg, int in_end){
        if(pre_beg > pre_end or in_beg > in_end) return NULL;

        TreeNode *node = new TreeNode(pre[pre_beg]);
        for(int i = in_beg; i <= in_end; i++){
            if(pre[pre_beg] == in[i]){
                int len_left = i-in_beg;
                node->left = constructCore(pre, pre_beg+1, pre_beg+len_left, in, in_beg, i-1);
                node->right = constructCore(pre, pre_beg+len_left+1, pre_end, in, i+1, in_end);
                break;
            }
        }
        return node;
    }

    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in) {
        return constructCore(pre,0,pre.size()-1, in,0,in.size()-1);
    }
}; 
 ```
 
## 7.用两个栈实现队列

题目：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数appendTail和deleteHead，分别完成在队列尾部插入结点和在队列头部删除结点的功能。

解法：将第一个栈中的数据弹出到第二个栈，再弹出时的顺序就是队列弹出时的顺序。

![](assets/img7.png)

```c
/*
 * 1.stack1作为队尾，stack2作为队头。
 * 2.出队就是弹出stack2，若其中有元素，直接弹出，若无元素，将stack1所有元素入栈stack2
 */
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int ret = 0;
        if(!stack2.empty()){
            ret = stack2.top();
            stack2.pop();
            return ret;
        }

        while(!stack1.empty()){
            stack2.push(stack1.top());
            stack1.pop();
        }
        ret = stack2.top();
        stack2.pop();
        return ret;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
```
 
## 8. 旋转数组的最小数字
 
题目：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组{3，4，5，1，2}为（1，2，3，4，5}的一个旋转，该数组的最小值为1。
 
```c
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        int left = 0;
        int right = rotateArray.size()-1;
        if(left > right) return -1;
        if(rotateArray[left] < rotateArray[right]) return rotateArray[0];
        while(left < right){
            int mid = (left+right)/2;
            if(rotateArray[left] < rotateArray[mid]){
                left = mid;
            }
            else if (rotateArray[mid] < rotateArray[right]){
                right = mid;
            }
            else left++;
        }
        return rotateArray[right];
    }
};
```
 
## 9.
