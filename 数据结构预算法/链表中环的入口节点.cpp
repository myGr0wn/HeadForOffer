struct ListNode {
	int value;
	ListNode* nextNode;
};

//�ҳ���������һ��������ָ�������Ľڵ�
ListNode* MeetingNode(ListNode* pHead)
{
	if (pHead == nullptr)
		return nullptr;
	ListNode* pSlow = pHead->nextNode;
	if (pSlow == nullptr)//ֻ��һ��ָ�������
		return nullptr;

	ListNode* pFast = pSlow->nextNode;
	while (pFast != nullptr&&pSlow != nullptr) {
		if (pFast == pSlow)
			return pSlow;

		pSlow = pSlow->nextNode;
		pFast = pFast->nextNode;
		//ÿ��ѭ���������ĩβ�ڵ㣬���ָ���Ҫ������ָ�����һ��
		if (pFast != nullptr)
			pFast = pFast->nextNode;
	}
	return nullptr;
}
//�������ҵ���������ָ�������Ľڵ�֮�󣬼��ҵ��˻��е�����һ���ڵ�
ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	ListNode* meetingNode = MeetingNode(pHead);
	if (meetingNode == nullptr)
		return nullptr;
	//��������нڵ����Ŀ
	int nodesInLoop = 1;
	ListNode* pNode1 = meetingNode;//��ǵĽڵ�
	while (pNode1->nextNode != meetingNode) {
		pNode1 = pNode1->nextNode;
		++nodesInLoop;//�߹�һ���ڵ�ͼ�һ��
	}
	//���ƶ�pNode1,����Ϊ�������Ļ��еĽڵ���
	pNode1 = pHead;
	for (int i = 0; i < nodesInLoop; i++)
		pNode1 = pNode1->nextNode;
	//��ʼͬʱ�ƶ������ڵ�,��ʱpNode1��pNode2ǰ����
	ListNode* pNode2 = pHead;
	while (pNode1 != pNode2) {
		pNode1 = pNode1->nextNode;
		pNode2 = pNode2->nextNode;
	}
	return pNode1;
}
