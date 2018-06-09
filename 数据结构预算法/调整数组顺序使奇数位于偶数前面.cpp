void ReorderOddEven(int* pData, unsigned int length)
{
	//�����ڸ����飬����Ϊ������
	if (pData == nullptr || length == 0)
		return;
	int *pBegin = pData;
	int *pEnd = pData + length - 1;
	while (pBegin < pEnd) {
		//����ƶ�ǰ���ָ�룬ֱ����ָ��ż��
		while (pBegin < pEnd && (*pBegin & 0x1) != 0)//����
			pBegin++;
		//��ǰ�ƶ������ָ�룬ֱ����ָ������
		while (pBegin < pEnd && (*pEnd & 0x1) == 0)//ż��
			pEnd--;

		if (pBegin < pEnd) {
			int temp=*pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

//�������չ������Ŀ�������
void Reorder(int* pData, unsigned int length, bool(*fun)(int))
{
	if (pData == nullptr || length == 0)
		return;

	int *pBegin = pData;
	int *pEnd = pData + length - 1;
	while (pBegin < pEnd) {
		while (pBegin < pEnd && !fun(*pBegin))
			pBegin++;
		while (pBegin < pEnd&&fun(*pEnd))
			pEnd;
		if (pBegin < pEnd) {
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

//ʹ������Ĵ�����оͻ��֡���ʵֻҪ�ı�isEven��������Ϳ��Խ������������ˣ����ջ��ǻع鵽isEventһ�д���
void OddEven(int *pData, unsigned int length)
{
	Reorder(pData, length, isEven);
}

bool isEven(int number) {
	return (number & 1) == 0;
}