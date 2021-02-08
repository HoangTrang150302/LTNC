#include<iostream> //dap an d
using namespace std;

int main()
{
	int i, j;
	cin >> i >> j;
	if (i == j) {
  	cout << "A" << endl;
	}
	else if ((i % j) < 3) {
	 	cout << "B" << endl;
	}
	else if (i < (j-1)) {
	  	cout << "C" << endl;
	}
	else {
	  	cout << "D" << endl;
	}
	return 0;
}

