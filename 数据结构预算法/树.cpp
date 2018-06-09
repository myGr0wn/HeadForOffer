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

//���Ĵ���
BinaryTreeNode* ConstructCore(int* firstPreorder, int* lastPreorder,
	int* firstMidorder, int* lastMidorder)
{
	//��ǰ����������еõ����ڵ�
	int rootValue = firstPreorder[0];
	BinaryTreeNode* root = new BinaryTreeNode();
	root->value = rootValue;
	root->leftNode = root->rightNode = nullptr;
	//ֻʣһ���ڵ�,�����ͷ���һ���ڵ�Ϳ����ˣ�����Ҫ���к���Ĳ���
	if (firstPreorder==lastPreorder)
	{	
		if (firstMidorder == lastMidorder && *firstPreorder == *firstMidorder)
			return root;
		else
			throw std::exception("Invalid order");
	}
	//������������ҵ����ڵ�λ�ã��Ӷ�������������������
	int* rootMidorder = firstMidorder;
	//�ҵ����ڵ��λ��
	while (rootMidorder <= lastMidorder && *rootMidorder != rootValue)
		++rootMidorder;
	if (rootMidorder == lastMidorder && *rootMidorder != rootValue)
		throw std::exception("Invalid input");
	//�������ĸ���
	int leftLen = rootMidorder - firstMidorder;
	int *leftPreorderEnd = firstPreorder + leftLen;
	if (leftLen > 0)
		//����������
		root->leftNode = ConstructCore(firstPreorder + 1, leftPreorderEnd, firstMidorder, rootMidorder - 1);
	if (leftLen < lastPreorder - firstPreorder)
		//����������
		root->rightNode = ConstructCore(leftPreorderEnd + 1, lastPreorder, rootMidorder + 1, lastMidorder);

	return root;
}

//����ǰ��������к�������������Լ����еĳ��ȣ���һ�����ģ�
BinaryTreeNode* Construct(int* preorder, int* midorder, int length)
{
	if (preorder == nullptr || midorder == nullptr || length == 0)
		return nullptr;
	//����ǰ������ĵ�һ�������һ������ָ�룬�Լ���������ĵ�һ���������һ������ָ��
	return ConstructCore(preorder, preorder + length - 1, midorder, midorder + length - 1);
}

//ӵ�и��ڵ����
struct BinaryTreeParentNode
{
	int value;
	BinaryTreeParentNode* leftNode;
	BinaryTreeParentNode* rightNode;
	BinaryTreeParentNode* parentNode;
};

//�Ӷ��������ҳ�һ���ڵ����һ���ڵ�
BinaryTreeParentNode* findNext(BinaryTreeParentNode* pNode)
{
	if (pNode == nullptr)
		return;

	BinaryTreeParentNode* pNext;
	//�����ҽڵ�==>��һ���ڵ�����������������ߵ�һ���ڵ㣬˳����ڵ�һֱ��
	if (pNode->rightNode != nullptr) {
		BinaryTreeParentNode* rightNode = pNode->rightNode;
		while (rightNode->leftNode != nullptr)
			rightNode = rightNode->leftNode;
		pNext = rightNode;
	}//�������ҽڵ㣬���Ǹýڵ����丸�ڵ����ڵ�==>��һ���ڵ�������ĸ��ڵ�
	//���߸ýڵ㲻���丸�ڵ����ڵ�==>һֱ���Ÿ��ڵ������ң�ֱ���ҵ���ǰλ�õĽڵ�ʹ�丸�ڵ����ڵ� ��������һ���ڵ����nullptr
	//��ʵ�����������ܽ����������ҵ���ǰ�ڵ�ʹ�丸�ڵ����ڵ�Ϳ����ˣ�Ҳ���÷��࣬����һ���Ͷಽ���������
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

//����A���ҽṹΪ��B������
//�ڶ���������A���ҵ���B������һ���Ľṹ������
bool DoesTree1HaveTree2(BinaryTreeNode* rootA, BinaryTreeNode* rootB)
{
	//�ݹ��������������B�ߵ���ͷ��
	if (rootB == nullptr)
		return true;
	if (rootA == nullptr)	//B��û�н���A�ͽ����ˣ���Ȼ��û���ҵ�һ����������
		return false;	
	if (rootA->value != rootB->value)
		return false;
	//�ҵ�һ���ĸ��ڵ��ˣ������ж�������������������
	return DoesTree1HaveTree2(rootA->leftNode, rootB->leftNode) && DoesTree1HaveTree2(rootA->rightNode, rootB->rightNode);
}

//��һ����������A���ҵ�����B�ĸ��ڵ�һ���Ľڵ�
//�������ص�ʱ��rootAָ��ָ����ڴ�û�иı䣬�ڴ�����Ķ���Ҳû�иı�
bool HasSubTree(BinaryTreeNode* rootA, BinaryTreeNode* rootB)
{
	bool result = false;
	if (rootA != nullptr&&rootB != nullptr) {
		if (rootA->value == rootB->value)
			result = DoesTree1HaveTree2(rootA, rootB);
		//���û���ҵ�һ���ĸ��ڵ�����ҵ�һ���ĸ��ڵ������������B��һ���ͼ�������������
		if (!result)
			result = HasSubTree(rootA->leftNode, rootB);
		//���������л���û���ҵ���������������������������
		if (!result)
			result = HasSubTree(rootA->rightNode, rootB);
	}
}
//double���ͱȽ�
bool doubleIsEqual(double num1, double num2)
{
	if (num1 - num2<0.0000001 || num1 - num2>-0.0000001)
		return true;
	else
		return false;
}

//�ж������Ƿ��Ƕ����������ĺ����������
bool isSequenceBST(int sequence[], int length)
{
	//����һ�������п�����,ֱ�ӾͿ����˳��˴��ж���
	if (sequence == nullptr ||  length <= 0)
		return false;
	//������ǿ����������
	int root = sequence[length - 1];//�������һ��Ԫ��
	//�ڶ������������������Ľڵ㶼С�ڸ��ڵ�,�ҵ�С�ڸ��ڵ�����һ��Ԫ��
	int i;
	for (i = 0; i < length - 1; i++)
		if (sequence[i] > root)
			break;		//ע����break��ֻ��Ϊ���ҵ����һ���������ڵ�
	//�ڶ������������������Ľڵ㶼���ڸ��ڵ㣬���������������һ��Ԫ��֮���Ԫ���ж�
	//��֮�������Ԫ���Ƿ񶼴��ڸ��ڵ㣬���С�ڵĻ�˵���������������������
	int j;
	for (j = i; j < length - 1; j++)
		if (sequence[j] < root)
			return false;
	//�ж��������ǲ��Ƕ���������
	bool left = true;	//Ϊʲôһ��ʼ��true����ΪҪ��û����������ֱ�Ӳ����ж�������ֱ����true��
	if (i > 0)
		left = isSequenceBST(sequence, i);
	bool right = true;
	if (i != length - 1)
		right = isSequenceBST(sequence + i, length - i - 1);//length-i-1�Ǽ�ȥ�������͸��ڵ�
		
	return (left&&right);
}

void FindPath(BinaryTreeNode* root, int expectedSum)
{
	if (root != nullptr)
		return;
	std::vector<int> path;//Ϊʲô����stack��
	int currentSum = 0;
	FindPath(root, expectedSum, path, currentSum);
}

void FindPath(BinaryTreeNode* root, int expectedSum,std::vector<int>& path, int currentSum)
{
	currentSum += root->value;
	path.push_back(root->value);
	//�����Ҷ�ڵ㣬����·���Ͻڵ�ֵ�ĺ͵������������ֵ����ӡ����ǰ·��
	bool isLeaf = root->leftNode == nullptr&&root->rightNode == nullptr;
	if (currentSum == expectedSum && isLeaf) {
		cout<<"�ҵ�һ��·����"<<endl;
		std::vector<int>::iterator it;
		for (it == path.begin(); it != path.end(); it++)
			cout << *it << "\t";
		cout << endl;
	}
	//�������Ҷ�ڵ㣬��������������ӽڵ�
	if (root->leftNode != nullptr)
		FindPath(root->leftNode, expectedSum, path, currentSum);
	if (root->rightNode != nullptr)
		FindPath(root->rightNode, expectedSum, path, currentSum);

	//�ڷ��ص����ڵ�ǰ����·����ɾ����ǰ�ڵ㣿��������ɶ��
	//������Ҷ�ڵ�֮��Ҫ���ص����ڵ㣬������������һ�㣬Ҳ����Ҷ�ڵ�-Ҷ�ڵ�ĸ��ڵ�-����
	//��ʼһ�����뵽���һ�����Ҷ��ʼһ���������ݹ�Ҫ��ͼ
	path.pop_back();
}

//�ݹ�Ӹ���Ҷ���ú�����֮���ҳ��������
//ֻҪ���ǿ�ָ�룬ÿ�η��ض����ۼӡ�
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
	//�ڵ㲻���ڣ�������ƽ��ƽ���������
	if (root == nullptr)
		return true;
	//Ҫ�ж�����ڵ��Ƿ�ƽ�⣬����ֱ�õ��������������
	int depthLeft = depthTree(root->leftNode);
	int depthRight = depthTree(root->rightNode);
	int diff = depthLeft - depthRight;
	if (diff >= 1 || diff <= -1)
		return false;
	//֮����һ��һ�����������ڵ㣬���㡢�Ƚϡ��ж�
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
	//�������isBalanced��ʱ���з��ع�false��˵���Ͳ���Ҫ����Ƚ��ˣ���Ϊ˵���Ѿ���һ���ڵ��²�ƽ�����
	return false;
}