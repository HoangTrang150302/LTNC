#include<iostream>
using namespace std;

long long F(int n)
{
	int a[1000];
	if(n == 0) return 0;
	else return n + F(n - 1);
}

int main()
{
	int n;
	cin >> n;
	cout << F(n);
	return 0;
	// den n = 511 thi bi loi tran bo nho
}
