#include<math.h>
int digitAtIndex(int index)
{
	if (index < 0)
		return -1;
	int digits = 1;
	while (true)
	{
		//����digits���������ж��ٸ�
		int numbers = countOfIntegers(digits);
		if (index < numbers*digits)
			return digitAtIndex(index, digits);
	}
}
//����mλ��������һ���ɶ��ٸ������紫��2�����90
int countOfIntegers(int digits)
{
	if (digits == 1)
		return 10;
	int count = (int)pow(10, digits);
	return 9 * count;
}
//�Ժ��ĺ�����������
//������֪��Ҫ�ҵ���һλ����λ��ĳmλ��֮��ʹ�øú����ҳ�Ҫ�ҵ��Ǹ���
int digitAtIndex(int index, int digits)
{	//�õ��������յ�Ŀ�����ڵ��Ǹ���������˵��370
	int number = beginNumber(digits) + index / digits;
	int indexFromRight = digits - index % digits;//3-811%3=3-1=2
	for (int i = 1; i < indexFromRight; i++)
		number /= 10;		//370--��37
	return number % 10;		//37--��7
}
//mλ�������ĵ�һ����ɶ,����2λ��100��3λ��1000
int beginNumber(int digits)
{
	if (digits == 1)
		return 1;
	return (int)pow(10, digits-1);
}