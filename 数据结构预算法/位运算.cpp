int NumberOf1(int n)
{
	int count = 0;
	unsigned int flag = 1;
	while (flag) {
		if (n&flag)
			count++;
		flag <<= 1;
	}
	return count;
}

int Count1(int n)
{
	int count = 0;
	while (n) {
		++count;
		n = (n - 1)&n;
	}
	return count;
}

//找到第一个1的位置，用传统的做法
unsigned int FindFirstBitIs1(int n)
{
	int indexBit = 0;
	while (((n & 1) == 0) && (indexBit < 8 * sizeof(int))) {
		n = n >> 1;
		indexBit++;
	}
}
//判断第indexBit位是不是1
bool isBit(int num, unsigned int indexBit)
{
	num = num >> indexBit;//将第一个1的位置移到最右边
	return (num & 1);
}
//num1，num2是返回的两个只出现一次的数字,因为不能返回两个数，只能用传参的方式返回
void FindAppearOnce(int data[], int length, int* num1, int* num2)
{
	if (data == nullptr || length == 0)//判断数组是否存在以及存在的话是否是空数组
		return;

	int resultExclusiveOR = 0;
	for (int i = 0; i < length; i++)
		resultExclusiveOR ^= data[i];	//^异或符号
	unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);
	*num1 = 0;
	*num2 = 0;
	//没有真正分为两个子数组，只是进行判断，之后选择处理方式而已
	for (int i = 0; i < length; i++) {
		if (isBit(data[i], indexOf1))
			*num1 ^= data[i];
		else
			*num2 ^= data[i];
	}
}

#include<exception>
int FindAppearOnceOf3(int data[], int length)
{
	if (data == nullptr || length == 0)
		throw new std::exception("Invalid input!");
	int bitSum[32] = { 0 };//数组中的每一位都是0
	for (int i = 0; i < length; i++)
	{
		int bitMask = 1;
		for (int j = 31; j >= 0; j--) {//从最右边那一位开始，计算所有数每一位的和
			int bit = data[j] & bitMask;
			if (bit != 0)
				bitSum[j]++;
			bitMask = bitMask << 1;
		}
	}
	int result = 0;//result是用来记录每次计算并新加、移位后得到的结果
	for (int i = 0; i < 32; i++) {//从最左边那一位最高位开始计算最终结果
		result = result << 1;	
		//到这一步result的最后一位总是0，所以不可以先加再移位
		//因为最后一步的时候会使得结果比原来结果多移了一位
		result += bitSum[i] % 3;
	}
	return result;
}

int AddWithBit(int num1, int num2)
{
	int sum, carry;
	//为什么要使用循环，因为要将进位加上
	//这个“加”和两个数相加用的是一样的方法，直到没有进位为止
	//想象一下刚学加法时画的图做的运算
	do {
		sum = num1 ^ num2;
		carry = (num1&num2) << 1;//进位，只有11才需要进位，所以这个使用与&运算
		num1 = sum;
		num2 = carry;
	} while (num2 != 0);
	return sum;
}