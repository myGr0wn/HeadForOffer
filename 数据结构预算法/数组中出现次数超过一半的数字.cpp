#include<exception>
void Swap(int *x, int *y)
{
	int p;
	p = *x;
	*x = *y;
	*y = p;
}
int  Partition(int data[], int length, int start, int end)
{
	if (data == nullptr || start < 0 || end >= length || length <= 0)
		throw new std::exception("不合格的输入！");

	int small = start - 1;  //指向最小的数
	int flag = data[end];       //用于进行划分的标志
	for (int i = 0; i < length; i++)
	{
		if (data[i] < flag) {
			small++;
			Swap(&data[i], &data[small]);
		}
	}
	//最后还要将最后一个数放到前面，和其他小的数放到一起
	++small;
	Swap(&flag, &data[small]);

	return small;   //返回的是最后一个较小的数的位置，即大数与小数划分处
}
//有可能并不存在出现次数超过一半的数组，所以要检查以下
int CheckMoreThanHalf(int* numbers, int length, int number)
{
	int times = 0;
	for (int i = 0; i < length; i++) {
		if (numbers[i] == number)
			times++;
	}
	bool isMoreThanHalf = true;
	if (times * 2 <= length)
		isMoreThanHalf = false;
	return isMoreThanHalf;
}
//方法1：基于Partition函数的时间复杂度为O(n)的算法
int MoreThanHalfNum_1(int* numbers, int length)
{
	if (numbers == nullptr || length == 0)
		return 0;
	int middle = length >> 1;	//除以2
	int start = 0;
	int end = length - 1;
	int index = Partition(numbers, length, start, end);//分界处
	while (index != middle) {
		if (index > middle) {
			end = index - 1;
			index = Partition(numbers, length, start, end);
		}
		else {
			start = index + 1;
			index = Partition(numbers, length, start, end);
		}
	}
	int result=numbers[middle];
	if (!CheckMoreThanHalf(numbers, length, result))
		result = 0;
	return result;
}

//方法2:根据数组特点（就是说要审题）找出使劲按复杂度为O(n)的算法
int MoreThanHalfNum_2(int* numbers, int length)
{
	if (numbers == nullptr || length == 0)
		return 0;

	int result = numbers[0];
	int times = 1;
	for (int i = 1; i < length; i++) {
		if (times == 0) {
			result = numbers[i];
			times++;
		}
		else if (numbers[i] == result)
			times++;
		else times++;
	}
	if (!CheckMoreThanHalf(numbers, length, result))
		result = 0;
	return result;
}

//最小的k个数
//基于Partition函数
void GetLeastNumbers_1(int* input, int n, int* output, int k)
{
	//为什么output也判断？因为如果output没有指向
	//就是说它根本不存在的话，返回的输出要放到哪个地址都不知道
	if (input == nullptr || output == nullptr || k > n || n <= 0 || k <= 0)
		return;
	int start = 0;
	int end = n - 1;
	int index = Partition(input, n, start, end);
	while (index != k - 1) {
		if (index > k - 1) {
			end = index - 1;
			index = Partition(input, n.start, end);
		}
		else {
			start = index + 1;
			index = Partition(input, n, start, end);
		}
	}
	for (int i = 0; i < k; i++)
		output[i] = input[i];
}

#include<set>
#include<vector>
#include<iterator>
#include<functional>

using namespace std;

typedef multiset<int, greater<int>> intSet;
typedef multiset<int, greater<int>>::iterator setIterator;

//解法2：使用红黑树
void GetLeastNumbers_2(const vector<int>&data, intSet& leastNumbers, int k)
{
	leastNumbers.clear;
	if (k < 1 || data.size() < k)
		return;

	vector<int>::const_iterator iter = data.begin();
	for (; iter != data.end(); iter++) {
		if (leastNumbers.size() < k)
			leastNumbers.insert(*iter);
		else {
			setIterator iterGreatest = leastNumbers.begin();
			if (*iter < *(leastNumbers.begin())) {
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}