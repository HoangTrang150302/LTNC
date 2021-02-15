#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int *b = new int [n];
	fill_n(b,n,1);
	
	for (int i = 2; i < n; i++)
	{
		for (int j = i+i; j < n; j += i)
		{
			b[j] = 0;
		}
	}
	
	for (int i = 1; i < n; i++)
	{
		if(b[i])
		cout << i << " ";
	}
	delete [] b;
	return 0;
}
