bool match(char* str, char* pattern)
{
	if (str == nullptr || pattern == nullptr)
		return false;
	//��Ϊ���ĵĲ�����һ���ݹ�Ĺ��̣����Ի��ǵ�д��������
	return matchCore(str, pattern);
}

bool matchCore(char* str, char* pattern)
{
	//�ݹ��˳���������ģʽ���ַ������Ѿ���β����
	if (*str == '\0' && *pattern == '\0')
		return true;
	//Ϊʲô�������ģʽ��û�꣬�����ַ����Ѿ������أ�
	if (*str != '\0'&& *pattern == '\0')
		return false;
	//�ڶ����ַ���*�����
	if (*(pattern + 1) == '*') {
		if (*pattern == *str || (*pattern == '.'&&*str != '\0'))//&&��||���ȼ���
			//�����Ǹպ�ǰ��һ���ַ�ƥ�䣬�������ŵ��Ǹ��ַ�Ҳƥ�䡾��nice�������ָƥ��һ���ַ���������a*bcd<==>abcd��
			return matchCore(str + 1, pattern + 2)
			//����������������Ǿͼ����������Ϊ*����ƥ�����ⳤ�ȵ��ַ���������str�Ϳ��Լ�������������������.*bcd<==>asfsdbcd
			|| matchCore(str + 1, pattern)
			//�ڶ�������ٲ������Żᵽ����
			|| matchCore(str, pattern + 2);
		else
			return matchCore(str, pattern + 2);//��Ȼ��һ������ƥ�䣬�Ǿ͵���*��0ƥ�䣬ֱ�ӽ�����һ��ƥ��
	}
	if (*pattern == *str || (*pattern == '.'&&*str != '\0'))
		return matchCore(str + 1, pattern + 1);

	return false;
}

//��ʾ��ֵ���ַ���
//str��һ���ַ�����ָ���һ���ַ�
bool isNumberic(const char* str)
{
	if (str == nullptr)
		return false;//�ַ����ǿյľͺܿ����ˣ���ȫ�����ж�
	//Ϊʲô�����ã��������������ý���ʱ��strָ����ַ���Ҳ���������ƶ���
	bool numeric=scanInteger(&str);
	//�������'.'����ʼС�����ֵ�ƥ��
	if (*str == '.') {
		++str;
		//����һ�д�����||��ԭ��
		//��С������û����������
		//��С����������û������
		//��С����ǰ��ͺ��涼���������֡�Ҳ����˵Ψһ�����Գ��ֵľ���С����ǰ��ͺ��涼û������
		numeric = scanIntegerUnsigned(&str) || numeric;
	}
	//��������ַ�'e''E'���������ƥ��ָ������
	if (*str == 'e' || *str == 'E') {
		++str;
		//����һ�д�����&&��ԭ��
		//�ٵ�e��Eǰ��û������ʱ�������ַ�������Ϊ���֣���.e1,e1
		//�ڵ�e��E����û������ʱ��Ҳ�����ϣ���12E,12e4.8
		//Ҳ����˵��������E����ǰ��ͱ�������ֵ���������������
		numeric = scanInteger(&str) && numeric;
	}
	return numeric && *str == '\0';
}
//ɨ����������λ��������+ -
//str��ָ��һ���ַ�����ָ��
bool scanInteger(const char** str)
{
	if (**str == '+' || **str == '-')
		++(*str);//ָ���ַ�����һ���ַ�
	return scanIntegerUnsigned(str);
}
//����ƥ��B����
bool scanIntegerUnsigned(const char** str)
{
	const char* before = *str;
	//����ֵ0~9֮��
	while (**str != '\0'&&**str >= '0'&&**str <= '9')
		(*str)++;
	//������������ֵ0~9ʱ����true����ʱ��*strָ�����һ����Ϊ��ֵ���ַ�
	return *str > before;
}

