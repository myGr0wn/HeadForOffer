struct BinaryNode
{
	int value;
	BinaryNode* leftNode;
	BinaryNode* rightNode;
};

void ConvertNode(BinaryNode* pNode, BinaryNode** pLastNode)
{
	if (pNode == nullptr)
		return;
	BinaryNode* pCurrentNode = pNode;
	if (pCurrentNode->leftNode != nullptr)
		ConvertNode(pCurrentNode->leftNode, pLastNode);
	pCurrentNode->leftNode = *pLastNode;	//��Ϊһֱ�ݹ��ȥ��������ʵ��һ��ʹ��ֵΪ10��pLastNode������ߵ��������һ���ڵ�
	if (*pLastNode != nullptr)
		(*pLastNode)->rightNode = pCurrentNode;	//�����������һ���ڵ����ָ��Ϊ������������ڵ�
	
	*pLastNode = pCurrentNode;//�������һ���ڵ��Ǹ��ڵ���
	if (pCurrentNode->rightNode != nullptr)
		ConvertNode(pCurrentNode->rightNode, pLastNode);
}

BinaryNode* Convert(BinaryNode* rootNode)
{
	BinaryNode* pLastNode = nullptr;
	ConvertNode(rootNode, &pLastNode);	//ע����������бȽ�

	BinaryNode* pHeadList = pLastNode;
	while (pHeadList != nullptr && pHeadList->leftNode != nullptr)
		pHeadList = pHeadList->leftNode;
	return pHeadList;
}