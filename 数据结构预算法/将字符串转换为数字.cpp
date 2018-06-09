//ö��
//ȫ�ֱ�����־����ĺϷ���
enum Status { kValid = 0, kInvalid };
int g_nStatus = kValid;

int StrToInt(const char* str)
{
	g_nStatus = kInvalid;
	long long num = 0;
	
	//�ַ������ܲ����ڣ�Ҳ�����ǿ��ַ���
	if (str != nullptr&&*str != '\0')
	{
		//�п����ַ���ǰ��û��+����-
		//��־�Ƿ�Ϊ����-
		bool minus = false;
		if (*str == '+')
			str++;
		else if (*str == '-') {
			str++;
			minus = true;
		}
		//�����������ת�����֣�ǰ��֪ʶ�жϵ�һ���ַ��Ƿ�Ϊ����
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
		//�ж��Ƿ��ǺϷ�����0~9
		if (*digit >= '0'&&*digit <= '9') {
			int flag = minus ? -1 : 1;
			num = num * 10 + flag * (*digit - '0');
			//������������0x7FFFFFFF,��С�ĸ�������0x80000000
			//�ж��Ƿ����������
			if ((!minus&&num > 0x7FFFFFFF) || (minus&&num < (signed int)0x80000000))
			{
				//�������ˣ��ǾͿ��Խ�������while��
				num = 0;
				break;
			}
			digit++;
		}
		else {//�в������ֵ��ַ��������ַ�����
			num = 0;
			break;
		}
	}
	if (*digit == '\0')
		g_nStatus = kValid;
	return num;
}