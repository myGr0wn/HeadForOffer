#include<exception>
#include<iostream>

using namespace std;

//快速排序算法
//交换两个数的值
void Swap(int *x, int *y)
{
	int p;
	p = *x;
	*x = *y;
	*y = p;
}
int  Partition(int data[], int length, int start, int end)
{
	try {
		if (data == nullptr || start < 0 || end >= length || length <= 0)
			throw new std::exception("不合格的输入！");
	}
	catch (std::exception e) {
		cout << e.what() << endl;
	}

	int small = start - 1;	//指向最小的数
	int flag = data[end];		//用于进行划分的标志
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

	return small;	//返回的是最后一个较小的数的位置，即大数与小数划分处
}

void QuickSort(int data[], int length, int start, int end)
{
	if (start == end)
		return;	//只有一个数不需要排序

	int index = Partition(data, length, start, end);
	if (index > start)//如果存在小的序列
		QuickSort(data, length, start, index - 1);
	if (index < end)//如果存在大数的序列
		QuickSort(data, length, index + 1, end);
}

//给员工年龄进行排序
void SortAges(int ages[], int length)
{
	if (ages == nullptr || length == 0)
		return;
	const int oldestAge = 99;
	int timeOfAges[100];
	//对传进来的年龄进行统计
	for (int i = 0; i < length; i++) {
		int age = ages[i];
		if (age < 0 || age>99)
			throw new std::exception("年龄超出统计范围了！");
		++timeOfAges[age];
	}
	int index = 0;
	for (int i = 0; i <= oldestAge; i++)
	{
		for (int j = 0; j < timeOfAges[i]; j++)
		{
			ages[index] = i;
			index++;
		}
	}
}

int Min(int array[], int length)
{
	if (array == nullptr || length <= 0)
		throw new exception("不合法输入！");

	int index1 = 0;
	int index2 = length - 1;
	//为什么是初始化为index1？而不是index2？
	//因为有可能旋转数组旋转的是排序数组的前面0个元素，这样就相当于没有旋转了
	//直接输出第一个元素就好了，因为while循环都不用进去了
	int indexMiddle = index1;
	while (array[index1] >= array[index2]) {
		//循环退出条件，找到最小值的位置了
		if (index2 - index1 == 1) {
			indexMiddle = index2;
			break;
		}
		indexMiddle = (index1 + index2) / 2;
		//如果middle在前面的子数组中
		if (array[indexMiddle] >= array[index1])
			index1 = indexMiddle;
		//如果middle在后面的子数组中，往前移后面的指针，缩小查找范围
		else if (array[indexMiddle] <= array[index2])
			index2 = indexMiddle;
	}
	return array[indexMiddle];
}

//顺序查找
int MinInOrder(int array[], int index1, int index2)
{
	int result = array[index1];
	for (int i = 0; i <= index2; i++)
	{
		if (array[i] < result)
			result = array[i];
	}
	return result;
}

int MinChoose(int array[], int length)
{
	if (array == nullptr || length <= 0)
		throw new exception("不合法输入！");

	int index1 = 0;
	int index2 = length - 1;
	//为什么是初始化为index1？而不是index2？
	//因为有可能旋转数组旋转的是排序数组的前面0个元素，这样就相当于没有旋转了
	//直接输出第一个元素就好了，因为while循环都不用进去了
	int indexMiddle = index1;
	while (array[index1] >= array[index2]) {
		//循环退出条件，找到最小值的位置了
		if (index2 - index1 == 1) {
			indexMiddle = index2;
			break;
		}
		indexMiddle = (index1 + index2) / 2;
		//修改的地方：
		//如果下标为index1,indexMiddle,index2的三个元素的值都相等，只能用顺序查找
		if (array[index1] == array[index2] && array[index2] == array[indexMiddle])
			return MinInOrder(array, index1, index2);

		//如果middle在前面的子数组中
		if (array[indexMiddle] >= array[index1])
			index1 = indexMiddle;
		//如果middle在后面的子数组中，往前移后面的指针，缩小查找范围
		else if (array[indexMiddle] <= array[index2])
			index2 = indexMiddle;
	}
	return array[indexMiddle];
}