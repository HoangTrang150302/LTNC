#include<iostream>
using namespace std;

int main()
{
	double mass;
	double height;
	cin >> mass >> height;
	cout << "BMI = " << mass/(height * height);
	return 0;
}

