#include<iostream> // ghi tran thi cac gia tri khong phai la gia tri cua mang se in ra gia tri rac
using namespace std;

int const NUM = 4;

int main()
{
	int a[NUM];
	for (int i = 0; i < 10; i++)
	{
		cin >> a[i];
	}
	
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	//do c++ de thua hai o nho du phong phia truoc va phia sau mang nen neu tran it hon 2 phan tu thi van in ra gia tri dung
	return 0;
}
