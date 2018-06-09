#include<stdio.h>
#include<algorithm>
#include<iostream>
using std::cout;	using std::endl;

const int g_MaxNumberLength = 10;

char* strCombine_1 = new char[g_MaxNumberLength * 2 + 1];
char* strCombine_2 = new char[g_MaxNumberLength * 2 + 1];

void PrintMinNumber(int* numbers, int length)
{
	if (numbers == nullptr || length == 0)
		return;
	char** strNumbers = (char**)(new int[length]);
	//�ٽ�int�����������е�intת��Ϊchar*�ַ���
	for (int i = 0; i < length; i++) {
		strNumbers[i] == new char[g_MaxNumberLength + 1];
		//sprintf�����Ĺ�����printf�����Ĺ��ܻ���һ����ֻ�����ѽ�������ָ�����ַ�����
		sprintf(strNumbers[i], "%d", numbers[i]);
	}
	//�ڶ��ַ�������strNumbers�������򣬶����������е��ַ�����������
	qsort(strNumbers, length, sizeof(char*), compare);
	//������Ѿ��ź�����ַ�������char**
	for (int i = 0; i < length; i++)
		cout << strNumbers[i];
	cout << endl;
	//��Ҫע���������ڴ�ռ���ͷ���delete[]
	for (int i = 0; i < length; i++)
		delete[] strNumbers[i];
	delete[] strNumbers;
}
// ���[strNumber1][strNumber2] > [strNumber2][strNumber1], ����ֵ����0
// ���[strNumber1][strNumber2] = [strNumber2][strNumber1], ����ֵ����0
// ���[strNumber1][strNumber2] < [strNumber2][strNumber1], ����ֵС��0
int compare(const void* strNumber1, const void* strNumber2)
{
	//mn
	strcpy(strCombine_1, *(const char**)strNumber1);
	strcpy(strCombine_1, *(const char**)strNumber2);
	//nm
	strcpy(strCombine_2, *(const char**)strNumber2);
	strcpy(strCombine_1, *(const char**)strNumber1);

	return strcmp(strCombine_1, strCombine_2);
}