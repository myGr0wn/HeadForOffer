#include<iostream>

using namespace std;

int AddFrom1ToN(int n)
{
	return n <= 0 ? 0 : AddFrom1ToN(n - 1);
}

int AddFrom1ToN2(int n)
{
	int result = 0;
	for (int i = 0; i < n; i++)
		result += n;
	return result;
}

//쳲���������
long long Fibonacci1(unsigned int n)
{
	//unsigned �п���С��0����������ԣ���Ϊʲô���ﻹҪ�Ƚϣ�
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);

}

//�Ľ����쳲��������У������ʱ��Ч�ʺͿռ�Ч��
int Fibonacci(unsigned int n)
{
	if (n < 2)
		return n;
	long long fibMinusOne = 1;
	long long fibMinusTwo = 0;
	long long fibN = 0;
	for (unsigned int i = 0; i <= n; i++)
	{
		fibN = fibMinusOne + fibMinusTwo;
		fibMinusTwo = fibMinusOne;
		fibMinusOne = fibN;
	}

	return fibN;
}

//����������
int FrogJump(unsigned int n)
{
	if (n < 3)
		return n;
	long long fibMinusOne = 2;
	long long fibMinusTwo = 1;
	long long fibN = 0;
	for (unsigned int i = 3; i <= n; i++)
	{
		fibN = fibMinusOne + fibMinusTwo;
		fibMinusTwo = fibMinusOne;
		fibMinusOne = fibN;
	}

	return fibN;
}

//���ڵݹ�ļ���n�����Ӻ�Ϊs���ֵĸ���
#define MAX_VALUE 6
void printProbability(int n)
{
	if (n < 1)
		return;

	int maxSum = MAX_VALUE * n;
	//����һ����С���б��������������
	int* pProbabilities = new int[maxSum - n + 1];
	for (int i = 0; i < maxSum - n + 1; i++)
		pProbabilities[i] = 0;	//ΪʲôҪ�ȸ�ֵ��������ֵ�Ļ�Ĭ�ϲ�Ҳ��0�𡣡�
	
	//i��ʾ��һ���ѵ����ӵĵ�������ʵ�������ֻ��һ��������
	for (int i = 1; i <= MAX_VALUE; i++)
		Probability(n,n,i,pProbabilities);

	int total = pow((double)MAX_VALUE, n);//һ������ô���������Ϊ�˼������
	for (int i = 0; i < maxSum-n+1; i++)
	{
		double radio = (double)pProbabilities[i] / total;
		cout << i;
		cout << " : ";
		cout << radio << endl;
	}

}

//������1�����������Ӹ�����2����һ�ּ���ʱ�����Ӹ�����3����s��4����ź�s����������
void Probability(int n, int current, int sum, int* pProbabilities)
{
	//���ֻ����һ�����ӣ��Ǿ�ֱ���ڴ������ĵ�ǰ��sum�ϵĶ�Ӧ�����ϼ�1
	//Ϊʲô������ʵ���Ǳ�ʾ�ڶ�����n-1��sum�Ѿ���������
	if (current == 1)
		pProbabilities[sum - n]++;
	else
		for (int i = 1; i <= MAX_VALUE; i++)
			//sum+i�ǵ�һ���Ѻ͵ڶ����ѵĵ�һ�ѵĵ����ĺͣ�������Ҫ�����һ���ѵĵڶ�����
			Probability(n, current - 1, sum + i, pProbabilities);
}

//����ѭ���ļ���n�����Ӻ�Ϊs���ֵĸ���
void PrintProbability(int n)
{
	if (n < 1)
		return;
	int* pProbabilities[2];	//������������
	//�ֱ����������ָ����С�����Ǵ�����
	pProbabilities[0] = new int[MAX_VALUE*n - n + 1];
	pProbabilities[1] = new int[MAX_VALUE*n - n + 1];
	//����һ����ֵ�Ĺ��̣�ͻȻ�뵽���ͺ���int i=0;һ�����������i����ʼֵ���ǾͲ�����i���м���
	for (int i = 0; i < MAX_VALUE*n - n + 1; i++) {
		pProbabilities[0][i] = 0;
		pProbabilities[1][i] = 0;
	}

	int flag = 0;
	//ֻ��һ�����ӵ�ʱ�򣬳��ֵĿ���sum=1~6
	for (int i = 1; i <= MAX_VALUE; i++)
		pProbabilities[flag][i] = 1;
	//�����������ӿ�ʼʹ��ѭ������
	for (int k = 2; k <= n; k++) {
		for (int i = 0; i < k; i++)
			pProbabilities[1 - flag][i] = 0;
		//��ǰ���������k�����ӣ�����һ��s�ķ�Χ��k~6*k
		//ÿ��ѭ��������i��ʾ���Ǻ�sum
		for (int i = k; i <= MAX_VALUE * k; i++) {
			pProbabilities[1 - flag][i] = 0;
			//j<=i��������Ϊ�п��ܺ�i��2~6֮�䣬����ζ����������2~6��ÿ�����Ӷ�Ϊ1��ʱ��֮��
			//���Լ�����һ��s�ĸ�����ʱ�������û����Ҫ����ν��ǰ6������Ϊǰ��û��6��
			//���統������k=2�����i=3�ĸ�����ʱ���Ǿ�ֻ��Ҫ����ǰһ�ֵ�i-1��i-2��Ҳ����ֻ��һ�����ӣ�sum=1��2��ʱ��
			for (int j = 1; j <= i && j <= MAX_VALUE; j++)
				pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
		}
		flag = flag - 1;	//���������ɫ������֮�������һ�ּ���
	}//��������Ѿ���������

	double total = pow(MAX_VALUE, n);
	for (int i = n; i <= MAX_VALUE * n; i++) {
		double ratio = (double)pProbabilities[flag][i] / total;
		cout << i;
		cout << " : ";
		cout << ratio << endl;
	}

	delete[] pProbabilities[0];
	delete[] pProbabilities[1];
}
	
