#include <bits/stdc++.h>
using namespace std;

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
...
...
