#include<iostream>
#include<cmath>
using namespace std;

int main()
{
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	double x = abs(x1 - x2) * abs(x1 - x2) * 1.0;
	double y = abs(y1 - y2) * abs(y1 - y2) * 1.0;
	cout << sqrt(x + y);
	return 0;
}
