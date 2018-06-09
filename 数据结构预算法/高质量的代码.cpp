bool g_InvalidInput = false;//ȫ�ֱ����������ж��Ƿ��д������룬��0�ĸ�������
double Power(double base, int exponent)
{
	g_InvalidInput = true;
	//���������0��ָ�����Ǹ��������ǲ������
	//����Ҫ��ȫ�ֱ�����ʾ�����ˣ����ڵ��õĺ����о�Ҫ��ȫ�ֱ��������ж�
	if (base < 0.00000001 && exponent < 0) {//double���͵ıȽ�ֻ���ý���ֵ
		g_InvalidInput = false;
		return 0.0;
	}

	unsigned int absExponent = (unsigned int)(exponent);	//�����ֵ
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
	double result = PowerWithUnsignedExponent(base, absExponent >> 1);//����������>>����2
	result *= result;
	if (absExponent & 0x1 == 1) //��1���룬�ж��ǲ�����������������
		result *= base;
	return result;
}

#include<algorithm>
#include<iostream>
using std::cout;
//��ӡ��1������nλ��
void Print1ToMaxOfNDigits(int n)
{	//�������
	if (n <= 0)
		return;
	char* number = new char[n + 1];//��Ϊnλ�������ֵ��ַ�����ʵ����Ӧ��Ϊn+1,���һλ��'\0'
	memset(number, '0', n);//Ϊnumber�����Ԫ����0
	number[n] = '\0';
	while (Increment(number))
		PrintNumber(number);
	delete[] number;
}
//����1���ж��Ƿ�������nλ����n��9
//����2���õ���һ������+1
bool Increment(char* number)
{
	bool isOverflow = false;
	int nTakeOver = 0;//��λ��־
	int nLength = strlen(number);
	for (int i = nLength-1; i >=0; i--)
	{	//number[i] - '0'���ҵ���ǰλ�ö�Ӧ��intֵ
		//����˵��λ������'5',����һλi-1��û�н�λ��
		int nSum = number[i] - '0' + nTakeOver;
		//��λ���ϼ�1������λ���ǿ���û�н�λ��
		if (i == nLength - 1)
			nSum++;
		if (nSum >= 10) {
			if (i == 0)
				//ֻ�дﵽ����nλ���Ż��ڵ�0λ���н�λ
				isOverflow = true;//�Ѿ���������nλ����
			else {
				nSum -= 10;
//�ڵ�ǰ��i����һ��λ�н�λ����������һ��λҲ�н�λ�𣿾�������һ�ν�λ֮������û�л�ԭΪ0��
//��������߼��Ǵ�ģ�����һֱ��λֱ����������Ҫ��λ�ľ�break���˳��˴ε�ѭ���ˡ�
//����199���ڵ�һ��9+1=10>=10֮�󣬾���һ����λ��֮�������һ��ѭ����
//��һλ��Ȼ��9-0+1=10>=10�������н�λ����һ��ѭ����1-0+1=2<10����û�н�λ�ˣ�ֱ��break������ĸ�λ�����Ͳ��øı���
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
//ÿ����һ�����ʹ�ӡһ������Ϊʲô����ֱ�Ӵ�ӡ��
//��Ϊ����������ʱ������������ǰ�油��'0'�ַ���
//��ӡ��ʱ������ϣ���ܰ������ǵ��Ķ�ϰ�ߴ�ӡ����
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
//ʹ�õݹ�:0��9��n��ȫ����
void Print1ToMaxOfDigitsWithRec(int n)
{
	if (n <= 0)
		return;
	char* number = new char[n + 1];
	number[n] = '\0';
	//���λ��0λ��ʼ����
	for (int i = 0; i < 10; i++) {
		number[0] = i + '0';//ʹ��ASCII
		PrintToMaxOfDigitsRecursively(number, n, 0);
	}
}

void PrintToMaxOfDigitsRecursively(char* number, int length, int index)
{
	if (index == length - 1) {
		PrintNumber(number);//ѭ�������һ�����ˣ����������
		return;
	}
	for (int i = 0; i < 10; i++) {
		number[index + 1] = i + '0';
		PrintToMaxOfDigitsRecursively(number, length, index + 1);
	}
}