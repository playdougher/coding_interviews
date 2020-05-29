/*
 * 1. 如2^32次方，可以通过2^16平方取得。可用递归。
 * 2. 注意：若指数<0，分母有可能为0。
 */
class Solution {
public:
    double power_recur(double base, int exponent){
        if(exponent == 0) return 1;

        // exponent/2
        double result = power_recur(base,exponent >> 1);
        result *= result;

        //exponent若不能被2整除
        if(exponent&1) result *= base;
        return result;
    }
    double Power(double base, int exponent)
        int exp = exponent;
        if(exponent < 0) {
            exp = -exp;
            //分母不为0
            if(fabs(base-0.0) < 0.0000001) return 0;
        }
        
        double result = power_recur(base, exp);
        return exponent > 0 ? result : 1/result;
    }
};
