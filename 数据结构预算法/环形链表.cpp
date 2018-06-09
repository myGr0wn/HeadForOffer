#include<list>
using std::list;

int lastRemaining1(unsigned int n, unsigned int m)
{
	if (n < 1 || m < 1)
		return -1;

	unsigned int i;
	list<int> numbers;
	for (int i = 0; i < n; i++)
		numbers.push_back(i);
	list<int>::iterator current = numbers.begin();
	while (numbers.size() > 1) {
		for (int i = 0; i < m; i++)
		{
			current++;
			if (current == numbers.end())
				current = numbers.begin();
		}
		//记录下一个，要不然删掉后会掉链
		list<int>::iterator next = ++current;
		if (next == numbers.end())
			next = numbers.begin();

		--current;
		numbers.erase(current);
		current = next;
	}
	return *current;
}

int lastRemaining(unsigned int n, unsigned int m)
{
	if (n < 1 || m < 1)
		return -1;
	int last = 0;	//当n=1时，最后剩下的一个数也就只有0，不需要进行操作
	//根据以上的分析，之后的序列中有两个数的序列可以根据有一个数的序列计算出最后剩下的数字的值。其他序列也类似
	for (int i = 2; i <= n; i++)
		last = (last + m) % i;
	return last;
}