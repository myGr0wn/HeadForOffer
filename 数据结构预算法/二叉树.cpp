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
	if (pNode->leftNode == nullptr&&pNode->rightNode == nullptr)//只有一个节点的树或者说是树的叶节点
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
//pRoot1是前序遍历这一次遍历的节点，pRoot2是新的前序遍历这一次遍历的节点
bool isSymmertrical(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot1 == nullptr&&pRoot2 == nullptr)
		return true;
	if (pRoot1 == nullptr || pRoot2 == nullptr)//其中一个已经遍历结束了，肯定不对称
		return false;
	if (pRoot1->value != pRoot2->value)
		return false;
	return isSymmertrical(pRoot1->leftNode, pRoot2->rightNode) && 
		isSymmertrical(pRoot1->rightNode, pRoot2->leftNode);
}