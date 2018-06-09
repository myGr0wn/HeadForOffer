#include<deque>
#include<iostream>
#include<queue>
using std::cout;
using std::deque;//���˶����Գ��Ķ���
using std::queue;

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode* leftNode;
	BinaryTreeNode* rightNode;
};

void PrintFromTopToBottom(BinaryTreeNode* pRoot)
{
	if (!pRoot)//�����ڵ���
		return;
	deque<BinaryTreeNode*> dequeTreeNode;
	dequeTreeNode.push_back(pRoot);
	while (dequeTreeNode.size())
	{
		BinaryTreeNode* pNode = dequeTreeNode.front();
		dequeTreeNode.pop_front();//����
		cout << pNode->value;
		//��ǰ�ڵ�����ҽڵ����
		if (pNode->leftNode)
			dequeTreeNode.push_back(pNode->leftNode);
		if (pNode->rightNode)
			dequeTreeNode.push_back(pNode->rightNode);
	}
}
//���������ӡ������
void Print(BinaryTreeNode* pRoot)
{
	if (!pRoot)
		return;
	queue<BinaryTreeNode*> dequeTreeNodes;	//queue��ͨ����
	dequeTreeNodes.push(pRoot);
	int nextLevel = 0;	//��һ����Ҫ��ӡ�Ľڵ���
	int toBePrint = 1;	//��ǰ�л�û�д�ӡ�Ľڵ���
	while (!dequeTreeNodes.empty()) {	//��.size()�Ĺ���һ��
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
		if (toBePrint == 0) {	//Ϊ��һ���ӡ��׼��    
			cout << std::endl;
			toBePrint = nextLevel;
			nextLevel = 0;
		}
	}
}
//��֮����˳���ӡ������
#include<stack>
void PrintZ(BinaryTreeNode* pRoot)
{
	if (!pRoot)	return;
	std::stack<BinaryTreeNode*> levels[2];	//����ջ
	int current = 0;
	int next = 1;
	levels[current].push(pRoot);
	while (!levels[0].empty() || !levels[1].empty())
	{
		BinaryTreeNode* pNode = levels[current].top();	//��ǰҪ��ӡ�Ľڵ�
		levels[current].pop();
		//������ʵ�����滭��ͼ������ջ�෴�ˡ�
		//Stack1��levels[1]����������ջ�����ҵ����ջ
		cout << pNode->value << " ";
		if (current == 0) {//next=1
			if (pNode->leftNode != nullptr)
				levels[next].push(pNode->leftNode);
			if (pNode->rightNode != nullptr)
				levels[next].push(pNode->rightNode);
		}//Stcak2��levels[0]�����ҵ�����ջ�������ҳ�ջ
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
//���л�������[1,2,4,$,$,$����]4������3��$����Ϊ4û���ӽڵ㣬�����������߶���nullptr
//2�����ӽڵ�ݹ�����󣬿�ʼ���ӽڵ㣬����2�����ӽڵ�Ҳ��nullptr�������ֶ���һ��$
void Serialize(BinaryTreeNode* pRoot, std::ostream& stream)
{
	//ֻҪ�������սڵ�����롰$����Ȼ������˴εݹ�
	if (pRoot == nullptr) {
		stream << "$";
		return;
	}
	stream << pRoot->value << ",";
	//ǰ����������л�
	Serialize(pRoot->leftNode,stream);
	Serialize(pRoot->rightNode,stream);
}

//ÿ�ε��ô����ж�ȡһ�����ֻ�һ���ַ���$��
//�������ж�ȡ��������ʱ������true����ȡ����$ʱ������false
bool ReadStream(std::istream& stream, int* number)
{
	if (stream.eof())
		return false;

	char buffer[32];
	buffer[0] = '\0';

	char ch;
	stream >> ch;
	int i = 0;
	//���������ֶ��꣬��Ϊ�����Ƕ�λ������
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
//Ϊʲô��**����Ϊ���ڵ��ָ���ڴ�Ҫ�ı䣬���Ծ���Ҫ��һ��ָ��ָ���ڴ��ָ��
void Deserialize(BinaryTreeNode** pRoot, std::istream& stream)
{
	int number;
	if (ReadStream(stream, &number)) {//��ȡ����һ������
		//�ȴ���һ�����Ľڵ�
		*pRoot = new BinaryTreeNode();
		(*pRoot)->value = number;
		(*pRoot)->leftNode = nullptr;
		(*pRoot)->rightNode = nullptr;
		Deserialize(&(*pRoot)->leftNode, stream);//�Ե�ǰ�ڵ����ڵ㸳ֵ
		//�����һ����������$���Ǿ�ֱ�Ӳ��ù��ˣ�������ǰ�ݹ飬һ��㷵��
		Deserialize(&(*pRoot)->rightNode, stream);
	}
}