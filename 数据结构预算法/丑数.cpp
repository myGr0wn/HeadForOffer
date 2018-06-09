bool isUgly(int number)
{
	while (number % 2 == 0)
		number /= 2;
	while (number % 3 == 0)
		number /= 3;
	while (number % 5 == 0)
		number /= 5;

	return (number == 1);
}

int GetUglyNumber(int index)
{
	if (index <= 0)
		return 0;

	int number = 0;
	int uglyFound = 0;
	while (uglyFound < index)
	{
		number++;
		if (isUgly(number))
			++uglyFound;
	}
	return number;
}
/*在前面分析的时候提到把已有的每个丑数分别乘以2、3和5。
事实上这不是必须的，因为已有的丑数是按顺序存放在数组中的。
对于乘以2而言，肯定存在某一个丑数T2，排在它之前的每个丑数
乘以2都会小于已有最大的丑数，在它之后的每个丑数乘以2得到的
结果都会太大。我们只需要记下这个丑数的位置，同时每次生成新
的丑数的时候去更新这个T2即可。对于乘以3和5而言，也存在同样的T3和T5
*/

int GetUglyNumber_2(int index)
{
	if (index <= 0)
		return 0;
	//存放所有的丑数
	int* pUglyNumbers = new int[index];
	pUglyNumbers[0] = 1;
	int nextUglyIndex = 1;
	//三个指针在一开始都指向pUglyNumber指向的空间
	int* pMultiply2 = pUglyNumbers;
	int* pMultiply3 = pUglyNumbers;
	int* pMultiply5 = pUglyNumbers;

	while (nextUglyIndex < index) {
		int min = (*pMultiply2 * 2 < *pMultiply3 * 3) ? *pMultiply2 * 2 : *pMultiply3 * 3;
		min = (min < *pMultiply5 * 5) ? min : *pMultiply5 * 5;
		//总是从P2 P3 P5中找一个最小的放进去
		pUglyNumbers[nextUglyIndex] = min;
		//对P2 P3 P5三个的指向进行改变，一般都是目前谁最小就改谁的指向
		//为什么是while？因为指向新的数之后可能还是小于现在最小的数，那就要继续变
		//直到指向符合条件的最大值
		while (*pMultiply2 * 2 <= pUglyNumbers[nextUglyIndex])
			++pMultiply2;
		while (*pMultiply3 * 3 <= pUglyNumbers[nextUglyIndex])
			++pMultiply3;
		while (*pMultiply5 * 5 <= pUglyNumbers[nextUglyIndex])
			++pMultiply5;

		++nextUglyIndex;
	}
	int ugly = pUglyNumbers[index - 1];
	delete[] pUglyNumbers;
	return ugly;
}