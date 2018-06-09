//�õ�����ĺ�
int getMaxtrixSum(int n, int m)
{
	int sum = 0;
	while (n > 0) {
		sum += sum % 10;
		sum /= 10;
	}
	while (m > 0) {
		sum += sum % 10;
		sum /= 10;
	}
	return sum;
}

//���������Ƿ���Խ�������꣨row,col��
bool check(int maxK, int rows, int cols, int row, int col, bool* isVisited)
{
	if (row >= 0 && col >= 0 && row < rows&&col < cols
		&&getMaxtrixSum(row, col)
		&& !isVisited[row*cols + col])
		return true;
	return false;
}

int moveCountCore(int maxK, int rows, int cols, int row, int col, bool* isVisited)
{
	int count = 0;
	if (check(maxK, rows, cols, row, col, isVisited)) {
		isVisited[row*cols + col] = true;
		//���countֻ�ǵ�ǰ�ڵ��Լ��Ժ���ܺͣ�û��ǰ��ģ�ǰ���Ҫ�ȵݹ��ȥ֮�����
		count = 1 + moveCountCore(maxK, rows, cols, row - 1, col, isVisited)
			+ moveCountCore(maxK, rows, cols, row + 1, col, isVisited)
			+ moveCountCore(maxK, rows, cols, row, col - 1, isVisited)
			+ moveCountCore(maxK, rows, cols, row, col + 1, isVisited);
	}
	return count;
}

int moveCount(int maxK, int rows, int cols)
{
	if (maxK < 0 || rows <= 0 || cols <= 0)
		return 0;
	bool *isVisited = new bool[rows*cols];
	for (int i = 0; i < rows*cols; i++)
		isVisited[i] = false;
	int count = moveCountCore(maxK, rows, cols, 0, 0, isVisited);
	//����Ҫ�ǵ��ͷ��ڴ�ռ䣡��
	delete[] isVisited;
	return count;
}
