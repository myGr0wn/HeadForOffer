#include<iostream>
#include<exception>
#include<vector>
using namespace std;

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* leftNode;
	BinaryTreeNode* rightNode;
};

//核心代码
BinaryTreeNode* ConstructCore(int* firstPreorder, int* lastPreorder,
	int* firstMidorder, int* lastMidorder)
{
	//在前序遍历序列中得到根节点
	int rootValue = firstPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->value = rootValue;
	root->leftNode = root->rightNode = nullptr;
	//只剩一个节点,子树就返回一个节点就可以了，不需要进行后面的操作
	if (firstPreorder==lastPreorder)
	{	
		if (firstMidorder == lastMidorder && *firstPreorder == *firstMidorder)
			return root;
		else
			throw std::exception("Invalid order");
	}
	//在中序遍历中找到根节点位置，从而区分左子树和右子树
	int* rootMidorder = firstMidorder;
	//找到根节点的位置
	while (rootMidorder <= lastMidorder && *rootMidorder != rootValue)
		++rootMidorder;
	if (rootMidorder == lastMidorder && *rootMidorder != rootValue)
		throw std::exception("Invalid input");
	//左子树的个数
	int leftLen = rootMidorder - firstMidorder;
	int *leftPreorderEnd = firstPreorder + leftLen;
	if (leftLen > 0)
		//构建左子树
		root->leftNode = ConstructCore(firstPreorder + 1, leftPreorderEnd, firstMidorder, rootMidorder - 1);
	if (leftLen < lastPreorder - firstPreorder)
		//构建右子树
		root->rightNode = ConstructCore(leftPreorderEnd + 1, lastPreorder, rootMidorder + 1, lastMidorder);

	return root;
}

//传入前序遍历序列和中序遍历序列以及序列的长度（是一样长的）
BinaryTreeNode* Construct(int* preorder, int* midorder, int length)
{
	if (preorder == nullptr || midorder == nullptr || length == 0)
		return nullptr;
	//传入前序遍历的第一个和最后一个数的指针，以及中序遍历的第一个数和最后一个数的指针
	return ConstructCore(preorder, preorder + length - 1, midorder, midorder + length - 1);
}

//拥有父节点的树
struct BinaryTreeParentNode
{
	int value;
	BinaryTreeParentNode* leftNode;
	BinaryTreeParentNode* rightNode;
	BinaryTreeParentNode* parentNode;
};

//从二叉树中找出一个节点的下一个节点
BinaryTreeParentNode* findNext(BinaryTreeParentNode* pNode)
{
	if (pNode == nullptr)
		return;

	BinaryTreeParentNode* pNext;
	//存在右节点==>下一个节点是其右子树的最左边的一个节点，顺着左节点一直走
	if (pNode->rightNode != nullptr) {
		BinaryTreeParentNode* rightNode = pNode->rightNode;
		while (rightNode->leftNode != nullptr)
			rightNode = rightNode->leftNode;
		pNext = rightNode;
	}//不存在右节点，但是该节点是其父节点的左节点==>下一个节点就是它的父节点
	//或者该节点不是其父节点的左节点==>一直沿着父节点网上找，直到找到当前位置的节点使其父节点的左节点 ，否则下一个节点就是nullptr
	//其实这两种做法总结起来就是找到当前节点使其父节点的左节点就可以了，也不用分类，就是一步和多步的区别而已
	else if (pNode->parentNode != nullptr) {
		BinaryTreeParentNode* pParent = pNode->parentNode;
		BinaryTreeParentNode* pCurrent = pNode;
		while (pParent != nullptr&&pCurrent == pParent->rightNode) {
			pCurrent = pParent;
			pParent = pParent->parentNode;
		}
		pNext = pParent;
	}
	return pNext;
}

//从树A中找结构为树B的子树
//第二步：在树A中找到与B的子树一样的结构的子树
bool DoesTree1HaveTree2(BinaryTreeNode* rootA, BinaryTreeNode* rootB)
{
	//递归结束的条件就是B走到尽头啦
	if (rootB == nullptr)
		return true;
	if (rootA == nullptr)	//B还没有结束A就结束了，当然就没有找到一样的子树了
		return false;	
	if (rootA->value != rootB->value)
		return false;
	//找到一样的根节点了，继续判断它的左子树和右子树
	return DoesTree1HaveTree2(rootA->leftNode, rootB->leftNode) && DoesTree1HaveTree2(rootA->rightNode, rootB->rightNode);
}

//第一步：遍历树A，找到与树B的根节点一样的节点
//函数返回的时候，rootA指针指向的内存没有改变，内存里面的东西也没有改变
bool HasSubTree(BinaryTreeNode* rootA, BinaryTreeNode* rootB)
{
	bool result = false;
	if (rootA != nullptr&&rootB != nullptr) {
		if (rootA->value == rootB->value)
			result = DoesTree1HaveTree2(rootA, rootB);
		//如果没有找到一样的根节点或者找到一样的根节点后它的子树和B不一样就继续往左子树找
		if (!result)
			result = HasSubTree(rootA->leftNode, rootB);
		//在左子树中还是没有找到符合条件的子树就往右子树找
		if (!result)
			result = HasSubTree(rootA->rightNode, rootB);
	}
}
//double类型比较
bool doubleIsEqual(double num1, double num2)
{
	if (num1 - num2<0.0000001 || num1 - num2>-0.0000001)
		return true;
	else
		return false;
}

//判断数组是否是二叉搜索树的后序遍历序列
bool isSequenceBST(int sequence[], int length)
{
	//这是一个空序列空数组,直接就可以退出此次判断了
	if (sequence == nullptr ||  length <= 0)
		return false;
	//如果不是空序列则继续
	int root = sequence[length - 1];//根是最后一个元素
	//在二叉搜索树中左子树的节点都小于根节点,找到小于根节点的最后一个元素
	int i;
	for (i = 0; i < length - 1; i++)
		if (sequence[i] > root)
			break;		//注意是break，只是为了找到最后一个左子树节点
	//在二叉搜索树中右子树的节点都大于根节点，接着左子树的最后一个元素之后的元素判断
	//看之后的所有元素是否都大于根节点，如果小于的话说明这个树不是搜索二叉树
	int j;
	for (j = i; j < length - 1; j++)
		if (sequence[j] < root)
			return false;
	//判断左子树是不是二叉搜索树
	bool left = true;	//为什么一开始就true？因为要是没有左子树就直接不用判断啦，就直接是true了
	if (i > 0)
		left = isSequenceBST(sequence, i);
	bool right = true;
	if (i != length - 1)
		right = isSequenceBST(sequence + i, length - i - 1);//length-i-1是减去左子树和根节点
		
	return (left&&right);
}

void FindPath(BinaryTreeNode* root, int expectedSum)
{
	if (root != nullptr)
		return;
	std::vector<int> path;//为什么不用stack？
	int currentSum = 0;
	FindPath(root, expectedSum, path, currentSum);
}

void FindPath(BinaryTreeNode* root, int expectedSum,std::vector<int>& path, int currentSum)
{
	currentSum += root->value;
	path.push_back(root->value);
	//如果是叶节点，并且路径上节点值的和等于输入的期望值。打印出当前路径
	bool isLeaf = root->leftNode == nullptr&&root->rightNode == nullptr;
	if (currentSum == expectedSum && isLeaf) {
		cout<<"找到一条路径："<<endl;
		std::vector<int>::iterator it;
		for (it == path.begin(); it != path.end(); it++)
			cout << *it << "\t";
		cout << endl;
	}
	//如果不是叶节点，则继续遍历它的子节点
	if (root->leftNode != nullptr)
		FindPath(root->leftNode, expectedSum, path, currentSum);
	if (root->rightNode != nullptr)
		FindPath(root->rightNode, expectedSum, path, currentSum);

	//在返回到父节点前，在路径上删除当前节点？？？这是啥？
	//遍历到叶节点之后要返回到父节点，从最最最上面一层，也就是叶节点-叶节点的父节点-……
	//开始一层层进入到最后一层后再叶开始一层层剥开，递归要画图
	path.pop_back();
}

//递归从根往叶调用函数，之后从页往根返回
//只要不是空指针，每次返回都会累加。
int depthTree(BinaryTreeNode* root)
{
	if (root == nullptr)
		return 0;
	int depthLeft = depthTree(root->leftNode);
	int depthRight = depthTree(root->rightNode);

	return (depthLeft > depthRight) ? (depthLeft + 1) : (depthRight + 1);
}

bool isBalanced1(BinaryTreeNode* root)
{
	//节点不存在，不存在平不平衡这个问题
	if (root == nullptr)
		return true;
	//要判断这个节点是否平衡，必须分别得到左右子树的深度
	int depthLeft = depthTree(root->leftNode);
	int depthRight = depthTree(root->rightNode);
	int diff = depthLeft - depthRight;
	if (diff >= 1 || diff <= -1)
		return false;
	//之后再一个一个遍历其他节点，计算、比较、判断
	return isBalanced1(root->leftNode) && isBalanced1(root->rightNode);
}

bool isBalanced(BinaryTreeNode* root,int* pDepth)
{
	if (root == nullptr) {
		*pDepth = 0;
		return 0;
	}

	int left, right;
	if (isBalanced(root->leftNode, &left) && isBalanced(root->rightNode, &right)) {
		int diff = left - right;
		if (diff <= 1 || diff >= -1) {
			*pDepth = 1 + (left > right) ? left : right;
			return true;
		}
	}
	//如果调用isBalanced的时候有返回过false，说明就不需要进入比较了，因为说明已经有一个节点事不平衡的了
	return false;
}