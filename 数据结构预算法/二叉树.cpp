struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* leftNode;
	BinaryTreeNode* rightNode;
};
void MirrorRecusively(BinaryTreeNode* pNode)
{
	if (pNode == nullptr)
		return;
	if (pNode->leftNode == nullptr&&pNode->rightNode == nullptr)//ֻ��һ���ڵ��������˵������Ҷ�ڵ�
		return;
	BinaryTreeNode* pTemp = pNode->leftNode;
	pNode->leftNode = pNode->rightNode;
	pNode->rightNode = pTemp;
	if (pNode->leftNode != nullptr)
		MirrorRecusively(pNode->leftNode);
	if (pNode->rightNode != nullptr)
		MirrorRecusively(pNode->rightNode);
}

bool isSymmertrical(BinaryTreeNode* pRoot)
{
	return isSymmertrical(pRoot, pRoot);
}
//pRoot1��ǰ�������һ�α����Ľڵ㣬pRoot2���µ�ǰ�������һ�α����Ľڵ�
bool isSymmertrical(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot1 == nullptr&&pRoot2 == nullptr)
		return true;
	if (pRoot1 == nullptr || pRoot2 == nullptr)//����һ���Ѿ����������ˣ��϶����Գ�
		return false;
	if (pRoot1->value != pRoot2->value)
		return false;
	return isSymmertrical(pRoot1->leftNode, pRoot2->rightNode) && 
		isSymmertrical(pRoot1->rightNode, pRoot2->leftNode);
}