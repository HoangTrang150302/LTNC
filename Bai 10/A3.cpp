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

POINT Mid_Point(POINT p1, POINT p2)
{
	POINT mid(0, 0);
	mid.x = (p1.x + p2.x)/2;
	mid.y = (p1.y + p2.y)/2;
	return mid;
}

void print(POINT p) 
{
	cout << "x = " << p.x << endl << "y = " << p.y << endl;
}

int main()
{
	POINT p1(3,4), p2(5.3, 10);
	print(p1);
	print(p2);
	POINT mid = Mid_Point(p1, p2);
	print(mid);
	return 0;
}
