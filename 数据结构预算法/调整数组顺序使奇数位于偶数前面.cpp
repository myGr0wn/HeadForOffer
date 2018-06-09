void ReorderOddEven(int* pData, unsigned int length)
{
	//不存在该数组，或者为空数组
	if (pData == nullptr || length == 0)
		return;
	int *pBegin = pData;
	int *pEnd = pData + length - 1;
	while (pBegin < pEnd) {
		//向后移动前面的指针，直到它指向偶数
		while (pBegin < pEnd && (*pBegin & 0x1) != 0)//奇数
			pBegin++;
		//向前移动后面的指针，直到它指向奇数
		while (pBegin < pEnd && (*pEnd & 0x1) == 0)//偶数
			pEnd--;

		if (pBegin < pEnd) {
			int temp=*pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

//问题的扩展，代码的可重用性
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

//使用上面的代码进行就划分。其实只要改变isEven这个参数就可以进行其他分类了，最终还是回归到isEvent一行代码
void OddEven(int *pData, unsigned int length)
{
	Reorder(pData, length, isEven);
}

bool isEven(int number) {
	return (number & 1) == 0;
}