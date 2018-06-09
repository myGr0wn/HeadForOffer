bool g_InvalidInput = false;//全局变量，用于判断是否有错误输入，即0的负数次幂
double Power(double base, int exponent)
{
	g_InvalidInput = true;
	//如果底数是0，指数还是负数，这是不允许的
	//所以要用全局变量提示出错了，那在调用的函数中就要对全局变量进行判断
	if (base < 0.00000001 && exponent < 0) {//double类型的比较只能用近似值
		g_InvalidInput = false;
		return 0.0;
	}

	unsigned int absExponent = (unsigned int)(exponent);	//求绝对值
	if (exponent < 0)
		absExponent = (unsigned int)(-exponent);
	double result = PowerWithUnsignedExponent(base, absExponent);
	if (exponent < 0)
		return 1.0 / result;
	return result;
}

double  PowerWithUnsignedExponent1(double base, unsigned int absExponent)
{
	double result = 1.0;
	for (int i = 0; i < absExponent; i++)
		result *= base;
	return result;
}

double PowerWithUnsignedExponent(double base, unsigned int absExponent)
{
	if (absExponent == 0)
		return 1.0;
	if (absExponent == 1)
		return base;
	double result = PowerWithUnsignedExponent(base, absExponent >> 1);//！！！！！>>除以2
	result *= result;
	if (absExponent & 0x1 == 1) //与1相与，判断是不是奇数！！！！！
		result *= base;
	return result;
}

#include<algorithm>
#include<iostream>
using std::cout;
//打印从1到最大的n位数
void Print1ToMaxOfNDigits(int n)
{	//负面情况
	if (n <= 0)
		return;
	char* number = new char[n + 1];//因为n位长的数字的字符串其实长度应该为n+1,最后一位是'\0'
	memset(number, '0', n);//为number数组的元素清0
	number[n] = '\0';
	while (Increment(number))
		PrintNumber(number);
	delete[] number;
}
//功能1：判断是否到了最大的n位数：n个9
//功能2：得到下一个数，+1
bool Increment(char* number)
{
	bool isOverflow = false;
	int nTakeOver = 0;//进位标志
	int nLength = strlen(number);
	for (int i = nLength-1; i >=0; i--)
	{	//number[i] - '0'：找到当前位置对应的int值
		//比如说百位数上是'5',那下一位i-1就没有进位了
		int nSum = number[i] - '0' + nTakeOver;
		//个位数上加1，其他位就是看有没有进位了
		if (i == nLength - 1)
			nSum++;
		if (nSum >= 10) {
			if (i == 0)
				//只有达到最大的n位数才会在第0位上有进位
				isOverflow = true;//已经到达最大的n位数了
			else {
				nSum -= 10;
//在当前的i对下一个位有进位，但是下下一个位也有进位吗？就是用完一次进位之后它并没有还原为0啊
//上面这个逻辑是错的，它是一直进位直到碰到不需要进位的就break，退出此次的循环了。
//比如199，在第一个9+1=10>=10之后，就有一个进位，之后进入下一个循环；
//下一位依然是9-0+1=10>=10，还是有进位，下一个循环；1-0+1=2<10所以没有进位了，直接break，后面的高位的数就不用改变了
				nTakeOver = 1;
				number[i] = '0' + nSum;
			}
		}
		else {
			number[i] = '0' + nSum;
			break;
		}
	}
	return isOverflow;
}
//每生成一个数就打印一个数，为什么不能直接打印？
//因为在生成数的时候，我们在数的前面补了'0'字符。
//打印的时候我们希望能按照我们的阅读习惯打印出来
void PrintNumber(char* number)
{
	bool isBegining0 = true;
	int nLength = strlen(number);
	for(int i=0;i<nLength;i++){
		if (isBegining0&&number[i] != '0')
			isBegining0 = false;
		if (!isBegining0)
			cout << number[i];
	}
	cout << "\t";
}
//使用递归:0到9的n个全排列
void Print1ToMaxOfDigitsWithRec(int n)
{
	if (n <= 0)
		return;
	char* number = new char[n + 1];
	number[n] = '\0';
	//最高位第0位开始触发
	for (int i = 0; i < 10; i++) {
		number[0] = i + '0';//使用ASCII
		PrintToMaxOfDigitsRecursively(number, n, 0);
	}
}

void PrintToMaxOfDigitsRecursively(char* number, int length, int index)
{
	if (index == length - 1) {
		PrintNumber(number);//循环到最后一个数了，生成数完成
		return;
	}
	for (int i = 0; i < 10; i++) {
		number[index + 1] = i + '0';
		PrintToMaxOfDigitsRecursively(number, length, index + 1);
	}
}