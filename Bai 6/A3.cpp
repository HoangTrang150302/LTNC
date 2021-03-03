#include<iostream>
using namespace std;

double H(int N) { 
   if (N == 1) return 1.0;
   return H(N) + 1.0/N; //o day chua co gia tri cua H(n) nen chuong trinh bi loi
}

int main()
{
	int n;
	cin >> n;
	cout << H(n);
	return 0;
}
