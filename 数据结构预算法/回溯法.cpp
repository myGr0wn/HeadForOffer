#include<string>

bool hasPathCore(char* matrix, int rows, int cols, int row, int col, const char* str, int& pathLength, bool* isVisited)
{
	//˵���Ѿ�����·���ĳ�����
	if (str[pathLength] == '\0')
		return true;
	
	bool hasPath = false;
	//��ǰ���ʵ��ַ������Ƿ���·�����ַ���
	if (row >= 0 && row < rows&&col >= 0 && col < cols
		&&matrix[row*cols + col] == str[pathLength]
		&& !isVisited[row*cols + col]) {
		++pathLength;//����Ŀ���ַ�������һ���ַ�
		isVisited[row*cols + col] = true;
		//�������������ĸ�Ԫ��
		hasPath = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, isVisited)
			|| hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, isVisited)
			|| hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, isVisited)
			|| hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, isVisited);
		//��һ��Ԫ��֮���·����û�к��ʵģ��ص���ǰԪ�ص���һ��Ԫ�أ�����,���ڵ㣩
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
	buffer��Ϊָ���������,
	c���Ǹ���buffer��ֵ,
	count����buffer�ĳ���.
	���ã�
	���������socket�ж������������.��:ԭ����memset(buffer, 0, sizeof(buffer))
	������һ���ڴ�ռ�ȫ������Ϊĳ���ַ���һ�����ڶԶ�����ַ������г�ʼ��Ϊ�� ����/0����*/
	memset(visited, 0, rows*cols);
	int pathLength = 0;	
	//Ϊʲô��˫��ѭ������Ϊ�Ƕ�ά���飬Ҫ�����������������е�Ԫ��
	//ΪʲôҪ��������Ԫ�أ���Ϊ�����ĳһ��Ԫ��Ϊ��ʼ���Ҳ�������������·����Ҫ��������㣬֮���Ҫ��ѡ�����
	for (int row = 0; row < rows; row++)
		for (int col = 0; col < cols; col++)
			if (hasPathCore(matrix, rows, cols, row, col, str, pathLength, visited))
				return true;
	//ΪʲôҪdelete����Ϊvisited��һ��ָ�룬����һ��ʼ����new��������ռ䣬֮������ռ䲻���˾���Ҫ�ͷŵ�����Ȼ������ڴ�й¶��
	delete[] visited;
	return false;
}