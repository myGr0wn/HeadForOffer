//使用一个全局变量来标记输入是否有效
bool g_InvalidInput = false;//false表示合格
//最大子数组的和
int FindGreatestSumOfArray(int* pData, int nLength)
{
	if (pData == nullptr || nLength <= 0)//不合格输入
	{
		g_InvalidInput = true;
		return 0;
	}
	g_InvalidInput = false;
	int nCurrentSum = 0;
	int nGreatestSum = 0x80000000;//？怎么回事？？？
	for (int i = 0; i < nLength; i++) {
		if (nCurrentSum <= 0)//只要是小于0就抛弃之前的累加
			nCurrentSum = pData[i];
		else
			nCurrentSum += pData[i];

		if (nCurrentSum > nGreatestSum)
			nGreatestSum = nCurrentSum;
	}
	return nGreatestSum;
}