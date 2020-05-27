#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool Find(int target, vector<vector<int>> array) {
        if (array.empty()  || array[0].size() == 0 ) {
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
int main(){
    Solution s;
    vector<vector<int>> array = {{1, 2, 8, 9},{2, 4, 9, 12},{4, 7, 10, 13},{6, 8, 11, 15}};
    bool ans = s.Find(3,array);
    if(ans) cout << "YES" << endl; 
    else cout << "NO" << endl;
    return 0;
}
