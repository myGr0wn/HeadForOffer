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
//ʱ�临�Ӷ�O(n)
int NumberOf1Between1AndN_2(unsigned int n)
{
	int count = 0;
	int base = 1;
	int round = n;
	while (round > 0) {
		int current = round % 10;
		round /= 10;
		count += round * base;
		//�������n��ǰλ������1���Ǹ�λ�ϵ�1�ĸ��������λ�й�ϵ��
		if (current == 1)
			count += (n%base) + 1;//n%base�ǵ�λ�ϵ���
		else if (current > 1)//�������1���Ǿ���˵��λ�ϵ��������߸���
			count += base;
		base *= 10;
	}
	return count;
}