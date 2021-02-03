#include<iostream>
using namespace std;

int main()
{
	long long x = 65536; //46340 = 2^15.5 max value because the int max value is 2^31
	cout << "x = " << x << endl;
	long long y = x * x;
	cout << "y = " << y << endl;
	return 0;
}
