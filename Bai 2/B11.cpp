#include <iostream> // dap an la c.9 = 5 + 3 + 1
using namespace std;

int main()
{
	int num = 5, sum = 0;
	while (num > 0)
	{
	  	if (num %2 !=0)
	      sum+=num;
	  	--num;
	}
	cout << "The sum is " << sum << endl;	
}




