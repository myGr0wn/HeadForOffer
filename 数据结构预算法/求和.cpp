class Temp {
public:
	Temp() { ++N; Sum += N; }
	//C++静态成员函数
	static void Reset() { N = 0; Sum = 0; }
	static unsigned int GetSum() { return Sum; }

private:
	//C++静态数据成员
	static unsigned int N;
	static unsigned int Sum;
};

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int Sum_1(unsigned int n)
{
	Temp::Reset();

	Temp *a = new Temp[n];
	delete[] a;
	a = nullptr;

	return Temp::GetSum();
}

class A;
A* Array[2];

class A
{
public:
	virtual unsigned int Sum(unsigned int n) { return 0; }
};
//作为循环的类
class B :public A
{
public:
	virtual unsigned int Sum(unsigned int n) {
		return Array[!!n]->Sum(n - 1) + n;
	}
};
int Sum_2(int n)
{
	A a;
	B b;
	Array[0] = &a;
	Array[1] = &b;

	int value = Array[1]->Sum(n);
	return value;
}

//利用函数指针求解
typedef unsigned int(*fun)(unsigned int);

unsigned int teminator(unsigned int n)
{
	return 0;
}

unsigned int Sum_3(unsigned int n)
{
	static fun f[2] = { teminator,Sum_3 };
	return n + f[!!n](n - 1);
}

//利用模板类型求解
template <unsigned int n>struct Sum_4
{
	enum Value
	{
		N = Sum_4<n - 1>::N + n;
	};
};

template <> struct Sum_4<1>
{
	enum Value{N=1};
};