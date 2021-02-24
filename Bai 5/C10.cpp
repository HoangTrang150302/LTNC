#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int random(int N)
{
	int a;
	a = rand() % 49;
	return a;	
}

void chiahet25(int *a, const int &n)
{
	for(int i = 0; i < n - 1; i++)
	{
		int sum1 = a[i] + a[i + 1];
		int b = a[i];
		int c = a[i + 1];
		for(int j = i + 2; j < n; j++)
		{
			if((sum1 + a[j]) % 25 == 0)
			{
				cout << b << " " << c << " " << a[j] << endl;
			}
		}
	}
}

int main()
{
	short seed = time(0);
	srand(seed);
	int N;
	cin >> N;
	int *a = new int [N];
	
	for (int i = 0; i < N; i++)
	{
		a[i] = random(N);
	}
	
	for (int i = 0; i < N; i++)
	{
		cout << a[i] << " ";
	}	
	
	cout << endl;
	cout << "Cac bo 3 so chia het cho 25 la:\n";
	chiahet25(a, N);
	
	delete [] a;
	return 0;
}
