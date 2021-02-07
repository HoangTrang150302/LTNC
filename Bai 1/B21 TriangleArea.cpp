#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	double a, b, c;
	cin >> a >> b >> c;
	if(!(a < b + c && b < a + c && c < a + b))
	{
		cout << "Khong phai tam giac";
		return 0;
	}
	double p = (a+b+c)/2;
	cout << sqrt(p * (p - a) * (p - b) * (p - c));
	return 0;
}
