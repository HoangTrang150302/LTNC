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
	for(int i = 0; i < n; i++)
	{
		long long sum_left = 0;
		long long sum_right = 0;
		
		if(i == 0) sum_left = 0;
		else
		{
			for (int j = i - 1; j >= 0; j--)
			{
				sum_left += a[j];
			}
		}
		
		if(i == n - 1) sum_right = 0;
		else
		{
			for (int j = i + 1; j < n; j++)
			{
				sum_right += a[j];
			}
		}
		
		if(sum_left == sum_right)
		{
			return true;
		}
	}
	return false;
}


