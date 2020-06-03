// 面试题40：最小的k个数
// 题目：输入n个整数，找出其中最小的k个数。例如输入4、5、1、6、2、7、3、8
// 这8个数字，则最小的4个数字是1、2、3、4。

#include <cstdio>

#include <set>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

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

    //example: 2,2,2,1,1,1,2
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
void GetLeastNumbers_Solution1(int *input, int n, int *output, int k){
    if(!input or !output or k < 0 or k > n) return;

    int idx = -1;
    int beg = 0;
    int end = n-1;
    while(idx != k-1){ // k-1
        idx = Partition(input, n, beg, end);
        if(idx < k-1) beg = idx+1;
        else end = idx-1;
    }

    for(int i = 0; i < k; i++) output[i] = input[i];
}

// ====================方法2====================

typedef multiset<int, std::greater<int>> int_set;
typedef multiset<int, std::greater<int>>::iterator set_iterator;
void GetLeastNumbers_Solution2(const vector<int>& data, int_set& least_num, int k){
    if(k > data.size() or k < 0) return;

    least_num.clear();
    int i = 0;
    while(i < k){
        //printf("data[i]:%d\n",data[i]);
        least_num.insert(data[i++]);
    }

    while(i < data.size()){
        int max_num = *least_num.begin();
        if( data[i] < max_num) {
            //printf("max_num:%d\n",max_num);
            //printf("data[i]:%d\n",data[i]);
            least_num.erase(max_num);
            least_num.insert(data[i]);
        }
        ++i;
    }
}

// ====================测试代码====================
void Test(char* testName, int* data, int n, int* expectedResult, int k)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    vector<int> vectorData;
    for(int i = 0; i < n; ++ i)
        vectorData.push_back(data[i]);

    if(expectedResult == nullptr)
        printf("The input is invalid, we don't expect any result.\n");
    else
    {
        printf("Expected result: \n");
        for(int i = 0; i < k; ++ i)
            printf("%d\t", expectedResult[i]);
        printf("\n");
    }

    printf("Result for solution1:\n");
    int* output = new int[k];
    GetLeastNumbers_Solution1(data, n, output, k);
    if(expectedResult != nullptr)
    {
        for(int i = 0; i < k; ++ i)
            printf("%d\t", output[i]);
        printf("\n");
    }

    delete[] output;

    printf("Result for solution2:\n");
    int_set leastNumbers;
    GetLeastNumbers_Solution2(vectorData, leastNumbers, k);
    printf("The actual output numbers are:\n");
    for(set_iterator iter = leastNumbers.begin(); iter != leastNumbers.end(); ++iter)
        printf("%d\t", *iter);
    printf("\n\n");
}

// k小于数组的长度
void Test1()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4};
    Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于数组的长度
void Test2()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k大于数组的长度
void Test3()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k等于1
void Test4()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1};
    Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于0
void Test5()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// 数组中有相同的数字
void Test6()
{
    int data[] = {4, 5, 1, 6, 2, 7, 2, 8};
    int expected[] = {1, 2};
    Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// 输入空指针
void Test7()
{
    int* expected = nullptr;
    Test("Test7", nullptr, 0, expected, 0);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}

