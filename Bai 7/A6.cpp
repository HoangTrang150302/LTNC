#include<iostream>
using namespace std;

//tham so dong lenh cua ham main
int main(int argc, const char * argv[]) {
	cout << "Number of command-line arguments: " << argc << endl;
	for (int i = 0; i < argc; i++) {
		cout << "Argument #" << i << ": _" << argv[i] << "_\n";
	}
	return 0;
}

/*C:\Users\admin>D:\LTNC\B7\A6.exe 1
Number of command-line arguments: 2
Argument #0: _D:\LTNC\B7\A6.exe_
Argument #1: _1_

C:\Users\admin>D:\LTNC\B7\A6.exe first second 3rd
Number of command-line arguments: 4
Argument #0: _D:\LTNC\B7\A6.exe_
Argument #1: _first_
Argument #2: _second_
Argument #3: _3rd_*/

