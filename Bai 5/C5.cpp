#include<iostream>
#include<cmath>
using namespace std;

bool is_Prime(int n)
{
	if(n < 2) return false;
	for(int i = 2; i <= sqrt(n); i++)
	{
		if(n % i == 0)
		return false;
	}
	return true;
}

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		if(is_Prime(i)) cout << i << " ";
	}
	return 0;
}
