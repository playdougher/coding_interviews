// 面试题21：调整数组顺序使奇数位于偶数前面
// 题目：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有
// 奇数位于数组的前半部分，所有偶数位于数组的后半部分。

#include <cstdio>

bool is_even(int num);
void Reorder(int *p_data, int length, bool (*fun)(int));

// ====================方法一====================
void ReorderOddEven_1(int *p_data, int length){
    if(!p_data or length==0) return;

    int *p_beg = p_data;
    int *p_end = p_data+length-1;

    while(p_beg < p_end){
        // odd
        while(p_beg < p_end and (*p_beg & 1)){
            p_beg++;
        }
        // even
        while(p_beg < p_end and !(*p_beg & 1)){
            p_end--;
        }
        int tmp = *p_beg;
        *p_beg = *p_end;
        *p_end = tmp;
    }
}

// ====================方法二====================
void ReorderOddEven_2(int *pData, unsigned int length)
{
    Reorder(pData, length, is_even);
}

bool is_even(int num){
    return (num&1) == 0;
}
void Reorder(int *p_data, int length, bool (*fun)(int)){
    if(!p_data or length==0) return;

    int *p_beg = p_data;
    int *p_end = p_data+length-1;

    while(p_beg < p_end){
        // odd
        while(p_beg < p_end and !fun(*p_beg)){
            p_beg++;
        }
        // even
        while(p_beg < p_end and fun(*p_end)){
            p_end--;
        }
        int tmp = *p_beg;
        *p_beg = *p_end;
        *p_end = tmp;
    }
}

// ====================测试代码====================
void PrintArray(int numbers[], int length)
{
    if(length < 0)
        return;

    for(int i = 0; i < length; ++i)
        printf("%d\t", numbers[i]);

    printf("\n");
}

void Test(char* testName, int numbers[], int length)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    int* copy = new int[length];
    for(int i = 0; i < length; ++i)
    {
        copy[i] = numbers[i];
    }

    printf("Test for solution 1:\n");
    PrintArray(numbers, length);
    ReorderOddEven_1(numbers, length);
    PrintArray(numbers, length);

    printf("Test for solution 2:\n");
    PrintArray(copy, length);
    ReorderOddEven_2(copy, length);
    PrintArray(copy, length);

    delete[] copy;
}

void Test1()
{
    int numbers[] = {1, 2, 3, 4, 5, 6, 7};
    Test("Test1", numbers, sizeof(numbers)/sizeof(int));
}

void Test2()
{
    int numbers[] = {2, 4, 6, 1, 3, 5, 7};
    Test("Test2", numbers, sizeof(numbers)/sizeof(int));
}

void Test3()
{
    int numbers[] = {1, 3, 5, 7, 2, 4, 6};
    Test("Test3", numbers, sizeof(numbers)/sizeof(int));
}

void Test4()
{
    int numbers[] = {1};
    Test("Test4", numbers, sizeof(numbers)/sizeof(int));
}

void Test5()
{
    int numbers[] = {2};
    Test("Test5", numbers, sizeof(numbers)/sizeof(int));
}

void Test6()
{
    Test("Test6", nullptr, 0);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}


