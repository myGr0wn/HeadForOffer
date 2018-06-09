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
		throw new std::exception("���ϸ�����룡");

	int small = start - 1;  //ָ����С����
	int flag = data[end];       //���ڽ��л��ֵı�־
	for (int i = 0; i < length; i++)
	{
		if (data[i] < flag) {
			small++;
			Swap(&data[i], &data[small]);
		}
	}
	//���Ҫ�����һ�����ŵ�ǰ�棬������С�����ŵ�һ��
	++small;
	Swap(&flag, &data[small]);

	return small;   //���ص������һ����С������λ�ã���������С�����ִ�
}
//�п��ܲ������ڳ��ִ�������һ������飬����Ҫ�������
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
//����1������Partition������ʱ�临�Ӷ�ΪO(n)���㷨
int MoreThanHalfNum_1(int* numbers, int length)
{
	if (numbers == nullptr || length == 0)
		return 0;
	int middle = length >> 1;	//����2
	int start = 0;
	int end = length - 1;
	int index = Partition(numbers, length, start, end);//�ֽ紦
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

//����2:���������ص㣨����˵Ҫ���⣩�ҳ�ʹ�������Ӷ�ΪO(n)���㷨
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

//��С��k����
//����Partition����
void GetLeastNumbers_1(int* input, int n, int* output, int k)
{
	//ΪʲôoutputҲ�жϣ���Ϊ���outputû��ָ��
	//����˵�����������ڵĻ������ص����Ҫ�ŵ��ĸ���ַ����֪��
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

//�ⷨ2��ʹ�ú����
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