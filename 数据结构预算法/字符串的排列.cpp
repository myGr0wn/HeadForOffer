#include<iostream>
using std::cout;

void Permutation(char* pStr)
{
	if (pStr == nullptr)
		return;
	Permutation(pStr, pStr);
}

void Permutation(char* pStr, char* pBegin)
{
	if (*pBegin == '\0')//存在，但为空串，没有被赋值（默认）
		cout << pStr;
	else
		for (char* pCh = pBegin; *pCh != '\0'; pCh++) {
			char temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;

			Permutation(pStr, pBegin + 1);
			//还原回来，准备与下一个字符交换，不然下一次与下一个字符交换的就不是原来那个*pBegin字符了
			temp = *pCh;
			*pCh = *pBegin;
			*pBegin = temp;
		}
}

bool PermutationInt(int* pInt,int length)
{
	if (pInt == nullptr || length!=8)
		return;
	return PermutationInt(pInt, pInt,1);
}
bool PermutationInt(int* pInt, int* pBegin,int order)
{
	bool isFix = false;
	if (order == 8)
		isFix = isOK(pInt);
	else
		for (int* pInt= pBegin,int pNum=order; pNum != 8; pNum++,pInt++) {
			int temp = *pInt;
			*pInt = *pBegin;
			*pBegin = temp;

			isFix=PermutationInt(pInt, pBegin + 1, pNum + 1);
			
			temp = *pInt;
			*pInt = *pBegin;
			*pBegin = temp;
		}
	return isFix;
}

bool isOK(int* pInt)
{
	return pInt[0] + pInt[1] + pInt[2] + pInt[3] == pInt[4] + pInt[5] + pInt[6] + pInt[7]
		&& pInt[0] + pInt[1] + pInt[4] + pInt[5] == pInt[2] + pInt[3] + pInt[6] + pInt[7]
		&& pInt[0] + pInt[2] + pInt[4] + pInt[7] == pInt[1] + pInt[3] + pInt[5] + pInt[6];
}