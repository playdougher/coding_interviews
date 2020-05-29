
class Solution {
public:
    int Fibonacci(int n) {
        int a= 0;
        int b = 1;
        if (n <= 0) b = 0;
        for(int i  = 2; i <= n ; i++){
            b += a;
            a = b-a;
        }
        return b;
    }
};

