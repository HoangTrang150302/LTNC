#include<iostream> //in ra cac so chia het cho 5 dap an b
using namespace std;

int main()
{
	int n = 5, k;
	  for (k = 1; k <= 50; k++) {
	  	if ( (k%n)) continue;
	      cout << k << "\t";
	  }
	return 0; 
}
/*5 d
6 b
7 d
8 a b c
*/
