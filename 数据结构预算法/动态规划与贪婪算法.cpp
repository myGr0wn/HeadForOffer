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

	//Ϊʲô��n+1?��ΪҪ������ǵ�n��ֵ�����������е�n��ֵ�����飬����Ҫn+1�����ӵ�0��ʼ�㣩
	int *products = new int[length + 1];
	int i;
	for (i = 0; i <= 3; i++)
		products[i] = i;
	int max = 0;
	//i=4��������㷨������쳲���������
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

//̰���㷨
int maxProductAfterCutting2(int length)
{
	if (length < 2)//0||1
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	//�����ܼ�ȥ����Ϊ3������
	int timeOf3 = length / 3;
	//���������ʣ�µĳ���Ϊ4ʱ�����ټ�ȥ3������2*2��ֻ��4����Ҫ-1
	if (length - timeOf3 * 3 == 1)//��ʾ���ʣ�µ���3+1=4
		timeOf3--;
	//��Ϊ�������α���>=5���ܼ�����3�����Ե������һ��ֻ��Ϊ4��3��2��
	//������һ����4����2��3����0����timeOf3û�м�1��2����1���������Ҳ�ǵ���2��
	//���һ����1��2��3�Ͳ���Ҫ�ټ��ˣ����־ͺ�
	int timeOf2 = (length - timeOf3 * 3) / 2;
	return (int)(pow(3, timeOf3))*(int)(pow(2, timeOf2));
}