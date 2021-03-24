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

int main()
{
	POINT p(3.2,4.6);
	cout << "Address of p is: " << &p << endl;
	cout << "&p.x = " << &p.x << endl << "&p.y = " << &p.y << endl;
	return 0;
	//dia chi cua bien dau tien chinh la dia chi cua bien kieu struct va cac bien duoc sap xep lien tiep nhau
}
