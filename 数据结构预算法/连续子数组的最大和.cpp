//ʹ��һ��ȫ�ֱ�������������Ƿ���Ч
bool g_InvalidInput = false;//false��ʾ�ϸ�
//���������ĺ�
int FindGreatestSumOfArray(int* pData, int nLength)
{
	if (pData == nullptr || nLength <= 0)//���ϸ�����
	{
		g_InvalidInput = true;
		return 0;
	}
	g_InvalidInput = false;
	int nCurrentSum = 0;
	int nGreatestSum = 0x80000000;//����ô���£�����
	for (int i = 0; i < nLength; i++) {
		if (nCurrentSum <= 0)//ֻҪ��С��0������֮ǰ���ۼ�
			nCurrentSum = pData[i];
		else
			nCurrentSum += pData[i];

		if (nCurrentSum > nGreatestSum)
			nGreatestSum = nCurrentSum;
	}
	return nGreatestSum;
}