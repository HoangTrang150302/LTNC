#include<iostream> // doc tran thi cac gia tri khong phai la gia tri cua mang se in ra gia tri rac
using namespace std;

int const NUM = 4;

int main()
{
	int a[NUM] = {1, 2, 3, 4};
	for (int i = 0; i < NUM; i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}
