#include<iostream>
using namespace std;

struct POINT
{
	double x;
	double y;
	POINT(double _x, double _y)
	{
		x = _x;
		y = _y;
	}
};	

void print(POINT p) 
{
	cout << "x = " << p.x << endl << "y = " << p.y << endl;
}

int main()
{
	POINT p1(3.2,4.6);
	print(p1);
	return 0;
}
