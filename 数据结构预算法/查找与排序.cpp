#include<exception>
#include<iostream>

using namespace std;

//���������㷨
//������������ֵ
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
			throw new std::exception("���ϸ�����룡");
	}
	catch (std::exception e) {
		cout << e.what() << endl;
	}

	int small = start - 1;	//ָ����С����
	int flag = data[end];		//���ڽ��л��ֵı�־
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

	return small;	//���ص������һ����С������λ�ã���������С�����ִ�
}

void QuickSort(int data[], int length, int start, int end)
{
	if (start == end)
		return;	//ֻ��һ��������Ҫ����

	int index = Partition(data, length, start, end);
	if (index > start)//�������С������
		QuickSort(data, length, start, index - 1);
	if (index < end)//������ڴ���������
		QuickSort(data, length, index + 1, end);
}

//��Ա�������������
void SortAges(int ages[], int length)
{
	if (ages == nullptr || length == 0)
		return;
	const int oldestAge = 99;
	int timeOfAges[100];
	//�Դ��������������ͳ��
	for (int i = 0; i < length; i++) {
		int age = ages[i];
		if (age < 0 || age>99)
			throw new std::exception("���䳬��ͳ�Ʒ�Χ�ˣ�");
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
		throw new exception("���Ϸ����룡");

	int index1 = 0;
	int index2 = length - 1;
	//Ϊʲô�ǳ�ʼ��Ϊindex1��������index2��
	//��Ϊ�п�����ת������ת�������������ǰ��0��Ԫ�أ��������൱��û����ת��
	//ֱ�������һ��Ԫ�ؾͺ��ˣ���Ϊwhileѭ�������ý�ȥ��
	int indexMiddle = index1;
	while (array[index1] >= array[index2]) {
		//ѭ���˳��������ҵ���Сֵ��λ����
		if (index2 - index1 == 1) {
			indexMiddle = index2;
			break;
		}
		indexMiddle = (index1 + index2) / 2;
		//���middle��ǰ�����������
		if (array[indexMiddle] >= array[index1])
			index1 = indexMiddle;
		//���middle�ں�����������У���ǰ�ƺ����ָ�룬��С���ҷ�Χ
		else if (array[indexMiddle] <= array[index2])
			index2 = indexMiddle;
	}
	return array[indexMiddle];
}

//˳�����
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
		throw new exception("���Ϸ����룡");

	int index1 = 0;
	int index2 = length - 1;
	//Ϊʲô�ǳ�ʼ��Ϊindex1��������index2��
	//��Ϊ�п�����ת������ת�������������ǰ��0��Ԫ�أ��������൱��û����ת��
	//ֱ�������һ��Ԫ�ؾͺ��ˣ���Ϊwhileѭ�������ý�ȥ��
	int indexMiddle = index1;
	while (array[index1] >= array[index2]) {
		//ѭ���˳��������ҵ���Сֵ��λ����
		if (index2 - index1 == 1) {
			indexMiddle = index2;
			break;
		}
		indexMiddle = (index1 + index2) / 2;
		//�޸ĵĵط���
		//����±�Ϊindex1,indexMiddle,index2������Ԫ�ص�ֵ����ȣ�ֻ����˳�����
		if (array[index1] == array[index2] && array[index2] == array[indexMiddle])
			return MinInOrder(array, index1, index2);

		//���middle��ǰ�����������
		if (array[indexMiddle] >= array[index1])
			index1 = indexMiddle;
		//���middle�ں�����������У���ǰ�ƺ����ָ�룬��С���ҷ�Χ
		else if (array[indexMiddle] <= array[index2])
			index2 = indexMiddle;
	}
	return array[indexMiddle];
}