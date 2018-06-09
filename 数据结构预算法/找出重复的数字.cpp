#include<iostream>
#include<stack>

struct ListNode
{
	int value;
	ListNode* nextNode;
};

//�ҵ�����������ͬ�Ľڵ㣬��Ҫ����Ҫ֪��ָ����ڴ�Ĺ�ϵ��ָ�������������
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	//�������������ֱ�õ�����ĳ���
	unsigned int len1 = GetListLen(pHead1);
	unsigned int len2 = GetListLen(pHead2);
	//ֱ�Ӽ���len1>=len2
	int subLen = len1 - len2;
	ListNode* pLongList = pHead1;
	ListNode* pShortList = pHead2;
	//���ǵý��бȽϣ���ֻ��עһ���������Ϊǰ���Ѿ�����������Ĵ�������
	if (len2 > len1) {
		pLongList = pHead2;
		pShortList = pHead1;
		subLen = len2 - len1;
	}
	//���ó�������subLen��
	for (int i = 0; i < subLen; i++)
		pLongList = pLongList->nextNode;
	//֮����һ���ߣ�Ȼ��Ƚϣ���Ϊ�����һ����ͬ�ڵ���Ҫ�ߵĲ�����һ���ġ�����������ĵ���
	while ((pLongList != nullptr) && (pShortList != nullptr) && (pLongList->value != pShortList->value)) {
		pLongList = pLongList->nextNode;
		pShortList = pShortList->nextNode;
	}
	return pLongList;
}
//��������ĳ���
unsigned int GetListLen(ListNode* pHead)
{
	unsigned int len = 0;
	//�����룬����ΪʲôҪ����һ���µ�ָ�룬������ֱ���ô������Ĳ����𣿷�����������ͷָ��ָ����ڴ�λ�û��ǲ����ģ�������������û�иı䵽ֵ�ĵط�
	//��������ϸ���룬��Ȼͷָ��ָ��Ľڵ���ڴ治�䣬����Ҳû�иı�value�ĵط�������ͬ����ΪԪ�أ�nextNodeҲ��Ԫ�أ������иı䵽�ڵ�nextNode�ĵط������ԡ���
	ListNode* pNode = pHead;		
	while (pNode!=nullptr)
	{
		len++;
		pNode = pNode->nextNode;
	}
	return len;
}

//�ϲ�����
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == nullptr)		//����1�ǿ�����
		return pHead2;
	else if (pHead2 == nullptr)
		return pHead1;

	ListNode* pNewHead = nullptr;
	if (pHead1->value < pHead2->value) {
		pNewHead = pHead1;
		pNewHead->nextNode = Merge(pHead1->nextNode, pHead2->nextNode);
	}
	return pNewHead;
}

//��ת����
ListNode* ReverseList(ListNode* pHead)
{
	ListNode* pNewHead = nullptr;	//ÿ�η�ת����µ������ͷ������ʱ��ʱ�ģ�����һ�εĵ�ǰ�ڵ�
	ListNode* pNode = pHead;	
	ListNode* pPreNode = nullptr;	//��һ�εĵ�ǰ�ڵ㣬��һ�ε���һ���ڵ�

	while (pNode != nullptr) {
		ListNode* pNext = pNode->nextNode;//������һ���ڵ�
		if (pNext == nullptr)	//����ԭ�����β�ڵ�
			pNewHead = pNode;	//�µ�ͷ���ǵ�ǰ�ڵ�
		pNode->nextNode = pPreNode;		//��ǰ�ڵ��nextNode���ˣ�����Ŀ��
		pPreNode = pNode;	//���ָ���޸������Ϳ���Ϊ��һ����׼����
		pNode = pNext;	//ʹ��֮ǰ����õ���һ���ڵ�
	}
	return pNewHead;
}

//������������k���ڵ�
ListNode* FindKthToTail(ListNode* pHead, unsigned int k)
{
	ListNode* phead1=pHead;	//����ǰ���ָ��
	ListNode* phead2 = nullptr;	//���ں����ָ��

	for (unsigned int i = 0; i < k - 1; i++)
		phead1 = phead1->nextNode;	//��k-1��
	
	phead2 = pHead;
	while (phead1 != nullptr) {
		phead1 = phead1->nextNode;
		phead2 = phead2->nextNode;
	}
	return phead2;
}

//ɾ���������ظ��Ľڵ�
void DeleteDuplication(ListNode** pHead)
{//û�������������ǿ�����
	if (pHead == nullptr || *pHead == nullptr)
		return;

	ListNode* pPreNode = nullptr;
	ListNode* pNode = *pHead;
	while (pNode != nullptr) {
		ListNode* pNext = pNode->nextNode;
		bool needDelete = false;
		if (pNext != nullptr&& pNext->value == pNode->value) 
			needDelete = true;
		if (!needDelete) {	//�����ظ��ĵ㣬�����µĸ�ֵ��������һ��ѭ��
			pPreNode = pNode;
			pNode = pNode->nextNode;
		}
		else {	//���ظ��ĵ�
			int value = pNode->value;//��¼�ظ���ֵ
			ListNode* pToBeDelete = pNode;	//��¼��Ҫ��ɾ���Ľڵ㣬�����е�ǰ�ڵ����һ���ڵ�
			while (pToBeDelete!=nullptr&&pToBeDelete->value==value)
			{
				pNext = pToBeDelete->nextNode;
				delete pToBeDelete;
				pToBeDelete = nullptr;
				pToBeDelete = pNext;	//����ɾ���Ľڵ����Ľڵ��value�ͱ�ɾ���Ľڵ��valueһ��
			}
			if (pPreNode == nullptr)//��һ���ڵ㿪ʼ������Ҫ��ɾ���ĵ㣬�Ƚ�����
				*pHead = pNext;
			else
				pPreNode->nextNode = pNext;//��ɾ���Ľڵ����һ���ڵ�
		}
	}
}

//ɾ���ڵ�
void DeleteNode(ListNode** pHead, ListNode* pToBeDelete)
{
	if (!pHead || !pToBeDelete)
		return;
	//Ҫɾ���Ĳ���ĩβ�ڵ�
	if (pToBeDelete != nullptr) {
		ListNode* pNext = pToBeDelete->nextNode;
		pToBeDelete->value = pNext->value;
		pToBeDelete->nextNode = pNext->nextNode;

		delete pNext;
		pNext = nullptr;
	}
	//����ֻʣһ���ڵ㣬ɾ��ͷ�ڵ㣨Ҳ��β�ڵ㣩
	else if (pToBeDelete == *pHead) {
		delete pToBeDelete;
		pToBeDelete = nullptr;
		*pHead = nullptr;
	}
	else {//�������ж���ڵ㣬����ɾ������β�ڵ�
		ListNode* pNode = *pHead;
		while (pNode->nextNode != pToBeDelete)
			pNode = pNode->nextNode;

		pNode->nextNode = nullptr;
		delete pToBeDelete;
		pToBeDelete = nullptr;

	}
}

void PrintList(ListNode* pHead)
{
	if (pHead != nullptr) {
		if (pHead->nextNode != nullptr)
			PrintList(pHead->nextNode);
		std::cout << pHead->value;
	}
}

void PrintList1(ListNode* pHead)
{
	//c++ԭ������stack�ⶫ������ª���ţ����������Ϥһ��
	//stack���ֱ̫�����ˣ�֮ǰ��һֱ�Լ�дջ��
	std::stack<ListNode*> nodes;
	ListNode* pNode = pHead;
	while (pNode != nullptr) {
		nodes.push(pNode);
		pNode = pNode->nextNode;
	}
	while (!nodes.empty()) {
		pNode = nodes.top();
		std::cout << pNode->value;
		nodes.pop();
	}
}

void addToTail(ListNode **pHead, int value)
{
	ListNode* pNew = new ListNode();
	pNew->nextNode = nullptr;	//��Ϊ�ǲ���ĩβ
	pNew->value = value;

	if (pHead == nullptr)
		*pHead = pNew;
	else {
		ListNode* pNode = *pHead;
		while (pNode->nextNode != nullptr)
			pNode = pNode->nextNode;
		pNode->nextNode = pNew;
	}
}

void RemoveNode(ListNode **pHead, int value)
{	//ͷָ���ǿյĻ��߸�����û������������
	if (pHead == nullptr || *pHead == nullptr)
		return;
	//֮��Ҫ�ͷ�����ڴ�ռ䣬����Ҫ��¼����λ��
	ListNode* pToBeDeleted = nullptr;
	//��ͷ�ڵ㵥�������˵����Ϊͷ�ڵ�û��ǰ��ָ��
	if ((*pHead)->value == value) {
		pToBeDeleted = *pHead;
		*pHead = (*pHead)->nextNode;
	}
	else {
		ListNode* pNode = *pHead;
		while (pNode->nextNode != nullptr&&pNode->nextNode->value != value)
			pNode = pNode->nextNode;
		if (pNode->nextNode != nullptr) {
			pToBeDeleted = pNode->nextNode;
			pNode->nextNode = pNode->nextNode->nextNode;
		}
	}
	if (pToBeDeleted != nullptr)
	{
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
	}
}
