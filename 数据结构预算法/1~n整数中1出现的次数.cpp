int NumberOf1(unsigned int i)
{
	int number = 0;
	while (i)
	{
		if (i % 10 == 1)
			number++;
		i /= 10;
	}
	return number;
}

int NumberOf1Between1AndN_1(unsigned int n)
{
	int number = 0;
	for (unsigned int i = 1; i <= n; i++)
		number += NumberOf1(i);
	return number;
}
//时间复杂度O(n)
int NumberOf1Between1AndN_2(unsigned int n)
{
	int count = 0;
	int base = 1;
	int round = n;
	while (round > 0) {
		int current = round % 10;
		round /= 10;
		count += round * base;
		//如果对于n当前位正好是1，那该位上的1的个数就与低位有关系了
		if (current == 1)
			count += (n%base) + 1;//n%base是低位上的数
		else if (current > 1)//如果大于1，那就是说低位上的数可以走个遍
			count += base;
		base *= 10;
	}
	return count;
}