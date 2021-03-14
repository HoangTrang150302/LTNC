#include<iostream>
using namespace std;

void f(int xval)
{
   int x;
   x = xval;
   cout << &x << endl;
}
void g(int yval)
{
   int y;
   cout << &y;
}
int main()
{
   f(7);
   g(11);
   //dia chi hai bien nay giong nhau
   return 0;
} 

/*giai thich: vi tri cua stack frame cho ham f khi no chay trung voi vi tri
cua ham g khi no duoc goi(deu bat dau tren dinh stack cua ham main), ca hai ham
f va g deu co mot bien dia phuong kieu int deu la bien dia phuong dau tien cua
ham nen nhieu kha nang trinh bien dich sapxep x va y o cung mot dia chi*/
