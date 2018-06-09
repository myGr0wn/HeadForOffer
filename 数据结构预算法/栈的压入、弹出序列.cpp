#include<stack>
using std::stack;
//pPush��ѹ�����У�pPop�ǵ�������
bool isPopOrder(const int* pPush, const int* pPop, int nLength)
{
	bool isPossible = false;
	//���ѹ�����л��ߵ������в����ڣ��Ǿ�����������ˣ��Ͳ���Ҫ���в�����
	if (pPush != nullptr&&pPop != nullptr&&nLength > 0)
	{
		const int* pNextPush = pPush;
		const int* pNextPop = pPop;
		stack<int> stackData;
		
		while (pNextPop - pPop < nLength)//����û��ջ������
		{
			//ջ�ջ���ջ��������һ������������ֱ����ѹ�����������һ������������ֹͣѹջ
			while (stackData.empty() || stackData.top() != *pNextPop)
			{
				//����ѹջ
				if (pNextPush - pPush == nLength)//�������ֶ��Ѿ�ѹ��ջ��
					break;
				stackData.push(*pNextPush);//ѹ��ѹջ�����е���һ������
				pNextPush++;
			}
			if (stackData.top() != *pNextPop)//����while
				break;
			stackData.pop();
			pNextPop++;	//׼����������һ������
		}
		if (stackData.empty() && pNextPop - pPop == nLength)//�������������ˣ�ջҲΪ���ˣ�˵��������������д��ڵ�
			//���ջ�л������֣�Ϊʲô���У�����ѹ��ȥ������ʱ����������
			isPossible = true;
	}
	return isPossible;
}