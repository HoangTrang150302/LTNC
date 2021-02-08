#include <iostream> // dap an la b.45
using namespace std;
 
int main()
{
   int x=7,y=45,z=63,min_num;
	if (x<z) 	
      min_num=x;
	else
      min_num=z;
	if(y<z)  
      min_num=y;
	else   	
	   min_num=z;
	
   cout<<"The minimum is:" <<min_num;
   system ("pause");
   return 0;
}

