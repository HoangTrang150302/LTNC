#include<iostream>
using namespace std;

long long F(int n) { 
   if (n == 0) return 0; 
   if (n == 1) return 1; 
   return F(n-1) + F(n-2); 
}

long long Fibo(int n)
{
	int f0 = 0, f1 = 1;
	long fn;
	for (int i = 2; i <= n; i++)
	{
		fn = f0 + f1;
		f0 = f1;
		f1 = fn;
	}
	return fn;
}

int main()
{
	int n;
	cin >> n;
	cout << F(n) << endl;
	cout << Fibo(n);
	/* n = 40 vong lap: 2.048s
	de quy 2.52s2*/
	return 0;
}
