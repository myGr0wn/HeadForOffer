#include<deque>
#include<iostream>
#include<queue>
using std::cout;
using std::deque;//两端都可以出的队列
using std::queue;

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* leftNode;
	BinaryTreeNode* rightNode;
};

void PrintFromTopToBottom(BinaryTreeNode* pRoot)
{
	if (!pRoot)//不存在的树
		return;
	deque<BinaryTreeNode*> dequeTreeNode;
	dequeTreeNode.push_back(pRoot);
	while (dequeTreeNode.size())
	{
		BinaryTreeNode* pNode = dequeTreeNode.front();
		dequeTreeNode.pop_front();//出队
		cout << pNode->value;
		//当前节点的左右节点入队
		if (pNode->leftNode)
			dequeTreeNode.push_back(pNode->leftNode);
		if (pNode->rightNode)
			dequeTreeNode.push_back(pNode->rightNode);
	}
}
//按层输出打印二叉树
void Print(BinaryTreeNode* pRoot)
{
	if (!pRoot)
		return;
	queue<BinaryTreeNode*> dequeTreeNodes;	//queue普通队列
	dequeTreeNodes.push(pRoot);
	int nextLevel = 0;	//下一行需要打印的节点数
	int toBePrint = 1;	//当前行还没有打印的节点数
	while (!dequeTreeNodes.empty()) {	//与.size()的功能一样
		BinaryTreeNode* pNode = dequeTreeNodes.front();
		cout << pNode->value;
		if (pNode->leftNode) {
			dequeTreeNodes.push(pNode->leftNode);
			nextLevel++;
		}
		if (pNode->rightNode) {
			dequeTreeNodes.push(pNode->rightNode);
			nextLevel++;
		}
		dequeTreeNodes.pop();
		--toBePrint;
		if (toBePrint == 0) {	//为下一层打印做准备    
			cout << std::endl;
			toBePrint = nextLevel;
			nextLevel = 0;
		}
	}
}
//按之字形顺序打印二叉树
#include<stack>
void PrintZ(BinaryTreeNode* pRoot)
{
	if (!pRoot)	return;
	std::stack<BinaryTreeNode*> levels[2];	//两个栈
	int current = 0;
	int next = 1;
	levels[current].push(pRoot);
	while (!levels[0].empty() || !levels[1].empty())
	{
		BinaryTreeNode* pNode = levels[current].top();	//当前要打印的节点
		levels[current].pop();
		//这里其实与上面画的图的两个栈相反了。
		//Stack1是levels[1]—从左到右入栈，从右到左出栈
		cout << pNode->value << " ";
		if (current == 0) {//next=1
			if (pNode->leftNode != nullptr)
				levels[next].push(pNode->leftNode);
			if (pNode->rightNode != nullptr)
				levels[next].push(pNode->rightNode);
		}//Stcak2是levels[0]—从右到左入栈，从左到右出栈
		else {//next=0
			if (pNode->rightNode != nullptr)
				levels[next].push(pNode->rightNode);
			if (pNode->leftNode != nullptr)
				levels[next].push(pNode->leftNode);
		}
		if (levels[current].empty()) {
			cout << std::endl;
			current = 1 - current;
			next = 1 - next;
		}
	}
}
//序列化二叉树[1,2,4,$,$,$……]4后面有3个$是因为4没有子节点，所以左右两边都是nullptr
//2的左子节点递归结束后，开始右子节点，发现2的右子节点也是nullptr，所以又多了一个$
void Serialize(BinaryTreeNode* pRoot, std::ostream& stream)
{
	//只要是遇到空节点就输入“$”，然后结束此次递归
	if (pRoot == nullptr) {
		stream << "$";
		return;
	}
	stream << pRoot->value << ",";
	//前序遍历的序列化
	Serialize(pRoot->leftNode,stream);
	Serialize(pRoot->rightNode,stream);
}

//每次调用从流中读取一个数字或一个字符“$”
//当从流中读取的是数字时，返回true；读取的是$时，返回false
bool ReadStream(std::istream& stream, int* number)
{
	if (stream.eof())
		return false;

	char buffer[32];
	buffer[0] = '\0';

	char ch;
	stream >> ch;
	int i = 0;
	//把整个数字读完，因为可能是多位的数字
	while (!stream.eof() && ch != ',') {
		buffer[i++] = ch;
		stream >> ch;
	}
	bool isNumberic = false;
	if (i > 0 && buffer[0] != '$') {
		*number = atoi(buffer);
		isNumberic = true;
	}
	return isNumberic;
}
//为什么是**。因为根节点的指向内存要改变，所以就需要有一个指向指针内存的指针
void Deserialize(BinaryTreeNode** pRoot, std::istream& stream)
{
	int number;
	if (ReadStream(stream, &number)) {//读取到了一个数字
		//先创建一个树的节点
		*pRoot = new BinaryTreeNode();
		(*pRoot)->value = number;
		(*pRoot)->leftNode = nullptr;
		(*pRoot)->rightNode = nullptr;
		Deserialize(&(*pRoot)->leftNode, stream);//对当前节点的左节点赋值
		//如果下一个读到的是$，那就直接不用管了，结束当前递归，一层层返回
		Deserialize(&(*pRoot)->rightNode, stream);
	}
}