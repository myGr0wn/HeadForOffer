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
/*��ǰ�������ʱ���ᵽ�����е�ÿ�������ֱ����2��3��5��
��ʵ���ⲻ�Ǳ���ģ���Ϊ���еĳ����ǰ�˳�����������еġ�
���ڳ���2���ԣ��϶�����ĳһ������T2��������֮ǰ��ÿ������
����2����С���������ĳ���������֮���ÿ����������2�õ���
�������̫������ֻ��Ҫ�������������λ�ã�ͬʱÿ��������
�ĳ�����ʱ��ȥ�������T2���ɡ����ڳ���3��5���ԣ�Ҳ����ͬ����T3��T5
*/

int GetUglyNumber_2(int index)
{
	if (index <= 0)
		return 0;
	//������еĳ���
	int* pUglyNumbers = new int[index];
	pUglyNumbers[0] = 1;
	int nextUglyIndex = 1;
	//����ָ����һ��ʼ��ָ��pUglyNumberָ��Ŀռ�
	int* pMultiply2 = pUglyNumbers;
	int* pMultiply3 = pUglyNumbers;
	int* pMultiply5 = pUglyNumbers;

	while (nextUglyIndex < index) {
		int min = (*pMultiply2 * 2 < *pMultiply3 * 3) ? *pMultiply2 * 2 : *pMultiply3 * 3;
		min = (min < *pMultiply5 * 5) ? min : *pMultiply5 * 5;
		//���Ǵ�P2 P3 P5����һ����С�ķŽ�ȥ
		pUglyNumbers[nextUglyIndex] = min;
		//��P2 P3 P5������ָ����иı䣬һ�㶼��Ŀǰ˭��С�͸�˭��ָ��
		//Ϊʲô��while����Ϊָ���µ���֮����ܻ���С��������С�������Ǿ�Ҫ������
		//ֱ��ָ��������������ֵ
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