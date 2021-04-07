#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 496;
const int SCREEN_HEIGHT = 496;
const string WINDOW_TITLE = "2048_Game";

const int START_ROW = 14;
const int START_COL = 11;
const int STEP = 121;
const int NUM = 4;

SDL_Window* window;
SDL_Renderer* renderer;

struct IMAGE
{
    string name;
    int x = 0;
    int y = 0;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    void loadMedia(SDL_Renderer* renderer);
    IMAGE(string file_name, int _x, int _y)
    {
        name = file_name;
        x = _x;
        y = _y;
        surface = IMG_Load(name.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        loadMedia(renderer);
    }
};

struct INDEX
{
    int row;
    int col;
};

struct BOARD
{
    int value = 0;
    bool done = false;
};

int dir_Row[4] = {0,0,-1,1}; //left:0 - right:1 - up:2 - down:3
int dir_Col[4] = {-1,1,0,0}; //left:0 - right:1 - up:2 - down:3

BOARD board[NUM][NUM];
//Starts up SDL and creates window
bool init();
int get_index_row(int x);
int get_index_col(int y);
void new_game();
INDEX random_position();
void print_image(string path, int x, int y);
int move_event(SDL_Event &e);
void print_board();
bool inside(int);
void index_to_num();
void move(SDL_Event &e);
void print_number(int n, int x, int y);

int main(int argc, char* argv[])
{
    //INIT Window
	if(!init())
	{
		cout << "Failed to initialize!\n";
		return 0;
	}
    srand(time(0));
	new_game();
    SDL_Event e;
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
                if(e.key.keysym.sym == SDLK_n)
                {
                    new_game();
                }
            /*else
            {
                //print_board();
                //move(e);
            }*/
            }

        }
    }
    /*while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
			//User requests quit
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
            else
            {
                move_event(image2, e);
            }
        }
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
    }
		/*while(true)
        {
            SDL_PumpEvents();
            int x, y;
            SDL_GetMouseState(&x,&y);
            cout << x << ' ' <<y<< '\n';
            SDL_Delay(1000);
        }*/

    //SDL_Delay(6000);
	//Free resources and close SDL
	//close();
	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL could not initialize!\n";
		success = false;
	}
	else
	{
        //Create window
		window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			cout << "Window could not be created!\n";
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL)
			{
				cout << "Renderer could not be created!\n";
				success = false;
			}
			else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
		}
	}
	return success;
}

void IMAGE::loadMedia(SDL_Renderer* renderer)
{
	if(surface == NULL) cout << "Surface error\n";
	if(texture == NULL) cout << "Texture error\n";
	SDL_Rect dest = {x, y,surface->w,surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

int get_index_row(int i)
{
    int x = START_ROW + STEP*i;
    //cout << "x = " << x << endl;
    return x;
}

int get_index_col(int j)
{
    int y = START_COL + STEP*j;
    //cout << "y = " << y << endl;
    return y;
}

void print_image(string path, int x, int y)
{
    IMAGE image1(path.c_str(), x, y);
    SDL_RenderPresent(renderer);
}

void new_game()
{
    for(int i = 0; i < NUM; i++)
	{
		for(int j = 0; j < NUM; j++)
		{
			board[i][j].value = 0;
		}
	}
    index_to_num();
    index_to_num();
    print_board();
    cout << "New Game\n";
}

INDEX random_position()
{
    INDEX index;
    bool check = true;
    while(check)
    {
        index.row = rand() % NUM;
        index.col = rand() % NUM;
        if(board[index.row][index.col].value == 0)
        {
            check = false;
        }
    }
    return index;
}

void index_to_num()
{
    INDEX a = random_position();
    board[a.row][a.col].value = 2;
}

int move_event(SDL_Event &e)
{
    int direction = 0;
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                //image.y -= STEP;
                direction = 2;
                cout << direction << endl;
                break;
            case SDLK_DOWN:
                //image.y += STEP;
                direction = 3;
                break;
            case SDLK_RIGHT:
                //image.x += STEP;
                direction = 1;
                break;
            case SDLK_LEFT:
                //image.x -= STEP;
                direction = 0;
                break;
            default:
                break;
        }
    }
    cout << "MOVE_EVENT\n";
    cout << direction << endl;
    return direction;
}

void print_board()
{
    print_image("grid.bmp", 0, 0);
	for(int i = 0; i < NUM; i++)
	{
		for(int j = 0; j < NUM; j++)
		{
			if(board[i][j].value)
			{
				print_number(board[i][j].value, get_index_row(i), get_index_col(j));
				cout << setw(4) << board[i][j].value;
			}
			else
            {
                cout << setw(4) << ".";
            }
		}
		cout << endl;
	}
	cout << "PRINT_BOARD\n";
}

bool inside(int a)
{
    if(a >= 0 && a < NUM) return true;
    else return false;
}

void move(SDL_Event &e)
{
    int direction = move_event(e);
    //cout << direction << endl;
    bool check, add = false;
    while(check)
    {
        check = false;
        for (int i = 0; i < NUM; i++)
        {
            for (int j = 0; j < NUM; j++)
            {
                int nextI = i + dir_Row[direction]; //nextI && nextJ move to the next Row or Col
                int nextJ = j + dir_Col[direction];
                if(inside(nextI) && inside(nextJ) && board[i][j].value)
                {
                    if(board[i][j].value == board[nextI][nextJ].value && !board[i][j].done)
                    {
                        board[nextI][nextJ].value += board[i][j].value;
                        board[nextI][nextJ].done = true;
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
    if(add)
    {
        index_to_num(); //genderate new number
        print_board();
    }
}

void print_number(int n, int x, int y)
{
    switch(n)
    {
        case 2:
            print_image("2.bmp", x, y);
            break;
        case 4:
            print_image("4.bmp", x, y);
            break;
        case 8:
            print_image("8.bmp", x, y);
            break;
        case 16:
            print_image("16.bmp", x, y);
            break;
        case 32:
            print_image("32.bmp", x, y);
            break;
        case 64:
            print_image("64.bmp", x, y);
            break;
        case 128:
            print_image("128.bmp", x, y);
            break;
        case 256:
            print_image("256.bmp", x, y);
            break;
        case 512:
            print_image("512.bmp", x, y);
            break;
        case 1024:
            print_image("1024.bmp", x, y);
            break;
        case 2048:
            print_image("2048.bmp", x, y);
            break;
        default:
            break;
    }
}

