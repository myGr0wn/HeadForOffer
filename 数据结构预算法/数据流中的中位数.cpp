#include<functional>

//����STL�еĺ���push_heap��pop_heap�Լ�vectorʵ�ֶ�
template<typename T> class DynamicArray
{
public:
	void Insert(T num) {
		//�����ż����������������С����
		//ż����˵��û�в���ǰ����С�Ѹ���=���Ѹ���
		//����Ĭ�Ϲ涨����С�ѵĸ��������Ѷ�һ��������˵�ȷŵ���С����
		if (((min.size() + max.size()) & 1) == 0)
		{
			//�������(���Ž�С����)�е�������max[0]�����²������
			//˵��Ŀǰ������������������С��Ҫ�����ó�������
			if (max.size() > 0 && num < max[0]) {
				//�������ݲ��뵽�����У���Ϊ���Ƚ�С
				max.push_back(num);
				push_heap(max.begin(), max.end(), less<T>());
				num = max[0];
				//��ԭ��������������������
				//less<T>()����ʾ���Ӵ�С�ݼ�����
				pop_heap(max.begin(), max.end(), less<T>());
				max.pop_back();
			}
			//����С�����������num������min[0]����С����
			min.push_back(num);
			push_heap(min.begin(), min.end(), greater<T>());
		}//���������
		else {
			if (min.size() > 0 && min[0] < num) {
				min.push_back(num);
				push_heap(min.begin(), min.end(), greater<T>());
				num = min[0];
				pop_heap(min.begin(), min.end(), greater<T>());
				min.pop_back();
			}
			max.push_back(num);
			push_heap(max.begin(), max.end(), less<T>());
		}
	}

	T GetMedian()
	{
		int size = min.size() + max.size();
		if (size == 0)
			throw exception("��������û������");

		T median = 0;
		if ((size & 1) == 1)
			median = min[0];
		else
			median = (min[0] + max[0]) / 2;

		return median;
	}
private:
	vector<T> max;//����
	vector<T> min;//��С��
};