#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

char* reverse(const char a[])
{
	int n = strlen(a);
	char *b = new char [n];
	for (int i = 0; i < n; i++)
	{
		b[i] = a[n - 1 - i];
	}
	return b;
}

char* delete_char(const char a[],const char& c)
{
	char *d = new char;
	int n = strlen(a);
	for(int i = 0, j = 0; i < n;)
	{
		if(a[i] != c)
		{
			d[j] = a[i];
			j++;
		}
		i++;
	}
	return d;
}

int main()
{
	char a[] = "trang";
	cout << a << endl;
	cout << reverse(a) << endl;
	cout << delete_char(a, 'a') << endl;
	return 0;
}
