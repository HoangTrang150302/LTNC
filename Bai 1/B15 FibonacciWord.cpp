#include<iostream>
#include<string>
using namespace std;

int main()
{
	int n;
	cin >> n;
	string f0 = "a";
	string f1= "b";
	string fn;
	if(n == 0)
	{
		cout << f0;
		return 0;
	}
	if(n == 1)
	{
		cout << f1;
		return 0;
	}
	for(int i = 2; i <= n; i++)
	{
		fn = f1 + f0;
		f0 = f1;
		f1 = fn;
	}
	cout << fn;
	return 0;
}
