#include<stack>
using std::stack;
//pPush是压入序列，pPop是弹出序列
bool isPopOrder(const int* pPush, const int* pPop, int nLength)
{
	bool isPossible = false;
	//如果压入序列或者弹出序列不存在，那就是输入错误了，就不需要进行操作了
	if (pPush != nullptr&&pPop != nullptr&&nLength > 0)
	{
		const int* pNextPush = pPush;
		const int* pNextPop = pPop;
		stack<int> stackData;
		
		while (pNextPop - pPop < nLength)//还有没出栈的数字
		{
			//栈空或者栈顶不是下一个弹出的数，直到新压入的数字是下一个弹出的数，停止压栈
			while (stackData.empty() || stackData.top() != *pNextPop)
			{
				//继续压栈
				if (pNextPush - pPush == nLength)//所有数字都已经压入栈了
					break;
				stackData.push(*pNextPush);//压入压栈序列中的下一个数字
				pNextPush++;
			}
			if (stackData.top() != *pNextPop)//结束while
				break;
			stackData.pop();
			pNextPop++;	//准备弹出的下一个数字
		}
		if (stackData.empty() && pNextPop - pPop == nLength)//弹出的数字完了，栈也为空了，说明有这个弹出序列存在的
			//如果栈中还有数字？为什么不行？可以压进去但是暂时不弹出来？
			isPossible = true;
	}
	return isPossible;
}