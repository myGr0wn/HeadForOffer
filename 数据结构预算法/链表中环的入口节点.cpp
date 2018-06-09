struct ListNode {
	int value;
	ListNode* nextNode;
};

//找出环中任意一个令两个指针相遇的节点
ListNode* MeetingNode(ListNode* pHead)
{
	if (pHead == nullptr)
		return nullptr;
	ListNode* pSlow = pHead->nextNode;
	if (pSlow == nullptr)//只有一个指针的链表
		return nullptr;

	ListNode* pFast = pSlow->nextNode;
	while (pFast != nullptr&&pSlow != nullptr) {
		if (pFast == pSlow)
			return pSlow;

		pSlow = pSlow->nextNode;
		pFast = pFast->nextNode;
		//每次循环如果不到末尾节点，快的指针就要比慢的指针多走一步
		if (pFast != nullptr)
			pFast = pFast->nextNode;
	}
	return nullptr;
}
//在上面找到能让两个指针相遇的节点之后，即找到了环中的任意一个节点
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	ListNode* meetingNode = MeetingNode(pHead);
	if (meetingNode == nullptr)
		return nullptr;
	//计算出环中节点的数目
	int nodesInLoop = 1;
	ListNode* pNode1 = meetingNode;//标记的节点
	while (pNode1->nextNode != meetingNode) {
		pNode1 = pNode1->nextNode;
		++nodesInLoop;//走过一个节点就加一个
	}
	//先移动pNode1,次数为上面数的环中的节点数
	pNode1 = pHead;
	for (int i = 0; i < nodesInLoop; i++)
		pNode1 = pNode1->nextNode;
	//开始同时移动两个节点,此时pNode1在pNode2前面了
	ListNode* pNode2 = pHead;
	while (pNode1 != pNode2) {
		pNode1 = pNode1->nextNode;
		pNode2 = pNode2->nextNode;
	}
	return pNode1;
}
