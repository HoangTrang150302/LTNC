#include<iostream> //chuyen thanh int thi moi in duoc dung ket qua can in
using namespace std;

int const row = 2;
int const col = 12;

void inmang(char daytab[][col])
{
	for(int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			cout << daytab[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	char daytab1[2][12] = {
  	{31,28,31,30,31,30,31,31,30,31},//,30,31},
  	{31,29,31,30,31,30,31,31,30,31}//,30,31}
	};
	inmang(daytab1);
	char daytab2[2][12] = {
    31,28,31,30,31,30,31,31,30,31,//30,31,
    31,29,31,30,31,30,31,31,30,31//,30,31
};
	inmang(daytab2);
	return 0; 
}
