#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <SDL_ttf.h>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 596;
const int SCREEN_HEIGHT = 762;
const string WINDOW_TITLE = "2048_Game";

const int START_ROW = 35;
const int START_COL = 192;
const int STEP = 136;
const int NUM = 4;
int SCORE = 0;
bool WIN_CHECK = false;

SDL_Window* window;
SDL_Renderer* renderer;

/*TTF_Font* font = TTF_OpenFont("lazy.ttf", 20);
SDL_Color color = {255, 0, 255, 255};

void load_from_render_text()
{
    //Load from render text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "HNMT", color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {0, 0, 50, 50};
    SDL_FreeSurface(textSurface);
    textSurface = NULL;
}*/


SDL_Texture* texture[18];

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
void init();
int get_index_row(int x);
int get_index_col(int y);
void new_game();
INDEX random_position();
void print_image(string path, int x, int y);
int move_event(SDL_Event &e);
void print_board();
bool inside(int);
void index_to_num();
void move_num(SDL_Event &e);
void print_number(int n, int x, int y);
void reset_false();
bool full_board();
bool win();
bool lose();
bool check_move_lose();
bool equal_num(const int &i,const int &j);
int random_new_number();
void close();
void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    //INIT Window
	init();
    srand(time(0));
	//new_game();
    SDL_Event e;
    bool quit = false;
    load_from_render_text();
    /*SDL_RenderCopy(renderer,texture[0],NULL,NULL);
    SDL_RenderPresent(renderer);
            while(true)
            {
                SDL_PumpEvents();
                int x, y;
                SDL_GetMouseState(&x,&y);
                cout << x << ' ' <<y<< '\n';
                SDL_Delay(1000);
            }*/

    //GAME LOOP
    while(!quit)
    {
        SDL_RenderPresent(renderer);
        if(win() && !WIN_CHECK)
        {
            cout << "YOU WIN\n";
            WIN_CHECK = true;
            cout << "Press ESC to quit, press N to start a new game, press arrow key to keep playing\n";
            if(e.type = SDL_KEYDOWN)
            {
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 0;
                    }
                    else if(e.key.keysym.sym == SDLK_n)
                    {
                        new_game();
                    }
            }
        }
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
                else if(e.key.keysym.sym == SDLK_n)
                {
                    new_game();
                }
                else
                {
                    if(move_event(e) >= 0)
                    {
                        move_num(e);
                        SDL_RenderPresent(renderer);
                    }
                }
            }
        }
        if(lose())
        {
            cout << "You lose";
            quit = true;
            SDL_Delay(5000);
        }
    }
	//Free resources and close SDL
	close();
	return 0;
}

void init()
{
    //Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    //Create window
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Load texture
	texture[0] = IMG_LoadTexture(renderer,"background.bmp");
    texture[1] = IMG_LoadTexture(renderer,"2.bmp");
    texture[2] = IMG_LoadTexture(renderer,"4.bmp");
    texture[3] = IMG_LoadTexture(renderer,"8.bmp");
    texture[4] = IMG_LoadTexture(renderer,"16.bmp");
    texture[5] = IMG_LoadTexture(renderer,"32.bmp");
    texture[6] = IMG_LoadTexture(renderer,"64.bmp");
    texture[7] = IMG_LoadTexture(renderer,"128.bmp");
    texture[8] = IMG_LoadTexture(renderer,"256.bmp");
    texture[9] = IMG_LoadTexture(renderer,"512.bmp");
    texture[10] = IMG_LoadTexture(renderer,"1024.bmp");
    texture[11] = IMG_LoadTexture(renderer,"2048.bmp");
    texture[12] = IMG_LoadTexture(renderer,"4096.bmp");
    texture[13] = IMG_LoadTexture(renderer,"8192.bmp");
    texture[14] = IMG_LoadTexture(renderer,"16384.bmp");
    texture[15] = IMG_LoadTexture(renderer,"32768.bmp");
    texture[16] = IMG_LoadTexture(renderer,"65536.bmp");
    texture[17] = IMG_LoadTexture(renderer,"131072.bmp");
}

int get_index_col(int j)
{
    int y = START_COL + STEP*j;
    return y;
}

int get_index_row(int i)
{
    int x = START_ROW + STEP*i;
    return x;
}

void print_image(SDL_Texture* texturee, int x, int y)
{
    SDL_Rect dest = {x, y, 119, 119};
    SDL_RenderCopy(renderer, texturee, NULL, &dest);
}

void new_game()
{
    for(int i = 0; i < NUM; i++)
	{
		for(int j = 0; j < NUM; j++)
		{
			board[i][j].value = 0;
			board[i][j].done = false;
		}
	}
	//board[1][1].value = 2048;
	WIN_CHECK = false;
	SCORE = 0;
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
    board[a.row][a.col].value = random_new_number();
}

int random_new_number()
{
    int n;
    n = rand() % 10;
    if(n == 0) return 4;
    return 2;
}

int move_event(SDL_Event &e)
{
    int direction = -1;
    if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                direction = 2;
                break;
            case SDLK_DOWN:
                direction = 3;
                break;
            case SDLK_RIGHT:
                direction = 1;
                break;
            case SDLK_LEFT:
                direction = 0;
                break;
            default:
                break;
        }
    }
    return direction;
}

void print_board()
{
    cout << "PRINT BOARD\n";
    SDL_RenderCopy(renderer,texture[0],NULL,NULL);
	for(int i = 0; i < NUM; i++)
	{
		for(int j = 0; j < NUM; j++)
		{
			if(board[i][j].value)
			{
				print_number(board[i][j].value, get_index_row(j), get_index_col(i));
				cout << setw(5) << board[i][j].value;
			}
			else
            {
                cout << setw(5) << ".";
            }
		}
		cout << endl;
	}
	cout << "SCORE = " << SCORE << endl;
}

bool inside(int a)
{
    if(a >= 0 && a < NUM) return true;
    return false;
}

void move_num(SDL_Event &e)
{
    int direction = move_event(e);
    bool check = true, add = false;
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
                        SCORE += board[nextI][nextJ].value;
                        board[nextI][nextJ].done = true;
                        board[i][j].done = true;
                        board[i][j].value = 0;
                        //print_board();
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
        //print_board();
        index_to_num(); //genderate new number
        //SDL_Delay(1);
        print_board();
    }
    reset_false();
}

void print_number(int n, int x, int y)
{
    switch(n)
    {
        case 2:
            print_image(texture[1], x, y);
            break;
        case 4:
            print_image(texture[2], x, y);
            break;
        case 8:
            print_image(texture[3], x, y);
            break;
        case 16:
            print_image(texture[4], x, y);
            break;
        case 32:
            print_image(texture[5], x, y);
            break;
        case 64:
            print_image(texture[6], x, y);
            break;
        case 128:
            print_image(texture[7], x, y);
            break;
        case 256:
            print_image(texture[8], x, y);
            break;
        case 512:
            print_image(texture[9], x, y);
            break;
        case 1024:
            print_image(texture[10], x, y);
            break;
        case 2048:
            print_image(texture[11], x, y);
            break;
        case 4096:
            print_image(texture[12], x, y);
            break;
        case 8192:
            print_image(texture[13], x, y);
            break;
        case 16384:
            print_image(texture[14], x, y);
            break;
        case 32768:
            print_image(texture[15], x, y);
            break;
        case 65536:
            print_image(texture[16], x, y);
            break;
        case 131072:
            print_image(texture[17], x, y);
            break;
        default:
            break;
    }
}

void reset_false()
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            board[i][j].done = false;
        }
    }
}

bool full_board()
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            if(!board[i][j].value)
            {
                return false;
            }
        }
    }
    return true;
}

bool win()
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

bool check_move_lose()
{
    for(int i = 0; i < NUM; i++)
    {
        for(int j = 0; j < NUM; j++)
        {
            if(equal_num(i, j))
            {
                return false;
            }
        }
    }
    return true;
}

bool lose()
{
    if(full_board() && check_move_lose()) return true;
    return false;
}

bool equal_num(const int &i,const int &j)
{
    int a, b, c, d, e, f;
    a = i;
    b = i + 1;
    c = i - 1;
    d = j;
    e = j + 1;
    f = j - 1;
    if(inside(e))
    {
        if(board[a][e].value == board[a][d].value)
        {
            return true;
        }
    }
    if(inside(f))
    {
        if(board[a][f].value == board[a][d].value)
        {
            return true;
        }
    }
    if(inside(b))
    {
        if(board[b][d].value == board[a][d].value)
        {
            return true;
        }
    }
    if(inside(c))
    {
        if(board[c][d].value == board[a][d].value)
        {
            return true;
        }
    }
    return false;
}

void close()
{
	//Free loaded image
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Destroy Texture
	/*SDL_DestroyTexture(text);
	text = NULL;*/

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while(true)
    {
        if(SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ) //xac dinh su kien ban phim
            return;
        SDL_Delay(100);  //deday 100ms
    }
}
            /*print_image("grid.bmp", 0, 0);
            while(true)
            {
                SDL_PumpEvents();
                int x, y;
                SDL_GetMouseState(&x,&y);
                cout << x << ' ' <<y<< '\n';
                SDL_Delay(1000);
            }*/

