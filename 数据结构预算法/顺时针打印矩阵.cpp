#include<iostream>
using std::cout;

//顺时针打印矩阵，该函数主要是控制打印圈退出的条件
void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
	if (numbers == nullptr || columns <= 0 || rows <= 0)
		return;

	int start = 0;	//start是每个圈开始的坐标（横纵一样）
	while (columns > start * 2 && rows > start * 2) {
		PrintMatrixInCircle(numbers, columns, rows, start);
		++start;
	}
}
//按圈打印出数字.每次调用只打印一圈
void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)
{
	int endX = columns - 1 - start;//这个画图看会比较清晰
	int endY = rows - 1 - start;
	//从左到右打印一行
	for (int i = start; i <= endX; i++) {
		int number = numbers[start][i];
		cout << number << "\t";
	}
	//从上到下打印一列
	if (endY > start)
		for (int i = start + 1; i <= endY; i++) {
			int number = numbers[i][endY];
			cout << number << "\t";
		}
	//从右到左打印一行
	//终止行号大于起始行号，终止列号大于起始列号
	if(endX>start&&endY>start)
		for (int i = endX - 1; i >= start; i--) {
			int number = numbers[endY][i];
			cout << number << "\t";
		}
	//从下到上打印一列，所以是列号不变，行号减小
	if(endX>start&&endY-1>start)
		for (int i = endY; i >= start + 1; i--) {
			int number = numbers[i][start];
			cout << number << "\t";
		}
}
