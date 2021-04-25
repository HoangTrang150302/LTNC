#include <iostream>
#include <string>
#include <cstdlib>
#include "BOARD.h"
using namespace std;

void generate_new_number(const int &NUM, BOARD** board)
{
    int i, j;
    bool check = true; // this variable to check that the new position does not contain any number
    while(check)
    {
        i = rand() % NUM;
        j = rand() % NUM;
        if(board[i][j].value == 0)
        {
            check = false;
        }
    }
    int n = rand() % 10;
    if(n == 0)
    {
        board[i][j].value = 4;
    }
    else
    {
        board[i][j].value = 2;
    }
}

void new_game(bool &win_check, int &score, const int &NUM, BOARD** board)
{
    //reset value
    for(int i = 0; i < NUM; i++)
	{
		for(int j = 0; j < NUM; j++)
		{
			board[i][j].value = 0;
			board[i][j].done = false;
		}
	}
	//board[1][1].value = 2048;
	win_check = false;
	score = 0;

	//generate new number
    generate_new_number(NUM, board);
    generate_new_number(NUM, board);
    cout << "New Game\n";
}

bool inside(int a, const int &NUM)
{
    if(a >= 0 && a < NUM) return true;
    return false;
}

void reset_false(const int &NUM, BOARD** board)
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            board[i][j].done = false;
        }
    }
}

bool move_num(int direction, int& score, const int &NUM, BOARD** board)
{
    const int dir_Row[4] = {0,0,-1,1}; //left:0 - right:1 - up:2 - down:3
    const int dir_Col[4] = {-1,1,0,0}; //left:0 - right:1 - up:2 - down:3

    bool check = true, add = false;
    int startLine = 0, startColumn = 0, lineStep = 1, columnStep = 1;

    if(direction == 0) //down
    {
        startLine = 3;
        lineStep = -1;
    }

    if(direction == 1) //right
    {
        startColumn = 3;
        columnStep = -1;
    }

    while(check)
    {
        check = false;
        for (int i = startLine; inside(i, NUM); i+= lineStep)
        {
            for (int j = startColumn; inside(j, NUM); j+= columnStep)
            {
                int nextI = i + dir_Row[direction]; //nextI && nextJ move to the next Row or Col
                int nextJ = j + dir_Col[direction];
                if(inside(nextI, NUM) && inside(nextJ, NUM) && board[i][j].value)
                {
                    if(board[i][j].value == board[nextI][nextJ].value && !board[i][j].done)
                    {
                        board[nextI][nextJ].value += board[i][j].value;
                        score += board[nextI][nextJ].value;
                        board[nextI][nextJ].done = true;
                        board[i][j].done = true;
                        board[i][j].value = 0;
                        check = true;
                        add = true;
                    }
                    else if(board[nextI][nextJ].value == 0)
                    {
                        board[nextI][nextJ].value += board[i][j].value;
                        board[i][j].value = 0;
                        check = true;
                        add = true;
                    }
                }
            }
        }
    }
    reset_false(NUM, board);
    return add;
}

bool win(const int &NUM, BOARD** board)
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            if(board[i][j].value == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

bool lose(const int &NUM, BOARD** board)
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            if(board[i][j].value == 0)
            {
                return false;
            }
            int a, b, c, d, e, f;
            a = i;
            b = i + 1;
            c = i - 1;
            d = j;
            e = j + 1;
            f = j - 1;
            if(inside(e, NUM))
            {
                if(board[a][e].value == board[a][d].value)
                {
                    return false;
                }
            }
            if(inside(f, NUM))
            {
                if(board[a][f].value == board[a][d].value)
                {
                    return false;
                }
            }
            if(inside(b, NUM))
            {
                if(board[b][d].value == board[a][d].value)
                {
                    return false;
                }
            }
            if(inside(c, NUM))
            {
                if(board[c][d].value == board[a][d].value)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
