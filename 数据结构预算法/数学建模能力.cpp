#include<stdlib.h>	//qsort
int compare(const void* arg1, const void* arg2)
{
	return *(int*)arg1 - *(int*)arg2;
}

bool isContinuous(int *numbers, int length)
{
	//先排除不按理出牌的情况
	if (numbers == nullptr || length < 1)
		return false;
	//void qsort (void* base, size_t num, size_t size,int(*compar)(const void*, const void*));
	/*这个函数被qsort重复调用来比较两个元素。 它应遵循以下原型:int compar (const void* p1, const void* p2);*/
	qsort(numbers, length, sizeof(int), compare);

	int numberOfZero = 0;
	int numberOfGap = 0;
	//统计0的个数，这是在排好序后再统计的，所以0是连在一起的
	for (int i = 0; i < length&&numbers[i] == 0; i++)
		numberOfZero++;
	//统计数组中的间隔数目，small是前面那个数的坐标，big是后面那个数的坐标
	int small = numberOfZero;
	int big = small + 1;
	while (big < length) {
		//两个数相等，有对子，所以就直接over了
		if (numbers[small] == numbers[big])
			return false;
		numberOfGap += numbers[big] - numbers[small] - 1;
		small++;
		big++;
	}
	return (numberOfGap <= numberOfZero);
}


//关于股票的买卖问题
int MaxDiff(const int* numbers, unsigned length)
{
	if (numbers == nullptr || length < 2)
		return 0;

	int min = numbers[0];
	int maxDiff = numbers[1] - min;

	//每个i都当一次卖出价，每一轮中i前面的又都当一次买入价
	for (int i = 2; i < length; i++)
	{
		//因为i增加1，那它前面的数也只增加了1个就是i-1
		if (numbers[i - 1] < min)
			min = numbers[i - 1];

		int currentDiff = numbers[i] - min;
		if (currentDiff > maxDiff)
			maxDiff = currentDiff;
	}
	return maxDiff;
}