#include<iostream>
#include<string>
using namespace std;

string dao_nguoc(string);
char ki_tu_giua(string);

int main()
{
	int n;
	cin >> n;
	string *a = new string [n];
	
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	
	for (int i = 0; i < n; i++)
	{
		for(int j = i + 1; j < n; j++)
		{
			if(a[j] == dao_nguoc(a[i]))
			{
				cout << a[i].size() << " ";
				cout << ki_tu_giua(a[i]);
				delete [] a;
				return 0;
			}
		}
	}
	return 0;
}

string dao_nguoc(string s)
{
	string kq;
	for (int i = s.size() - 1; i >= 0; i--)
	{
		kq += s[i];
	}
	return kq;
}

char ki_tu_giua(string s)
{
	int n = s.size();
	return s[n/2];
}
