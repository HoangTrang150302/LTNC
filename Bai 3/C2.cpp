#include<iostream>
using namespace std;

int main()
{
	string s;
	cin >> s;
	int n;
	n = s.size();
	bool check = true;
	for (int i = 0; i < n/2; i++)
	{
		if(s[i] != s[n - 1 - i])
		{
			check = false;
		}
	}
	if(check) cout << "yes";
	else cout << "no";
	return 0;
}
