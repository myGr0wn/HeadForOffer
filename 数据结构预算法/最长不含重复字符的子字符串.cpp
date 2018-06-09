#include<string>
using std::string;

int longestSubstringWithoutDuplication(const string& str)
{
	int curLength = 0;
	int maxLength = 0;
	int* position = new int[26];//记录字符最近出现的位置
	for (int i = 0; i < 26; i++)
		position[i] = -1;
	for (int i = 0; i < str.length(); i++)
	{
		int prevIndex = position[str[i] - 'a'];
		//如果是第一次出现或者在当前子字符串之外出现
		if (prevIndex<0 || i - prevIndex>curLength)
			++curLength;
		//如果是刚好在当前字符串内
		else {
			//那就要先保存当前长度了，要不然要对当前的子字符串进行操作了
			if (curLength > maxLength)
				maxLength = curLength;
			curLength = i - prevIndex;//d
		}
		position[str[i] - 'a'] = i;
	}
	if (curLength > maxLength)
		maxLength = curLength;
	delete[] position;
	return maxLength;
}