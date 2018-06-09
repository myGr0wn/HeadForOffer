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

//�ҵ���һ��1��λ�ã��ô�ͳ������
unsigned int FindFirstBitIs1(int n)
{
	int indexBit = 0;
	while (((n & 1) == 0) && (indexBit < 8 * sizeof(int))) {
		n = n >> 1;
		indexBit++;
	}
}
//�жϵ�indexBitλ�ǲ���1
bool isBit(int num, unsigned int indexBit)
{
	num = num >> indexBit;//����һ��1��λ���Ƶ����ұ�
	return (num & 1);
}
//num1��num2�Ƿ��ص�����ֻ����һ�ε�����,��Ϊ���ܷ�����������ֻ���ô��εķ�ʽ����
void FindAppearOnce(int data[], int length, int* num1, int* num2)
{
	if (data == nullptr || length == 0)//�ж������Ƿ�����Լ����ڵĻ��Ƿ��ǿ�����
		return;

	int resultExclusiveOR = 0;
	for (int i = 0; i < length; i++)
		resultExclusiveOR ^= data[i];	//^������
	unsigned int indexOf1 = FindFirstBitIs1(resultExclusiveOR);
	*num1 = 0;
	*num2 = 0;
	//û��������Ϊ���������飬ֻ�ǽ����жϣ�֮��ѡ����ʽ����
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
	int bitSum[32] = { 0 };//�����е�ÿһλ����0
	for (int i = 0; i < length; i++)
	{
		int bitMask = 1;
		for (int j = 31; j >= 0; j--) {//�����ұ���һλ��ʼ������������ÿһλ�ĺ�
			int bit = data[j] & bitMask;
			if (bit != 0)
				bitSum[j]++;
			bitMask = bitMask << 1;
		}
	}
	int result = 0;//result��������¼ÿ�μ��㲢�¼ӡ���λ��õ��Ľ��
	for (int i = 0; i < 32; i++) {//���������һλ���λ��ʼ�������ս��
		result = result << 1;	
		//����һ��result�����һλ����0�����Բ������ȼ�����λ
		//��Ϊ���һ����ʱ���ʹ�ý����ԭ�����������һλ
		result += bitSum[i] % 3;
	}
	return result;
}

int AddWithBit(int num1, int num2)
{
	int sum, carry;
	//ΪʲôҪʹ��ѭ������ΪҪ����λ����
	//������ӡ�������������õ���һ���ķ�����ֱ��û�н�λΪֹ
	//����һ�¸�ѧ�ӷ�ʱ����ͼ��������
	do {
		sum = num1 ^ num2;
		carry = (num1&num2) << 1;//��λ��ֻ��11����Ҫ��λ���������ʹ����&����
		num1 = sum;
		num2 = carry;
	} while (num2 != 0);
	return sum;
}