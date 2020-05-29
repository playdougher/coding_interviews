#include <bits/stdc++.h>
using namespace std;
void print_digits_recur(char *, int, int);
void print_number(char *, int);

void print_1_to_max_of_digits(int n){
    if(n <= 0) return;
    char number[n+1] = "";
    print_digits_recur(number, n, 0);
}

void print_digits_recur(char * number, int n, int index){
    //此时该数已构建完成，可以输出
    if(index == n){
        print_number(number, n);
        cout << ' ';
        return;
    }
    for(int i = 0; i <= 9; i++){
        number[index] = i+'0';
        print_digits_recur(number, n, index+1);
    }
}

void print_number(char *number, int n){
    int ind = 0;
    while(number[ind] == '0' and ind < n){
        ind++;
    }
    while(ind < n) cout << number[ind++];
}
int main(){
    print_1_to_max_of_digits(4);
    return 0;
}
