#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	char* a = new char[10];
	char* c = a + 3; // c tro den phan tu thu 3 cua day a 
	cout << strlen(c) << endl;
	for (int i = 0; i < 9; i++) a[i] = 'a'; 
	cout << a << endl;
	a[9] = '\0';
	cerr <<"a: " << "-" << a << "-" << endl;
	cerr <<"c: " << "-" << c << "-" << endl;
	delete c; //c phai duoc khai bao dong khong thi hanh vi cua chuong trinh la khong xac dinh
	cerr << "a after deleting c:" << "-" << a << "-" << endl;// lenh cerr nay khong chay nhu mong muon
	return 0;
}

