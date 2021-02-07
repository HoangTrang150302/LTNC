#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	int x, y;
	unsigned seed = time(0);
	srand(seed);
	x = rand() % 100 + 1;
	y = rand() % 100 + 1;
	//cin >> x >> y;
	int choose;
	cout << "Choose 1 or 2\n";
	cin >> choose;
	while(choose != 1 && choose != 2)
	{
		cout << "The number must be 1 or 2\n" << "Now choose again\n";
		cin >> choose;
	}
	if(choose == 1) cout << x << endl;
	else cout << y << endl;
	cout << "Which number is bigger?\n";
	cout << "Choose 1 or 2\n";
	cin >> choose;
	if(x > y && choose == 1) cout << "Congratulation. You win!";
	else if(x < y && choose == 2) cout << "Congratulation. You win!";
	else cout << "You lose!";
	return 0; 
}
