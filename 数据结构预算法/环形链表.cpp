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
		//��¼��һ����Ҫ��Ȼɾ��������
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
	int last = 0;	//��n=1ʱ�����ʣ�µ�һ����Ҳ��ֻ��0������Ҫ���в���
	//�������ϵķ�����֮����������������������п��Ը�����һ���������м�������ʣ�µ����ֵ�ֵ����������Ҳ����
	for (int i = 2; i <= n; i++)
		last = (last + m) % i;
	return last;
}