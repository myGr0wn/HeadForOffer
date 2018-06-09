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
	pCurrentNode->leftNode = *pLastNode;	//因为一直递归进去，所以其实第一个使用值为10的pLastNode的是左边的最下面的一个节点
	if (*pLastNode != nullptr)
		(*pLastNode)->rightNode = pCurrentNode;	//左子树的最后一个节点的右指针为（子树）其根节点
	
	*pLastNode = pCurrentNode;//现在最后一个节点是根节点了
	if (pCurrentNode->rightNode != nullptr)
		ConvertNode(pCurrentNode->rightNode, pLastNode);
}

BinaryNode* Convert(BinaryNode* rootNode)
{
	BinaryNode* pLastNode = nullptr;
	ConvertNode(rootNode, &pLastNode);	//注意与参数进行比较

	BinaryNode* pHeadList = pLastNode;
	while (pHeadList != nullptr && pHeadList->leftNode != nullptr)
		pHeadList = pHeadList->leftNode;
	return pHeadList;
}