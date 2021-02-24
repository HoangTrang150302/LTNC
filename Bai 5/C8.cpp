#include<iostream>
#include<cmath>
using namespace std;

int rounded(double n)
{
	double m = n - (int)n;
	if(m < 0.5) return n;
	else
	return n + 1;
}

int main()
{
	double n;
	cin >> n;
	cout << round(n) << endl;
	cout << rounded(n);
	return 0;
}
