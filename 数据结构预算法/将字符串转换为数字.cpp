//枚举
//全局变量标志输入的合法性
enum Status { kValid = 0, kInvalid };
int g_nStatus = kValid;

int StrToInt(const char* str)
{
	g_nStatus = kInvalid;
	long long num = 0;
	
	//字符串不能不存在，也不能是空字符串
	if (str != nullptr&&*str != '\0')
	{
		//有可能字符串前面没有+或者-
		//标志是否为负数-
		bool minus = false;
		if (*str == '+')
			str++;
		else if (*str == '-') {
			str++;
			minus = true;
		}
		//继续进入核心转换部分，前面知识判断第一个字符是否为符号
		if (*str != '\0')
			num = StrToIntCore(str, minus);
	}
	return (int)num;
}

long long StrToIntCore(const char* digit, bool minus)
{
	long long num = 0;
	while (*digit != '\0')
	{
		//判断是否是合法输入0~9
		if (*digit >= '0'&&*digit <= '9') {
			int flag = minus ? -1 : 1;
			num = num * 10 + flag * (*digit - '0');
			//最大的正整数是0x7FFFFFFF,最小的负整数是0x80000000
			//判断是否上溢或下溢
			if ((!minus&&num > 0x7FFFFFFF) || (minus&&num < (signed int)0x80000000))
			{
				//如果溢出了，那就可以结束本次while了
				num = 0;
				break;
			}
			digit++;
		}
		else {//有不是数字的字符出现在字符串中
			num = 0;
			break;
		}
	}
	if (*digit == '\0')
		g_nStatus = kValid;
	return num;
}