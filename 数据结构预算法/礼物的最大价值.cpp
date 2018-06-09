#include<algorithm>
using std::max;

int getMaxValue_1(const int* values, int rows, int cols)
{
	if (values == nullptr || rows <= 0 || cols <= 0)
		return 0;
	//初始化一个int*数组
	int** maxValues = new int*[rows];
	for (int i = 0; i < rows; i++)
		maxValues[i] = new int[cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) {
			int left = 0;	//左边一个
			int up = 0;	//上面一个
			if (i > 0)
				up = maxValues[i - 1][j];
			if (j > 0)
				left = maxValues[i][j - 1];

			maxValues[i][j] = max(up, left) + values[i*cols + j];
		}
	}
	int maxValue = maxValues[rows - 1][cols - 1];

	for (int i = 0; i < rows; i++)
		delete[] maxValues[i];
	delete[] maxValues;
	return maxValue;
}

int getMaxValue_2(const int* values, int rows, int cols)
{
	if (values == nullptr || rows == 0 || cols == 0)
		return 0;
	int* maxValues = new int[cols];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++) {
			int left = 0;
			int up = 0;
			//数组从下标为j的数字开始到最后一个数字，
			//分别为f(i−1,j)，f(i−1,j+1)，f(i−1,j+2)，……，f(i−1,n−1)
			//因为每开始一个新的i就对一维数组的每一个值从头开始更新，所以j开始后面的还没有被更新到
			//其实无论是第一种做法还是第二种做法，都需要遍历每一格
			if (i > 0)
				up = maxValues[j];

			if (j > 0)
				left = maxValues[j - 1];
			maxValues[j] = max(left, up) + values[i*cols + j];
		}
	}
	int maxValue = maxValues[cols - 1];
	delete[] maxValues;
	return maxValue;
}