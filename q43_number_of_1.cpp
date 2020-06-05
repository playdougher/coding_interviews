// 面试题43：从1到n整数中1出现的次数
// 题目：输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。例如
// 输入12，从1到12这些整数中包含1 的数字有1，10，11和12，1一共出现了5次。

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

// ====================方法一====================
int NumberOf1(unsigned int n);

int NumberOf1Between1AndN_Solution1(unsigned int n)
{
    int number = 0;

    for(unsigned int i = 1; i <= n; ++ i)
        number += NumberOf1(i);

    //printf("%d\n",number);
    return number;
}

int NumberOf1(unsigned int n)
{
    int number = 0;
    while(n)
    {
        if(n % 10 == 1)
            number ++;

        n = n / 10;
    }
    return number;
}

// ====================方法二====================
int NumberOf1(const char *str_n);
int NumberOf1Between1AndN_Solution2(int n){
    if(n < 0) return 0;
    char str_n[64];
    sprintf(str_n, "%d", n);
    return NumberOf1(str_n);
}

int NumberOf1(const char *str_n){
    if(!str_n or *str_n == '\0' ) return 0; //'\0'
	//第一个数字为0, 进行下一个递归
    if(*str_n == 0 +'0') return NumberOf1(str_n+1);

    int first_num = *str_n-'0';
    size_t length = strlen(str_n);
    if(length == 1) return first_num >= 1 ? 1 : 0;

    int num_of_first = 0;
    if(first_num == 1){
        num_of_first = atoi(str_n+1) + 1; //+1
    }
    else num_of_first = pow(10, length-1);

    int num_of_others = (length-1)*pow(10, length-2)*first_num;

    int num_of_recursive = NumberOf1(str_n+1);
    //printf("%d\n",num_of_recursive + num_of_others + num_of_first);
    return num_of_recursive + num_of_others + num_of_first;
}

// ====================测试代码====================
void Test(const char* testName, int n, int expected)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    if(NumberOf1Between1AndN_Solution1(n) == expected)
        printf("Solution1 passed.\n");
    else
        printf("Solution1 failed.\n");

    if(NumberOf1Between1AndN_Solution2(n) == expected)
        printf("Solution2 passed.\n");
    else
        printf("Solution2 failed.\n");

    printf("\n");
}

void Test()
{
    Test("Test1", 1, 1);
    Test("Test2", 5, 1);
    Test("Test3", 10, 2);
    Test("Test4", 55, 16);
    Test("Test5", 99, 20);
    Test("Test6", 10000, 4001);
    Test("Test7", 21345, 18821);
    Test("Test8", 0, 0);
    Test("Test9", 101, 23);
}

int main(int argc, char* argv[])
{
    Test();

    return 0;
}

