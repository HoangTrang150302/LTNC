#include<iostream>
using namespace std;

int main()
{
	int *p;
	int a = 10;
	p = &a;
	delete p; // lenh nay lam chuong trinh bi loi con tro nay khong duoc cap phat bo nho dong nen khon duoc dung lenh delete
	return 0;
}
