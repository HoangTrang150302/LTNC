#include<iostream>
using namespace std;

int main()
{
	int a, b;
	int min;
	cin >> a >> b;
	//c1 toan tu ba ngoi
	min = (a<b) ? a : b;
	cout << "C1:\n" << "Min = " << min << endl;
	//c2 if else
	if(a< b) min = a;
	else min = b;
	cout << "C2:\n" << "Min = " << min << endl;
	return 0; 
	//Cau 1 chon dap an b
	//Cau 2 chon dap an d tao menu
	// 3c
}
