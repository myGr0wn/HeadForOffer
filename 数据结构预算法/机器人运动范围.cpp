//得到坐标的和
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

//检查机器人是否可以进入该坐标（row,col）
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
		//这个count只是当前节点以及以后的总和，没有前面的，前面的要等递归回去之后加上
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
	//还是要记得释放内存空间！！
	delete[] isVisited;
	return count;
}
