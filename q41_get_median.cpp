
// 面试题41：数据流中的中位数
// 题目：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么
// 中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，
// 那么中位数就是所有数值排序之后中间两个数的平均值。

#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

template<typename T> class DynamicArray{
public:
    void Insert(T num){
        //even
        if((min.size()+max.size() & 1) == 0){
            if(!max.empty() and num < max.front()){
                max.push_back(num);
                push_heap(max.begin(), max.end());
                num = max.front();
                pop_heap(max.begin(), max.end());
                max.pop_back();
            }
            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<T>());

        }
        //odd
        else {
            if(!min.empty() and num > min.front()){
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<T>());
                num = min.front();

                pop_heap(min.begin(), min.end(), greater<T>());
                min.pop_back();
            }
            max.push_back(num);
            push_heap(max.begin(), max.end());
        }
    }

    T GetMedian(){
        int size = max.size() + min.size();
        if(size <= 0) throw length_error("No numbers");

        T median = 0;

        if(size & 1) median = min.front();
        else median = (max.front() + min.front())/2;

        return median;
    }
private:
    vector<T> max;
    vector<T> min;
};

// ====================测试代码====================
void Test(char* testName, DynamicArray<double>& numbers, double expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(abs(numbers.GetMedian() - expected) < 0.0000001)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
    DynamicArray<double> numbers;

    printf("Test1 begins: ");
    try
    {
        numbers.GetMedian();
        printf("FAILED.\n");
    }
    catch(const exception&)
    {
        printf("Passed.\n");
    }

    numbers.Insert(5);
    Test("Test2", numbers, 5);

    numbers.Insert(2);
    Test("Test3", numbers, 3.5);

    numbers.Insert(3);
    Test("Test4", numbers, 3);

    numbers.Insert(4);
    Test("Test6", numbers, 3.5);

    numbers.Insert(1);
    Test("Test5", numbers, 3);

    numbers.Insert(6);
    Test("Test7", numbers, 3.5);

    numbers.Insert(7);
    Test("Test8", numbers, 4);

    numbers.Insert(0);
    Test("Test9", numbers, 3.5);

    numbers.Insert(8);
    Test("Test10", numbers, 4);

    return 0;
}

