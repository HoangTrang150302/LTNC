#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	int* p = new int;
	int* p2 = p;
	*p = 10;
	//delete p; //delete p o day lam dong tiep theo mac loi truy nhap vung bo nho da thu hoi
	*p2 = 100; //dong 11 12 gay ra loi
	cout << *p2;
	delete p2;
	return 0;
}
