#include<iostream>
#include<cstring>
using namespace std;

char* concat(const char* a, const char* b)
{
	
	int counta = strlen(a), countb = strlen(b);
	int count = counta + countb;
	char *c = new char [count];
	for (int i = 0; i < counta; i++)
	{
		c[i] = a[i];
	}
	for (int i = counta, j = 0; i < count && j < countb; i++, j++)
	{
		c[i] = b[j];
	}
	return c;
}

int main()
{
	char *result = concat("Hello", " World!");
	cout << result;
	delete [] result;
	return 0;
}
