#include<math.h>
int digitAtIndex(int index)
{
	if (index < 0)
		return -1;
	int digits = 1;
	while (true)
	{
		//计算digits长的数字有多少个
		int numbers = countOfIntegers(digits);
		if (index < numbers*digits)
			return digitAtIndex(index, digits);
	}
}
//计算m位长的数字一共由多少个，比如传入2，输出90
int countOfIntegers(int digits)
{
	if (digits == 1)
		return 10;
	int count = (int)pow(10, digits);
	return 9 * count;
}
//对核心函数进行重载
//当我们知道要找的那一位数字位于某m位数之后，使用该函数找出要找的那个数
int digitAtIndex(int index, int digits)
{	//得到的是最终的目标所在的那个数，例子说的370
	int number = beginNumber(digits) + index / digits;
	int indexFromRight = digits - index % digits;//3-811%3=3-1=2
	for (int i = 1; i < indexFromRight; i++)
		number /= 10;		//370--》37
	return number % 10;		//37--》7
}
//m位长的数的第一个是啥,比如2位是100，3位是1000
int beginNumber(int digits)
{
	if (digits == 1)
		return 1;
	return (int)pow(10, digits-1);
}