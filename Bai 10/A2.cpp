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

void print_ref(POINT &p) 
{
	cout << "Cout from POINT &p\n";
	cout << "x = " << p.x << " " << "y = " << p.y << endl;
	cout << "Address of p is: " << &p << endl;
}

void print_val(POINT p) 
{
	cout << "Cout from POINT p\n";
	cout << "x = " << p.x << " " << "y = " << p.y << endl;
	cout << "Address of p is: " << &p << endl;
}

int main()
{
	POINT p1(3.2,4.6);
	cout << "Address of p1 is: " << &p1 << endl;
	print_ref(p1);
	print_val(p1);
	return 0;
}
