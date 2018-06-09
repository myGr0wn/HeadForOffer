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
//重载，参数是字符串
int GetTranslationCount(const string& number)
{
	int length = number.length();
	//用于存放第i个数字开始的翻译种类数
	int* counts = new int[length];	
	int count = 0;
	for (int i = length - 1; i >= 0; i--) {
		count = 0;
		//如果是最后一个数字，那么只有一种翻译
		//如果不是最后一个数字，那么翻译的种类数就要看后面的数字，比如123，就要看23
		if (i < length - 1)
			count = counts[i + 1];
		else count = 1;

		if (i < length - 1) {
			//这里其实是将字符串转换为int
			int digit1 = number[i] - '0';
			int digit2 = number[i + 1] - '0';
			int coverted = digit1 * 10 + digit2;
			//如果和后一个数字组合刚好在范围内，那就要加上后一个数字之后的种类书
			//比如2558，25符合要求，那就要看58能组成的种类数
			if (coverted >= 10 && coverted <= 25) {
				if (i < length - 2)
					count += counts[i + 2];
				else
					count += 1;
			}
		}
	}
}