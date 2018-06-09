#include<stdlib.h>	//qsort
int compare(const void* arg1, const void* arg2)
{
	return *(int*)arg1 - *(int*)arg2;
}

bool isContinuous(int *numbers, int length)
{
	//���ų���������Ƶ����
	if (numbers == nullptr || length < 1)
		return false;
	//void qsort (void* base, size_t num, size_t size,int(*compar)(const void*, const void*));
	/*���������qsort�ظ��������Ƚ�����Ԫ�ء� ��Ӧ��ѭ����ԭ��:int compar (const void* p1, const void* p2);*/
	qsort(numbers, length, sizeof(int), compare);

	int numberOfZero = 0;
	int numberOfGap = 0;
	//ͳ��0�ĸ������������ź������ͳ�Ƶģ�����0������һ���
	for (int i = 0; i < length&&numbers[i] == 0; i++)
		numberOfZero++;
	//ͳ�������еļ����Ŀ��small��ǰ���Ǹ��������꣬big�Ǻ����Ǹ���������
	int small = numberOfZero;
	int big = small + 1;
	while (big < length) {
		//��������ȣ��ж��ӣ����Ծ�ֱ��over��
		if (numbers[small] == numbers[big])
			return false;
		numberOfGap += numbers[big] - numbers[small] - 1;
		small++;
		big++;
	}
	return (numberOfGap <= numberOfZero);
}


//���ڹ�Ʊ����������
int MaxDiff(const int* numbers, unsigned length)
{
	if (numbers == nullptr || length < 2)
		return 0;

	int min = numbers[0];
	int maxDiff = numbers[1] - min;

	//ÿ��i����һ�������ۣ�ÿһ����iǰ����ֶ���һ�������
	for (int i = 2; i < length; i++)
	{
		//��Ϊi����1������ǰ�����Ҳֻ������1������i-1
		if (numbers[i - 1] < min)
			min = numbers[i - 1];

		int currentDiff = numbers[i] - min;
		if (currentDiff > maxDiff)
			maxDiff = currentDiff;
	}
	return maxDiff;
}