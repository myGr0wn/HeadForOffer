#include<stack>

template<typename T> class CQueue
{
public:
	CQueue(void);
	~CQueue(void);

	void appendTail(const &T node);
	T deleteHead();

private:
	stack<T> stack1;
	stack<T> stack2;
};

template<typename T> void CQueue::appendTail(const &T node)
{
	stack1.push(node);
}

template<typename T> T deleteHead()
{
	if (stack2.size() <= 0) {
		while (stack1.size() > 0) {
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}
	//上面将数从1搬到2之后，2还是为空，说明1中没有数，两个stack都是空的
	if (stack2.size() == 0)
		throw new exception("queue is empty");

	T head = stack2.top();
	stack2.pop();

	return head;
}



template <typename T> class CStack
{
public:
	CStack(void)；
	~CStack(void)；
	void appendTail(const T& node);
	T deleteHead();
private:
	queue<T> q1;
	queue<T> q2;
};

template<typename T> void CStack<T>::appendTail(const T& node)//在栈尾部添加数据
{
	if (!q1.empty())//不为空的执行push操作
		q1.push(node);
	else 
		q2.push(node);
}

template<typename T> T CStack<T>::deleteHead()
{
	int ret = 0;
	if (q1.empty() && q2.empty())
		throw new exception("stack is empty");

	if (q1.empty())
	{
		int i = q2.size();
		while (i > 1)//将q2队列中的数据pop到只剩一个
		{
			q1.push(q2.front());
			q2.pop();
			--i;
		}
		ret = q2.front();
		q2.pop();
	}
	else
	{
		int i = q1.size();
		while (i > 1)
		{
			q2.push(q1.front());
			q1.pop();
			--i;
		}
		ret = q1.front();
		q1.pop();
	}
	return ret;
}