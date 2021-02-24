#include<iostream>
#include<cmath>
using namespace std;

void tamgiac(int n)
{
	for (int y = n - 1; y >= 0; y--)
	{
		for(int x = -(n - 1); x <= n - 1; x++)
		{
			if(abs(x) + abs(y) <= n - 1)
			cout << "*";
			else cout << " ";
		}
		cout << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	tamgiac(n);
	return 0;
}
