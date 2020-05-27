/*
 * 从前往后处理复杂度高，而从后往前处理，O(n).
 * 1. 计算空格数
 * 2. 计算新字符串的长度
 * 3. 从后往前替换字符串。
 */
#include <bits/stdc++.h>
using namespace std;
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

int main(){
    Solution s;
    char str[20] = " hello  world";
    s.replaceSpace(str, 100);
    int i = 0;
    while (str[i] != '\0'){
        cout << str[i];
        i++;
    }
    return 0;
}

