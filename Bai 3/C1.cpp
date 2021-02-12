#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int *a = new int [n];
	for(int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	bool check = false;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if(a[i] == a[j])
			{
				check = true;
			}
		}
	}
	if(check) cout << "yes";
	else cout << "no";
	delete [] a;
	return 0;
}
