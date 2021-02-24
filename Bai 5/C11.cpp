#include<iostream>
using namespace std;

string to_binary(int n)
{
	string s, kq;
	while(n)
	{
		int a = n%2;
		char c = a + '0';
		s += c;
		n = n/2;
	}
	for (int i = s.size() - 1; i >= 0; i--)
	{
		kq += s[i];
	}
	return kq;
}

int main()
{
	int n;
	cin >> n;
	cout << to_binary(n);
	return 0;
}
