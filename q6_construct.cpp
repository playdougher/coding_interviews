
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
