
// 面试题39：数组中出现次数超过一半的数字
// 题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例
// 如输入一个长度为9的数组{1, 2, 3, 2, 2, 2, 5, 4, 2}。由于数字2在数组中
// 出现了5次，超过数组长度的一半，因此输出2。

#include <cstdio>
#include <utility>

bool g_bInputInvalid = false;

bool CheckInvalidArray(int* numbers, int length)
{
    g_bInputInvalid = false;
    if(numbers == nullptr or length <= 0)
        g_bInputInvalid = true;

    return g_bInputInvalid;
}

bool CheckMoreThanHalf(int* numbers, int length, int number)
{
    int times = 0;
    for(int i = 0; i < length; ++i)
    {
        if(numbers[i] == number)
            times++;
    }

    bool isMoreThanHalf = true;
    if(times * 2 <= length)
    {
        g_bInputInvalid = true;
        isMoreThanHalf = false;
    }

    return isMoreThanHalf;
}
//===========func============
// return the index of data[end]'s final position
int Partition(int data[], int length, int beg, int end){
    if(!data or length < 0 or beg<0 or end >= length or beg > end){
        throw;
    }

    //make data[end] as the pivot

    //index of number smaller than small_idx are smaller than data[end];
    int small_idx = beg;
    int idx = beg;

    while(idx < end){
        if(data[idx] <= data[end]){
            if(small_idx != idx) std::swap(data[idx], data[small_idx]);
            small_idx++;
        }
        idx++;
    }

    std::swap(data[idx], data[small_idx]);
    return small_idx;
}
// ====================方法1====================
int MoreThanHalfNum_Solution1(int* num, int length){
    if(CheckInvalidArray(num, length))
        return 0;
    int mid_idx = (length-1)/2; //[x] length/2-1,偶偏右
    int idx_ret = -1;
    int beg = 0;
    int end = length-1;
    int result = 0;
    //printf("mid_idx:%d\n", mid_idx);
    while(idx_ret != mid_idx){
        //printf("beg: %d, end: %d\n", beg, end);
        idx_ret = Partition(num, length, beg, end);
        //printf("idx_ret: %d, val: %d\n", idx_ret, num[idx_ret]);
        if(idx_ret < mid_idx) beg = idx_ret+1;
        else end = idx_ret-1;
    }
    //printf("\n");
    result = num[idx_ret];

    if(!CheckMoreThanHalf(num, length, num[idx_ret])) result = 0;
    return result;
}

// ====================方法2====================
int MoreThanHalfNum_Solution2(int* numbers, int length)
{
    if(CheckInvalidArray(numbers, length))
        return 0;

    int result = numbers[0];
    int times = 1;

    int i = 1;
    while(i < length){
        if(numbers[i] == result)
            times++;
        else
            times--;
        i++;
        if(!times) result = numbers[i];
    }


    if(!CheckMoreThanHalf(numbers, length, result))
        result = 0;

    return result;
}

// ====================测试代码====================
void Test(char* testName, int* numbers, int length, int expectedValue, bool expectedFlag)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    int* copy = new int[length];
    for(int i = 0; i < length; ++i)
        copy[i] = numbers[i];

    printf("Test for solution1: ");
    int result = MoreThanHalfNum_Solution1(numbers, length);
    if(result == expectedValue && g_bInputInvalid == expectedFlag)
        printf("Passed.\n");
    else
        printf("Failed.\n");

    printf("Test for solution2: ");
    result = MoreThanHalfNum_Solution2(copy, length);
    if(result == expectedValue && g_bInputInvalid == expectedFlag)
        printf("Passed.\n");
    else
        printf("Failed.\n");

    delete[] copy;
}

// 存在出现次数超过数组长度一半的数字
void Test1()
{
    int numbers[] = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    Test("Test1", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 不存在出现次数超过数组长度一半的数字
void Test2()
{
    int numbers[] = {1, 2, 3, 2, 4, 2, 5, 2, 3};
    Test("Test2", numbers, sizeof(numbers) / sizeof(int), 0, true);
}

// 出现次数超过数组长度一半的数字都出现在数组的前半部分
void Test3()
{
    int numbers[] = {2, 2, 2, 2, 2, 1, 3, 4, 5};
    Test("Test3", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 出现次数超过数组长度一半的数字都出现在数组的后半部分
void Test4()
{
    int numbers[] = {1, 3, 4, 5, 2, 2, 2, 2, 2};
    Test("Test4", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 输入空指针
void Test5()
{
   int numbers[] = {1};
   Test("Test5", numbers, 1, 1, false);
}

// 输入空指针
void Test6()
{
    Test("Test6", nullptr, 0, 0, true);
}

void print(int a){
    int b = (a-1)/2;
    int c = (a/2)-1;
    printf("b:%d, c:%d\n", b, c);
}
int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
}


