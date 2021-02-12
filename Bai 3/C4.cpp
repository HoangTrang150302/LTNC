#include<iostream>
using namespace std;

void nhapmang(int, int, char **);
void xuatmang(int, int, char **);
void checkmin(int, int, char **);
int dem_min(int, int, const int &, const int &, char **);
bool check(int, int);


int main()
{
	int m,n;
	cin >> n >> m;
	char **a = new char *[n];
	for (int i = 0; i < n; i++)
	{
		*(a+i) = new char [m];
	}
	
	nhapmang(n, m, a);
	//xuatmang(n, m, a);
	checkmin(n, m, a);
	
	for (int i = 0; i < n; i++)
	{
		delete *(a + i);
	}
	delete [] a;
	return 0;
}

void nhapmang(int n, int m, char **a)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[i][j];
		}
	}	
}

void xuatmang(int n, int m, char **a)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}	
}

void checkmin(int n, int m, char **a)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if(a[i][j] == '*')
			cout << a[i][j] << " ";
			else
			{
				cout << dem_min(i, j, n, m, a) << " ";
			}
		}
		cout << endl;
	}	
}

int dem_min(int i, int j,const int &n,const int &m,char **a)
{
	int a1,b,c,d,e,f;
	int count = 0;

	a1 = i;
	b = i + 1;
	c = i - 1;
	d = j;
	e = j + 1;
	f = j - 1;
	
	if(check(c,n) && check(f,m))
	{
		if(a[c][f] == '*')
		count++;		
	}
		
	if(check(c,n) && check(d,m))
	{
		if(a[c][d] == '*')
		count++;		
	}
	
	if(check(c,n) && check(e,m))
	{
		if(a[c][e] == '*')
		count++;		
	}
	
	if(check(a1,n) && check(f,m))
	{
		if(a[a1][f] == '*')
		count++;		
	}

	if(check(a1,n) && check(e,m))
	{
		if(a[a1][e] == '*')
		count++;		
	}
	
	if(check(b,n) && check(f,m))
	{
		if(a[b][f] == '*')
		count++;		
	}

	if(check(b,n) && check(d,m))
	{
		if(a[b][d] == '*')
		count++;		
	}
	
	if(check(b,n) && check(e,m))
	{
		if(a[b][e] == '*')
		count++;		
	}
	return count;	
}

bool check(int i, int n)
{
	if(i >= 0 && i < n)
	return true;
	else return false;
}
