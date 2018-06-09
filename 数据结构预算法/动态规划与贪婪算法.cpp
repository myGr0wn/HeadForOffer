#include<math.h>

//f(2)=1*1;f(3)=1*2>1*1*1?1*2:1*1*1
int maxProductAfterCutting1(int length)
{
	if (length < 2)//0||1
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	//为什么是n+1?因为要计算的是第n个值，在数组中有第n个值的数组，最少要n+1长（从第0开始算）
	int *products = new int[length + 1];
	int i;
	for (i = 0; i <= 3; i++)
		products[i] = i;
	int max = 0;
	//i=4，下面的算法类似于斐波那契数列
	for (; i <= length; i++) {
		max = 0;
		for (int j = 1; j <= i / 2; j++) {
			int product = products[j] * products[i - j];
			if (max < product)
				max = product;

			products[i] = max;
		}
	}
	max = products[length];
	delete[] products;
	return max;
}

//贪婪算法
int maxProductAfterCutting2(int length)
{
	if (length < 2)//0||1
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	//尽可能剪去长度为3的绳子
	int timeOf3 = length / 3;
	//当绳子最后剩下的长度为4时，不再剪去3，而是2*2；只有4才需要-1
	if (length - timeOf3 * 3 == 1)//表示最后剩下的是3+1=4
		timeOf3--;
	//因为倒数两段必须>=5才能继续剪3，所以倒数最后一段只能为4，3，2；
	//如果最后一段是4，则2；3，则0，但timeOf3没有减1；2，则1，反正最后也是等于2；
	//最后一段是1，2，3就不需要再剪了，保持就好
	int timeOf2 = (length - timeOf3 * 3) / 2;
	return (int)(pow(3, timeOf3))*(int)(pow(2, timeOf2));
}