#include<iostream>
using namespace std;

int main(int argc, char* argv [])
{
	int k;
	cout << "Enter an integer bigger than 3: ";
	cin >> k;
	while(k < 3)
	{
		cout << "The value entered must be bigger than 3!\n";
		cout << "Enter an integer bigger than 3: ";
		cin >> k;
	}
	while(k >= 3)
	{
		k = k/3;
	}
	cout << k;
	return 0;
}
