bool match(char* str, char* pattern)
{
	if (str == nullptr || pattern == nullptr)
		return false;
	//因为核心的部分是一个递归的过程，所以还是得写两个函数
	return matchCore(str, pattern);
}

bool matchCore(char* str, char* pattern)
{
	//递归退出的条件，模式和字符串都已经到尾部了
	if (*str == '\0' && *pattern == '\0')
		return true;
	//为什么？那如果模式还没完，但是字符串已经完了呢？
	if (*str != '\0'&& *pattern == '\0')
		return false;
	//第二个字符是*的情况
	if (*(pattern + 1) == '*') {
		if (*pattern == *str || (*pattern == '.'&&*str != '\0'))//&&比||优先级高
			//这里是刚好前面一个字符匹配，紧紧跟着的那个字符也匹配【很nice的情况，指匹配一个字符，类似于a*bcd<==>abcd】
			return matchCore(str + 1, pattern + 2)
			//那种情况不成立，那就继续看这里，因为*可以匹配任意长度的字符串，所以str就可以继续往后走啦，类似于.*bcd<==>asfsdbcd
			|| matchCore(str + 1, pattern)
			//第二种情况再不成立才会到这里
			|| matchCore(str, pattern + 2);
		else
			return matchCore(str, pattern + 2);//竟然第一个都不匹配，那就当他*是0匹配，直接进入下一个匹配
	}
	if (*pattern == *str || (*pattern == '.'&&*str != '\0'))
		return matchCore(str + 1, pattern + 1);

	return false;
}

//表示数值的字符串
//str是一个字符串，指向第一个字符
bool isNumberic(const char* str)
{
	if (str == nullptr)
		return false;//字符串是空的就很开心了，完全不用判断
	//为什么是引用？这样当函数调用结束时，str指向的字符串也跟着往后移动了
	bool numeric=scanInteger(&str);
	//如果出现'.'，则开始小数部分的匹配
	if (*str == '.') {
		++str;
		//下面一行代码用||的原因
		//①小数可以没有整数部分
		//②小数点后面可以没有数字
		//③小数点前面和后面都可以有数字。也就是说唯一不可以出现的就是小数点前面和后面都没有数字
		numeric = scanIntegerUnsigned(&str) || numeric;
	}
	//如果出现字符'e''E'，则接下来匹配指数部分
	if (*str == 'e' || *str == 'E') {
		++str;
		//下面一行代码用&&的原因
		//①当e或E前面没有数字时，整个字符串不能为数字，如.e1,e1
		//②当e或E后面没有整数时，也不符合，如12E,12e4.8
		//也就是说，出现了E，那前面就必须有数值，后面必须是整数
		numeric = scanInteger(&str) && numeric;
	}
	return numeric && *str == '\0';
}
//扫描连续的数位串，包括+ -
//str是指向一个字符串的指针
bool scanInteger(const char** str)
{
	if (**str == '+' || **str == '-')
		++(*str);//指向字符串下一个字符
	return scanIntegerUnsigned(str);
}
//用来匹配B部分
bool scanIntegerUnsigned(const char** str)
{
	const char* before = *str;
	//在数值0~9之间
	while (**str != '\0'&&**str >= '0'&&**str <= '9')
		(*str)++;
	//当存在若干数值0~9时返回true，此时的*str指向的是一个不为数值的字符
	return *str > before;
}

