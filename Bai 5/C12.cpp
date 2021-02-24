#include<iostream>
using namespace std;

void nhapso(int *a, int *b, int& sophantu)
{
	int k, n;
	int i = 0;
	do
	{
		cin >> k >> n;
		a[i] = k;
		b[i] = n;
		i++;
	}
	while(k != -1 && n != -1);
	sophantu = i - 1;	
}

int tohop(int k, int n)
{
	long long p1 = 1;
	for (int i = 1; i <= k; i++)
	{
		p1 *= i;
	}
	long long p2 = 1;
	for (int j = n; j >= (n - k + 1); j--)
	{
		p2 *= j;
	}
	int c = p2/p1;
	return c;
}

int main()
{
	int sophantu;
	int *a = new int;
	int *b = new int;
	
	nhapso(a, b, sophantu);
	
	for (int i = 0; i < sophantu; i++)
	{
		cout << tohop(a[i], b[i]) << endl;
	}
	
	delete [] a;
	delete [] b;
	return 0;
}
