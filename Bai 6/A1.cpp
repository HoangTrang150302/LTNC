#include<iostream>
using namespace std;

void diachi(int a[])
{
	cout << "In dia chi tu ham ben ngoai main\n";
	cout << a << endl;
	cout << &a[0] << endl;
}

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	for(int i = 0; i < 5; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl << "In dia chi tu trong main\n";
	cout << a << endl;
	cout << &a[0] << endl;
	diachi(a);
	return 0;
	//nhan xet hai ket qua in ra giong nhau
}
