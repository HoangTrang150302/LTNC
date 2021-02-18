#include<iostream>
using namespace std;

bool check(int *, int);

int main()
{
	int n;
	cin >> n;
	
	while(n)
	{
		int m;
		cin >> m;
		int *a = new int [m];
		for (int i = 0; i < m; i++)
		{
			cin >> a[i];
		}
		
		if(check(a, m))
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
		n--;
		delete [] a;
	}

	return 0;
}

bool check(int *a, int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	
	int count = a[0];
	if(sum == count) return true;
	for(int i = 1; i < n; i++)
	{
		if(sum - a[i] - count == count)
		{
			return true;
		}
		count += a[i];	
	}
	return false;
}

