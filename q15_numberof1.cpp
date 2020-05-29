class Solution {
public:
     int  NumberOf1(int n) {
         int cnt = 0;
         int flag = 1;
         while(flag){
             if(n & flag) ++cnt;
             flag = flag << 1;
         }
         return cnt;
     }
};
