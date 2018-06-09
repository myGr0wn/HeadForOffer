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
	//①将int型数组中所有的int转换为char*字符串
	for (int i = 0; i < length; i++) {
		strNumbers[i] == new char[g_MaxNumberLength + 1];
		//sprintf函数的功能与printf函数的功能基本一样，只是它把结果输出到指定的字符串中
		sprintf(strNumbers[i], "%d", numbers[i]);
	}
	//②对字符串数组strNumbers进行排序，对数组中所有的字符串进行排序
	qsort(strNumbers, length, sizeof(char*), compare);
	//③输出已经排好序的字符串数组char**
	for (int i = 0; i < length; i++)
		cout << strNumbers[i];
	cout << endl;
	//④要注意把请求的内存空间给释放了delete[]
	for (int i = 0; i < length; i++)
		delete[] strNumbers[i];
	delete[] strNumbers;
}
// 如果[strNumber1][strNumber2] > [strNumber2][strNumber1], 返回值大于0
// 如果[strNumber1][strNumber2] = [strNumber2][strNumber1], 返回值等于0
// 如果[strNumber1][strNumber2] < [strNumber2][strNumber1], 返回值小于0
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