#include<iostream>

struct ComplexListNode
{
	int value;
	ComplexListNode* nextNode;
	ComplexListNode* siblingNode;
};

//第一步：复制构成长链表
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

//第二步：设置克隆点的siblingNode指针
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

//第三步：奇偶节点分别连接
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