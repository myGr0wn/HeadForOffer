#include<list>
#include<vector>
using std::vector;
using std::list;

struct TreeNode
{
	int nValue;
	vector<TreeNode*> childNodes;
};

bool GetNodePath(TreeNode* pRoot, TreeNode* pNode, list<TreeNode*>& path)
{
	if (pRoot == pNode)
		return true;
	path.push_back(pRoot);
	bool found = false;
	vector<TreeNode*>::iterator i = pRoot->childNodes.begin();
	while (!found&&i < pRoot->childNodes.end())
	{
		found = GetNodePath(*i, pNode, path);
		++i;
	}
	//如果不在这条路径中那就弹出下，之后返回，然后进入下一次遍历
	if (!found)
		path.pop_back();
	return found;
}

TreeNode* GetLastCommonNode(const list<TreeNode*>& path1, const list<TreeNode*>& path2)
{
	list<TreeNode*>::const_iterator it1 = path1.begin();
	list<TreeNode*>::const_iterator it2 = path2.begin();

	TreeNode* pLast = nullptr;
	while (it1 != path1.end() && it2 != path2.end())
	{
		if (*it1 == *it2)
			pLast = *it1;
		it1++;
		it2++;
	}
	return pLast;//返回链表中最后一个相同的节点
}

TreeNode* GetLastCommonParent(TreeNode* pRoot, TreeNode* pNode1, TreeNode* pNode2)
{
	if (pRoot == nullptr || pNode1 == nullptr || pNode2 == nullptr)
		return nullptr;
	list<TreeNode*> path1;
	GetNodePath(pRoot, pNode1, path1);

	list<TreeNode*> path2;
	GetNodePath(pRoot, pNode2, path2);

	return GetLastCommonNode(path1, path2);
}