#include <iostream>
#include <cmath>

using namespace std;

int digitAtIndex(int idx, int n);
int countOfIntegers(int n);
int digitAtIndex(int idx){
    if(idx <= 0) return 0;

    int len = 1;
    int idx_tmp = 0;

    //0,1,2,3,4,5,6,7,8,9,10
    while(idx >= 0){
        idx_tmp = idx;
        //printf("idx: %d\n" , idx);
        idx -= (countOfIntegers(len++));
    }
    return digitAtIndex(idx_tmp, --len);
}
int digitAtIndex(int idx, int n){
    int beg_num = 0;

    if(n == 1) beg_num = 0; //[x] if(n=1)
    else beg_num = pow(10, n-1);

    //idx所在的整数, 如10,11,12,..., idx=2, 则num=11
    int num = beg_num + (idx / n);
    //从左往右数, num的索引值
    int remain = idx % n;
    //idx所在位置到结尾的长度
    int right_count = n-remain;
    //printf("num: %d\n", num);

    //[!]right_count-1
    for(int i = 0; i < right_count-1; i++) num /= 10;

    return num % 10;
}

//计算n位数总共有几位. 比如n=2, 有10-99, 共90*2位
int countOfIntegers(int n){
    if(n == 1) return 10;
    else return 9*pow(10, n-1)*n;
}

// ====================测试代码====================
void test(const char* testName, int inputIndex, int expectedOutput)
{
	if(digitAtIndex(inputIndex) == expectedOutput)
		cout << testName << " passed." << endl;
	else
		cout << testName << " FAILED." << endl;
}


int main()
{
	test("Test1", 0, 0);
	test("Test2", 1, 1);
	test("Test3", 9, 9);
	test("Test4", 10, 1);
	test("Test5", 189, 9);  // 数字99的最后一位，9
	test("Test6", 190, 1);  // 数字100的第一位，1
	test("Test7", 1000, 3); // 数字370的第一位，3
	test("Test8", 1001, 7); // 数字370的第二位，7
	test("Test9", 1002, 0); // 数字370的第三位，0
	return 0;
}

