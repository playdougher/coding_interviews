/*
 * 1. n=0 f(n)=0
 * 2. n=1 f(n)=1
 * 3. n=2 f(n)=2
 * 4. n>2 f(n)=f(n-1)+f(n-2)
 */
class Solution {
public:
    int jumpFloor(int n) {
        int a= 1; // f(n-1)
        int b = 2; // f(n)
        if (n <= 0) b = 0;
        else if(n == 1) b = 1;
        
        for(int i  = 3; i <= n ; i++){
            b += a;
            a = b-a;
        }
        return b;
    }
};

