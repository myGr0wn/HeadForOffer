#include<string>
using std::string;

int longestSubstringWithoutDuplication(const string& str)
{
	int curLength = 0;
	int maxLength = 0;
	int* position = new int[26];//��¼�ַ�������ֵ�λ��
	for (int i = 0; i < 26; i++)
		position[i] = -1;
	for (int i = 0; i < str.length(); i++)
	{
		int prevIndex = position[str[i] - 'a'];
		//����ǵ�һ�γ��ֻ����ڵ�ǰ���ַ���֮�����
		if (prevIndex<0 || i - prevIndex>curLength)
			++curLength;
		//����Ǹպ��ڵ�ǰ�ַ�����
		else {
			//�Ǿ�Ҫ�ȱ��浱ǰ�����ˣ�Ҫ��ȻҪ�Ե�ǰ�����ַ������в�����
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