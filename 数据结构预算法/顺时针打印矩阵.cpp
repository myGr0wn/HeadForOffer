#include<iostream>
using std::cout;

//˳ʱ���ӡ���󣬸ú�����Ҫ�ǿ��ƴ�ӡȦ�˳�������
void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
	if (numbers == nullptr || columns <= 0 || rows <= 0)
		return;

	int start = 0;	//start��ÿ��Ȧ��ʼ�����꣨����һ����
	while (columns > start * 2 && rows > start * 2) {
		PrintMatrixInCircle(numbers, columns, rows, start);
		++start;
	}
}
//��Ȧ��ӡ������.ÿ�ε���ֻ��ӡһȦ
void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)
{
	int endX = columns - 1 - start;//�����ͼ����Ƚ�����
	int endY = rows - 1 - start;
	//�����Ҵ�ӡһ��
	for (int i = start; i <= endX; i++) {
		int number = numbers[start][i];
		cout << number << "\t";
	}
	//���ϵ��´�ӡһ��
	if (endY > start)
		for (int i = start + 1; i <= endY; i++) {
			int number = numbers[i][endY];
			cout << number << "\t";
		}
	//���ҵ����ӡһ��
	//��ֹ�кŴ�����ʼ�кţ���ֹ�кŴ�����ʼ�к�
	if(endX>start&&endY>start)
		for (int i = endX - 1; i >= start; i--) {
			int number = numbers[endY][i];
			cout << number << "\t";
		}
	//���µ��ϴ�ӡһ�У��������кŲ��䣬�кż�С
	if(endX>start&&endY-1>start)
		for (int i = endY; i >= start + 1; i--) {
			int number = numbers[i][start];
			cout << number << "\t";
		}
}
