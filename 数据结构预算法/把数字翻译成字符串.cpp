#include<string>
#include<iostream>
using std::string;

int GetTranslationCount(int number)
{
	if (number < 0)
		return 0;
	string numberInString = std::to_string(number);
	return GetTranslationCount(numberInString);
}
//���أ��������ַ���
int GetTranslationCount(const string& number)
{
	int length = number.length();
	//���ڴ�ŵ�i�����ֿ�ʼ�ķ���������
	int* counts = new int[length];	
	int count = 0;
	for (int i = length - 1; i >= 0; i--) {
		count = 0;
		//��������һ�����֣���ôֻ��һ�ַ���
		//����������һ�����֣���ô�������������Ҫ����������֣�����123����Ҫ��23
		if (i < length - 1)
			count = counts[i + 1];
		else count = 1;

		if (i < length - 1) {
			//������ʵ�ǽ��ַ���ת��Ϊint
			int digit1 = number[i] - '0';
			int digit2 = number[i + 1] - '0';
			int coverted = digit1 * 10 + digit2;
			//����ͺ�һ��������ϸպ��ڷ�Χ�ڣ��Ǿ�Ҫ���Ϻ�һ������֮���������
			//����2558��25����Ҫ���Ǿ�Ҫ��58����ɵ�������
			if (coverted >= 10 && coverted <= 25) {
				if (i < length - 2)
					count += counts[i + 2];
				else
					count += 1;
			}
		}
	}
}