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

//斐波那契数列
long long Fibonacci1(unsigned int n)
{
	//unsigned 有可能小于0吗？如果不可以，那为什么这里还要比较？
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);

}

//改进版的斐波那契数列，提高了时间效率和空间效率
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

//青蛙跳问题
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

//基于递归的计算n个骰子和为s出现的概率
#define MAX_VALUE 6
void printProbability(int n)
{
	if (n < 1)
		return;

	int maxSum = MAX_VALUE * n;
	//定义一个大小带有变量的数组的做法
	int* pProbabilities = new int[maxSum - n + 1];
	for (int i = 0; i < maxSum - n + 1; i++)
		pProbabilities[i] = 0;	//为什么要先赋值？？不赋值的话默认不也是0吗。。
	
	//i表示第一个堆的骰子的点数。其实这个调用只是一个触发点
	for (int i = 1; i <= MAX_VALUE; i++)
		Probability(n,n,i,pProbabilities);

	int total = pow((double)MAX_VALUE, n);//一共有这么多种情况，为了计算概率
	for (int i = 0; i < maxSum-n+1; i++)
	{
		double radio = (double)pProbabilities[i] / total;
		cout << i;
		cout << " : ";
		cout << radio << endl;
	}

}

//参数：1、真正的骰子个数；2、这一轮计算时的骰子个数；3、和s；4、存放和s个数的数组
void Probability(int n, int current, int sum, int* pProbabilities)
{
	//如果只计算一个骰子，那就直接在传过来的当前的sum上的对应个数上加1
	//为什么？这其实就是表示第二个堆n-1的sum已经计算完了
	if (current == 1)
		pProbabilities[sum - n]++;
	else
		for (int i = 1; i <= MAX_VALUE; i++)
			//sum+i是第一个堆和第二个堆的第一堆的点数的和，接下来要计算第一个堆的第二个堆
			Probability(n, current - 1, sum + i, pProbabilities);
}

//基于循环的计算n个骰子和为s出现的概率
void PrintProbability(int n)
{
	if (n < 1)
		return;
	int* pProbabilities[2];	//定义两个数组
	//分别给两个数组指定大小，又是带参数
	pProbabilities[0] = new int[MAX_VALUE*n - n + 1];
	pProbabilities[1] = new int[MAX_VALUE*n - n + 1];
	//又是一个赋值的过程，突然想到，就好像int i=0;一样，如果不给i赋初始值，那就不能拿i进行计算
	for (int i = 0; i < MAX_VALUE*n - n + 1; i++) {
		pProbabilities[0][i] = 0;
		pProbabilities[1][i] = 0;
	}

	int flag = 0;
	//只有一个骰子的时候，出现的可能sum=1~6
	for (int i = 1; i <= MAX_VALUE; i++)
		pProbabilities[flag][i] = 1;
	//从有两个骰子开始使用循环计算
	for (int k = 2; k <= n; k++) {
		for (int i = 0; i < k; i++)
			pProbabilities[1 - flag][i] = 0;
		//当前计算的是有k个骰子，所以一共s的范围是k~6*k
		//每次循环计算中i表示的是和sum
		for (int i = k; i <= MAX_VALUE * k; i++) {
			pProbabilities[1 - flag][i] = 0;
			//j<=i限制是因为有可能和i在2~6之间，就意味着骰子数在2~6（每个骰子都为1的时候）之间
			//所以计算下一个s的个数的时候根本就没有需要加所谓的前6个，因为前面没有6个
			//比如当骰子数k=2计算和i=3的个数的时候那就只需要加上前一轮的i-1、i-2，也就是只有一个骰子，sum=1、2的时候
			for (int j = 1; j <= i && j <= MAX_VALUE; j++)
				pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
		}
		flag = flag - 1;	//两个数组角色互换，之后进入下一轮计算
	}//到这里就已经计算完了

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
	
