#include<functional>

//基于STL中的函数push_heap、pop_heap以及vector实现堆
template<typename T> class DynamicArray
{
public:
	void Insert(T num) {
		//如果是偶数个，把它放在最小堆中
		//偶数个说明没有插入前，最小堆个数=最大堆个数
		//这里默认规定是最小堆的个数比最大堆多一个，就是说先放到最小堆中
		if (((min.size() + max.size()) & 1) == 0)
		{
			//如果最大堆(存着较小的数)中的最大的数max[0]大于新插入的数
			//说明目前最大堆中最大的数还不够小，要把它拿出来才行
			if (max.size() > 0 && num < max[0]) {
				//把新数据插入到最大堆中，因为它比较小
				max.push_back(num);
				push_heap(max.begin(), max.end(), less<T>());
				num = max[0];
				//把原来最大堆中最大的数弹出来
				//less<T>()：表示按从大到小递减排序
				pop_heap(max.begin(), max.end(), less<T>());
				max.pop_back();
			}
			//按从小到大递增插入num，所以min[0]是最小的数
			min.push_back(num);
			push_heap(min.begin(), min.end(), greater<T>());
		}//如果是奇数
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
			throw exception("数据流中没有数字");

		T median = 0;
		if ((size & 1) == 1)
			median = min[0];
		else
			median = (min[0] + max[0]) / 2;

		return median;
	}
private:
	vector<T> max;//最大堆
	vector<T> min;//最小堆
};