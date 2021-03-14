#include<iostream>
#include<algorithm>
using namespace std;

void reverse(char a[])
{
	int n = 5;
	for (int i = 0; i <= n/2; i++)
	{
		swap(a[i], a[n - 1 - i]);
	}
}

void delete_char(char a[], char c)
{
	int n = 5;
	for(int i = 0; i < n;)
	{
		if(a[i] == c)
		{
			a[i] = a[i - 1];
			n--;
		}
		else i++;
	}
	for (int i = 0; i < n; i++)
	{
		cout << a[i];
	}
}

int main()
{
	char a[] = "trang";
	cout << a << endl;
	reverse(a);
	cout << a << endl;
	delete_char(a, 't');
	cout << endl;
	return 0;
}
