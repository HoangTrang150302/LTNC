#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int random(int N)
{
	int a;
	a = rand() % N + 1;
	return a;	
}

int main()
{
	short seed = time(0);
	srand(seed);
	int N;
	cin >> N;
	cout << random(N);
	return 0;
}
