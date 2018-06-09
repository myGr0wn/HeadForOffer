#include<string>

bool hasPathCore(char* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool* isVisited)
{
	//说明已经到达路径的出口了
	if (str[pathLength] == '\0')
		return true;
	
	bool hasPath = false;
	//当前访问的字符串就是符合路径的字符串
	if (row >= 0 && row < rows&&col >= 0 && col < cols
		&&matrix[row*cols + col] == str[pathLength]
		&& !isVisited[row*cols + col]) {
		++pathLength;//访问目标字符串的下一个字符
		isVisited[row*cols + col] = true;
		//访问上下左右四个元素
		hasPath = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, isVisited)
			|| hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, isVisited)
			|| hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, isVisited)
			|| hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, isVisited);
		//这一个元素之后的路径都没有合适的，回到当前元素的上一个元素（看树,父节点）
		if (!hasPath) {
			--pathLength;
			isVisited[row*cols + col] = false;
		}
	}
	return hasPath;
}

bool hasPath(char* matrix, int rows, int cols, char* str)
{
	if (matrix == nullptr || rows < 1 || cols < 1 || str == nullptr)
		return false;

	bool* visited = new bool[rows*cols];
	/*extern void *memset(void *buffer, int c, int count)        
	buffer：为指针或是数组,
	c：是赋给buffer的值,
	count：是buffer的长度.
	作用：
	这个函数在socket中多用于清空数组.如:原型是memset(buffer, 0, sizeof(buffer))
	用来对一段内存空间全部设置为某个字符，一般用在对定义的字符串进行初始化为‘ ’或‘/0’；*/
	memset(visited, 0, rows*cols);
	int pathLength = 0;	
	//为什么是双重循环？因为是二维数组，要遍历整个数组中所有的元素
	//为什么要遍历所有元素？因为如果从某一个元素为起始点找不到符合条件的路径就要重新找起点，之后就要另选起点了
	for (int row = 0; row < rows; row++)
		for (int col = 0; col < cols; col++)
			if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited))
				return true;
	//为什么要delete？因为visited是一个指针，我们一开始有用new给他分配空间，之后这个空间不用了就需要释放掉，不然会造成内存泄露？
	delete[] visited;
	return false;
}