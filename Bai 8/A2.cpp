#include<iostream>
using namespace std;

int main( )
{ 
   char a[] = "abcdefghiklmn"; 
   for (char *cp = a; (*cp) != '\0'; cp+=8) {
      cout << (void*) cp << " : " << (*cp) << endl;
   }
   /*int b[4] = {1, 2, 3, 4};
   for (int *i = b; i < (b+4); i++)
   {
   		cout << i << " : " << (*i) << endl;	
   } 
   double c[4] = {1, 2, 3, 4};
   for (double *i = c; i < (c+4); i++)
   {
   		cout << i << " : " << (*i) << endl;	
   } */
   return 0;
}

