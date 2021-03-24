#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

struct INDEX
{
    int row;
    int col;
};

struct BOARD
{
    int value;
    bool done = false;
};

const int num = 4;

int dir_Row[4] = {0,0,-1,1}; //left:0 - right:1 - up:2 - down:3
int dir_Col[4] = {-1,1,0,0}; //left:0 - right:1 - up:2 - down:3

BOARD board[num][num]; //array 4x4
bool check_move_lose = true;

void print_board();
void new_game();
INDEX auto_generate_index();
void index_to_num();
void move_num(char);
int command_to_direction(char);
bool inside(int);
void reset_false();
bool win();
bool lose();
bool full_board();


int main(int argc, const char* argv[])
{
	srand(time(0));
	char command;
	new_game();
	bool game = true;
	while(game)
	{

        if(win())
        {
            cout << "You win";
            return 0;
        }
        if(lose())
        {
            cout << "You lose";
            return 0;
        }
		cin >> command;
		if(command == 'n')
        {
            new_game();
        }
		else if(command == 'q')
        {
            game = false;
        }
        else
        {
            move_num(command);
        }
    }
	return 0;
}

void print_board()
{
	system("cls");
	cout << "Press n: new game, w: up, s: down, a: left, d: right, q: quit\n";
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			if(board[i][j].value == 0)
			{
				cout << setw(4) << ".";
			}
			else
			{
				cout << setw(4) << board[i][j].value;
			}
		}
		cout << endl;
	}
}

bool inside(int a)
{
    if(a >= 0 && a < num) return true;
    else return false;
}

int command_to_direction(char command)
{
    int num;
    if(command == 'a') num = 0;
    if(command == 'd') num = 1;
    if(command == 'w') num = 2;
    if(command == 's') num = 3;
    return num;
}

void move_num(char command)
{
    int direction = command_to_direction(command);
    check_move_lose = true;
    bool check, add = false;
    while(check)
    {
        check = false;
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j < num; j++)
            {
                //cout << "i = " << i << " j = " << j << endl;
                int nextI = i + dir_Row[direction]; //nextI && nextJ move to the next Row or Col
                int nextJ = j + dir_Col[direction];
                //cout << "nextI = " << nextI << " NextJ = " << nextJ << endl;
                if(inside(nextI) && inside(nextJ) && board[i][j].value)
                {
                    if(board[i][j].value == board[nextI][nextJ].value && !board[i][j].done)
                    {
                        //cout << "HELLO" << endl;
                        //if(board[nextI][nextJ] == board[i][j] && board[nextI][nextJ] != 0) check1 = true;
                        board[nextI][nextJ].value += board[i][j].value;
                        board[nextI][nextJ].done = true;
                        //cout << "board[nextI][nextJ] = " << board[nextI][nextJ] << endl;
                        //cout << "board[i][j] = " << board[i][j] << endl;
                        board[i][j].value = 0;
                        //print_board();
                        check = true;
                        add = true;
                    }
                    else if(board[nextI][nextJ].value == 0)
                    {
                        //cout << "HELLO" << endl;
                        //if(board[nextI][nextJ] == board[i][j] && board[nextI][nextJ] != 0) check1 = true;
                        board[nextI][nextJ].value += board[i][j].value;
                        //cout << "board[nextI][nextJ] = " << board[nextI][nextJ] << endl;
                        //cout << "board[i][j] = " << board[i][j] << endl;
                        board[i][j].value = 0;
                        //print_board();
                        check = true;
                        add = true;
                    }

                }
                //cout << "continue" << endl << endl;
            }

        }
         //if(check == false) continue;
        /*if(check == false) //print board when break the while loop
        {
            print_board();
        }*/
    }
    check_move_lose = !check;
    if(add)
    {
        //cout << "ADD" << endl;
        index_to_num(); //genderate new number
        print_board();
    }
    reset_false();

}

void index_to_num()
{
	INDEX a = auto_generate_index();
    board[a.row][a.col].value = 2;
}

void new_game()
{
	int count = 1;
	for(int i = 0; i < num; i++)
	{
		for(int j = 0; j < num; j++)
		{
			board[i][j].value = 0;
			/*board[0][0].value = 2;
			board[1][0].value = 2;
			board[2][0].value = 4;
			board[3][0].value = 4;
			board[0][2].value = 2048;
			board[i][j].value = count;
			count++;*/
		}
	}
	index_to_num();
	index_to_num();
	print_board();
}

INDEX auto_generate_index()
{
	INDEX board_index;
	bool check = true;
	while(check)
    {
        board_index.row = rand() % 4;
        board_index.col = rand() % 4;
        if(board[board_index.row][board_index.col].value == 0)
        {
            check = false;
        }
    }
	return board_index;
}

void reset_false()
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            board[i][j].done = false;
        }
    }
}

bool win()
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if(board[i][j].value == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool full_board()
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num; j++)
        {
            if(!board[i][j].value)
            {
                return false;
            }
        }
    }
    return true;
}

bool lose()
{
    if(full_board() && check_move_lose) return true;
    else return false;
}
