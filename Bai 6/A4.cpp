#include<iostream>
using namespace std;

double H(int N) { 
   if (N == 1) return 0.0;
   return H(N-1) + 1.0/N; 
}

int main()
{
	int n;
	cin >> n;
	cout << H(n);
	return 0;
	/*neu de quy qua nhieu se dan den loi tran bo nho
	vi bo nho stack dung de luu tru cac gia tri trong luc goi ham
	rat nho nen no rat de bi tran*/
}
