#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int const NUM = 5;

void bubble_sort(int a[])
{
	for(int i = NUM - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if(a[j] > a[j + 1])
			swap(a[j], a[j + 1]);
		}
	}
}

void inmang(int a[])
{
	for (int i = 0; i < NUM; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;	
}

int main()
{
	int a[NUM];
	srand(time(0));
	for (int i = 0; i < NUM; i++)
	{
		a[i] = (rand() % 100) + 1;
	}
	inmang(a);
	bubble_sort(a);
	inmang(a);
	return 0;
}
