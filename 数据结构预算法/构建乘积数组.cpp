#include<vector>
using std::vector;

void multiply(const vector<double>& arrayA, vector<double>& arrayB)
{
	int lengthA = arrayA.size();
	int lengthB = arrayB.size();

	if (lengthA == lengthB && lengthB > 1) {
		arrayB[0] = 1;
		for (int i = 1; i < lengthA; i++)
			//C[i]=C[i-1]*A[i-1]
			arrayB[i] = arrayB[i - 1] * arrayA[i - 1];
		double temp = 1;
		//D[n]=1,所以从n-2开始
		//D[i]=D[i+1]*A[i+1]
		for (int i = lengthA - 2; i >= 0; i--) {
			temp = temp * arrayA[i + 1];
			arrayB[i] = arrayB[i] * temp;
		}			
	}
}