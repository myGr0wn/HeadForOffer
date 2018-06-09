#include<iostream>
#include<stack>

struct ListNode
{
	int value;
	ListNode* nextNode;
};

//找到两个链表相同的节点，重要的是要知道指针和内存的关系（指针与数组的区别）
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	//遍历两个链表，分别得到链表的长度
	unsigned int len1 = GetListLen(pHead1);
	unsigned int len2 = GetListLen(pHead2);
	//直接假设len1>=len2
	int subLen = len1 - len2;
	ListNode* pLongList = pHead1;
	ListNode* pShortList = pHead2;
	//还是得进行比较，但只关注一种情况，因为前面已经有其他情况的处理方法了
	if (len2 > len1) {
		pLongList = pHead2;
		pShortList = pHead1;
		subLen = len2 - len1;
	}
	//先让长链表走subLen步
	for (int i = 0; i < subLen; i++)
		pLongList = pLongList->nextNode;
	//之后再一起走，然后比较，因为到达第一个相同节点需要走的步数是一样的。都是在链表的倒数
	while ((pLongList != nullptr) && (pShortList != nullptr) && (pLongList->value != pShortList->value)) {
		pLongList = pLongList->nextNode;
		pShortList = pShortList->nextNode;
	}
	return pLongList;
}
//计算链表的长度
unsigned int GetListLen(ListNode* pHead)
{
	unsigned int len = 0;
	//我在想，这里为什么要定义一个新的指针，不可以直接用传入来的参数吗？反正传进来的头指针指向的内存位置还是不会变的，而且这里面又没有改变到值的地方
	//后面再仔细想想，虽然头指针指向的节点的内存不变，而且也没有改变value的地方，但是同样作为元素，nextNode也是元素，这里有改变到节点nextNode的地方，所以。。
	ListNode* pNode = pHead;		
	while (pNode!=nullptr)
	{
		len++;
		pNode = pNode->nextNode;
	}
	return len;
}

//合并链表
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == nullptr)		//链表1是空链表
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

//反转链表
ListNode* ReverseList(ListNode* pHead)
{
	ListNode* pNewHead = nullptr;	//每次反转后的新的链表的头（可能时临时的），这一次的当前节点
	ListNode* pNode = pHead;	
	ListNode* pPreNode = nullptr;	//上一次的当前节点，这一次的上一个节点

	while (pNode != nullptr) {
		ListNode* pNext = pNode->nextNode;//保存下一个节点
		if (pNext == nullptr)	//不是原链表的尾节点
			pNewHead = pNode;	//新的头就是当前节点
		pNode->nextNode = pPreNode;		//当前节点的nextNode改了，这是目的
		pPreNode = pNode;	//完成指向修改任务后就可以为下一轮做准备了
		pNode = pNext;	//使用之前保存好的下一个节点
	}
	return pNewHead;
}

//查找链表倒数第k个节点
ListNode* FindKthToTail(ListNode* pHead, unsigned int k)
{
	ListNode* phead1=pHead;	//走在前面的指针
	ListNode* phead2 = nullptr;	//走在后面的指针

	for (unsigned int i = 0; i < k - 1; i++)
		phead1 = phead1->nextNode;	//走k-1步
	
	phead2 = pHead;
	while (phead1 != nullptr) {
		phead1 = phead1->nextNode;
		phead2 = phead2->nextNode;
	}
	return phead2;
}

//删除链表中重复的节点
void DeleteDuplication(ListNode** pHead)
{//没有这个链表或者是空链表
	if (pHead == nullptr || *pHead == nullptr)
		return;

	ListNode* pPreNode = nullptr;
	ListNode* pNode = *pHead;
	while (pNode != nullptr) {
		ListNode* pNext = pNode->nextNode;
		bool needDelete = false;
		if (pNext != nullptr&& pNext->value == pNode->value) 
			needDelete = true;
		if (!needDelete) {	//不是重复的点，进行新的赋值，进入下一个循环
			pPreNode = pNode;
			pNode = pNode->nextNode;
		}
		else {	//是重复的点
			int value = pNode->value;//记录重复的值
			ListNode* pToBeDelete = pNode;	//记录需要被删除的节点，至少有当前节点和下一个节点
			while (pToBeDelete!=nullptr&&pToBeDelete->value==value)
			{
				pNext = pToBeDelete->nextNode;
				delete pToBeDelete;
				pToBeDelete = nullptr;
				pToBeDelete = pNext;	//可能删掉的节点后面的节点的value和被删掉的节点的value一样
			}
			if (pPreNode == nullptr)//第一个节点开始就是需要被删除的点，比较特殊
				*pHead = pNext;
			else
				pPreNode->nextNode = pNext;//被删掉的节点的下一个节点
		}
	}
}

//删除节点
void DeleteNode(ListNode** pHead, ListNode* pToBeDelete)
{
	if (!pHead || !pToBeDelete)
		return;
	//要删除的不是末尾节点
	if (pToBeDelete != nullptr) {
		ListNode* pNext = pToBeDelete->nextNode;
		pToBeDelete->value = pNext->value;
		pToBeDelete->nextNode = pNext->nextNode;

		delete pNext;
		pNext = nullptr;
	}
	//链表只剩一个节点，删除头节点（也是尾节点）
	else if (pToBeDelete == *pHead) {
		delete pToBeDelete;
		pToBeDelete = nullptr;
		*pHead = nullptr;
	}
	else {//链表中有多个节点，并且删除的是尾节点
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
	//c++原来还有stack这东西，孤陋寡闻，在下面得熟悉一波
	//stack这简直太方便了，之前还一直自己写栈。
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
	pNew->nextNode = nullptr;	//因为是插在末尾
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
{	//头指针是空的或者根本就没有这个链表存在
	if (pHead == nullptr || *pHead == nullptr)
		return;
	//之后要释放这个内存空间，所以要记录起来位置
	ListNode* pToBeDeleted = nullptr;
	//把头节点单独拎出来说，因为头节点没有前向指针
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
