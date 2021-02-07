#include<iostream>
using namespace std;

int main()
{
	int grade;
	cin >> grade;
	bool isA = (grade >= 90 && grade <= 100);
	cout << isA;
	return 0;
}
