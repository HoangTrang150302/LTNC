#include<iostream>
using namespace std;

double H(int N) {
   if(N == 1) return 1.0; 
   return H(N-1) + 1.0/N; 
}

int main()
{
	int n;
	cin >> n;
	cout << H(n);
	return 0;
	//chuong trinh se bi loi neu khong co base case
}
