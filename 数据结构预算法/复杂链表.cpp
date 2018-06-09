#include<iostream>

struct ComplexListNode
{
	int value;
	ComplexListNode* nextNode;
	ComplexListNode* siblingNode;
};

//��һ�������ƹ��ɳ�����
void CloneNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr) {
		ComplexListNode* pClone = new ComplexListNode();
		pClone->value = pNode->value;
		pClone->nextNode = pNode->nextNode;
		pNode->nextNode = pClone;
		pClone->siblingNode = nullptr;

		pNode = pClone->nextNode;
	}
}

//�ڶ��������ÿ�¡���siblingNodeָ��
void ConnectSiblingNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	while (pNode != nullptr) {
		ComplexListNode* pClone = pNode->nextNode;
		if (pNode->siblingNode != nullptr)
			pClone->siblingNode = pNode->siblingNode->nextNode;
		pNode = pNode->nextNode;
	}
}

//����������ż�ڵ�ֱ�����
ComplexListNode* ReconnectNodes(ComplexListNode* pHead)
{
	ComplexListNode* pNode = pHead;
	ComplexListNode* pCloneHead = nullptr;
	ComplexListNode* pCloneNode = nullptr;

	if (pNode != nullptr) {
		pCloneNode = pNode->nextNode;
		pCloneHead = pNode->nextNode;
		pNode->nextNode = pCloneHead->nextNode;
		pNode = pNode->nextNode;
	}

	while (pNode != nullptr) {
		pCloneNode->nextNode = pNode->nextNode;
		pCloneNode = pCloneNode->nextNode;
		pNode->nextNode = pCloneNode->nextNode;
		pNode = pNode->nextNode;
	}
	return pCloneHead;
}

ComplexListNode* Clone(ComplexListNode* pHead)
{
	CloneNodes(pHead);
	ConnectSiblingNodes(pHead);
	return ReconnectNodes(pHead);
}