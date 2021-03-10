#include<iostream>
#include<utility>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

const int num = 4;

int board[num][num]; //array 4x4

void print_board(); 
void new_game();
pair<int, int> auto_generate_index();
void index_to_num();
void move_num();
void move_left();

int main(int argc, const char* argv[])
{
	srand(time(0));	
	cout << "Press n: new game, u: up, d: down, l: left, r: right, q: quit\n";
	char command;
	new_game();
	while(command != 'q')
	{
		cin >> command;
		if(command == 'n')
		new_game();
	}
	return 0;
}

void print_board()
{
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			if(board[i][j] == 0)
			{
				cout << setw(4) << ".";				
			}
			else
			{
				cout << setw(4) << board[i][j];
			}
		}
		cout << endl;
	}
}

void index_to_num()
{
	pair<int,int> a = auto_generate_index();
	bool check = true;
	while(check)
	{
		if(board[a.first][a.second] == 0) //dung vong lap de tranh lap trung nhau
		{
			board[a.first][a.second] = 2;
			check = false;			
		}
	}
}

void new_game()
{
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			board[i][j] = 0;
		}
	}
	index_to_num();
	index_to_num();
	print_board();	
}

pair<int, int> auto_generate_index()
{
	int row, col;
	row = rand() % 4;
	col = rand() % 4;
	return make_pair(row, col);
}

void move_left()
{
	
}

