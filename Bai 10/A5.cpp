#include<iostream>
using namespace std;

const int num = 5;

struct ARRAY
{
	int *a = new int [num];
};

int main()
{
	int *b= new int [num];
	ARRAY arr;
	cout << "arr.a = " << arr.a << endl;
	b = arr.a;
	cout << "b = " << b << endl;
	return 0;
	// dia chi hai bien in ra giong nhau
}
