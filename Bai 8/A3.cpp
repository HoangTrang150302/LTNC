#include<iostream>
using namespace std;

void swap_pointers(char** x, char** y)
{
   char *tmp;
   tmp = *x;
   *x = *y;
   *y = tmp;
}
int main()
{
   char a[] = "I should print second";
   char b[] = "I should print first";

   char *s1 = a;
   char *s2 = b;
   char**s3 = &s1;
   char**s4 = &s2;
   
   swap_pointers(s3,s4);
   
   cout << "s1 is " << s1 << endl;
   cout << "s2 is " << s2 << endl;
   return 0;
}

/* muon swap hai bien int ta phai dung tham so la con tro
muon swap hai bien con tro ta dung tham so la con tro toi con tro*/

