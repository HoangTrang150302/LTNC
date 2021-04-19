#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <SDL_ttf.h>
#include <fstream>
using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 596;
const int SCREEN_HEIGHT = 762;
const string WINDOW_TITLE = "2048_Game";

//Background coordinate
const int START_ROW = 35;
const int START_COL = 192;
const int STEP = 136;

//Board number of row and col
const int NUM = 4;

//Number of texture
const int TEXTURE_NUM = 22;

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

const int dir_Row[4] = {0,0,-1,1}; //left:0 - right:1 - up:2 - down:3
const int dir_Col[4] = {-1,1,0,0}; //left:0 - right:1 - up:2 - down:3

//FUNCTION PROTOTYPE

//Starts up SDL and creates window
void init(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* texture[18]);

//Start a new game
void new_game(BOARD board[NUM][NUM], bool &win_check, int &score, SDL_Renderer* &renderer, SDL_Texture* texture[TEXTURE_NUM], TTF_Font* font, SDL_Color color, int high_score);

//Board index to background coordinate
int get_index_row(int x);
int get_index_col(int y);

//Random number position
INDEX random_position(BOARD board[NUM][NUM]);

//Convert keyboard event to dirRow, dirCol index number
int move_event(SDL_Event &e);

//Print the number on the board
void print_board(BOARD board[NUM][NUM], int& score, SDL_Renderer* &renderer, SDL_Texture* texture[TEXTURE_NUM], TTF_Font* font, SDL_Color color, int high_score);

//Check whether the index inside the board or not
bool inside(int);

//Postion to number on the board
void index_to_num(BOARD board[NUM][NUM]);

//Move number
void move_num(SDL_Event &e, BOARD board[NUM][NUM], int& score, SDL_Renderer* &renderer, SDL_Texture* texture[TEXTURE_NUM], TTF_Font* font, SDL_Color color, int high_score);

//Print image corresponding to number
void print_number(int n, int x, int y, SDL_Texture* texture[TEXTURE_NUM], SDL_Renderer* &renderer);

//Reset the board.done to false
void reset_false(BOARD board[NUM][NUM]);

//Check if all the board contain value
bool full_board(BOARD board[NUM][NUM]);

//Check if the player get to 2048 title
bool win(BOARD board[NUM][NUM]);

//Check if the player lose or not
bool lose(BOARD board[NUM][NUM]);
bool check_move_lose(BOARD board[NUM][NUM]);
bool equal_num(const int &i,const int &j, BOARD board[NUM][NUM]);

//Random new number 2 or 4
int random_new_number();

void close(SDL_Renderer*&, SDL_Window*&);
void waitUntilKeyPressed();
void print_score(int& score, int x, int y, SDL_Renderer* &renderer, TTF_Font* font, SDL_Color color);

int main(int argc, char* argv[])
{
    //Variable Declaration
    int score = 0; // the player score
    bool win_check = false; //the player could only win once
    bool quit = false; //quit game

    //The 4x4 board
    BOARD board[NUM][NUM];

    //SDL Variable
    SDL_Window* window; //The window will be render to
    SDL_Renderer* renderer; // renderer
    SDL_Texture* texture[TEXTURE_NUM]; //the texture for image
    SDL_Event e; //event

    //INIT Window
	init(window, renderer, texture);

    //INPUT FILE
    ifstream high_score_file;
    high_score_file.open("high_score.txt");
    int high_score; //high score
    high_score_file >> high_score;
    cout << "HIGH SCORE: " << high_score << endl;
    high_score_file.close();

	//True Type Font
    TTF_Font *font = TTF_OpenFont("Roboto-Thin.ttf", 10);
    SDL_Color color = {255, 255, 255, 255};

	srand(time(0));

	//START MENU
	bool quitstart = false;
	while(!quitstart)
    {
        while(SDL_PollEvent(&e))
        {
            SDL_RenderCopy(renderer,texture[18],NULL,NULL); //print the startmenu
            //SDL_RenderPresent(renderer);
            SDL_Rect newgamerect = {120, 450, 364, 90};
            SDL_RenderCopy(renderer,texture[20],NULL,&newgamerect); //new game black
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(!(e.button.x >= 120 && e.button.x <= 120+364 && e.button.y >= 450 && e.button.y <= 450+90))
                {
                    SDL_RenderCopy(renderer,texture[20],NULL,&newgamerect); //new game black
                }
                else
                {
                    SDL_RenderCopy(renderer,texture[21],NULL,&newgamerect); // new game red
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        cout << "mouse button down\n";
                        if(e.button.button == SDL_BUTTON_LEFT)
                        {
                            quitstart = true;
                        }
                    }
                }
            }
            SDL_RenderPresent(renderer);
        }
    }

	//Start a new game
    new_game(board, win_check, score, renderer, texture, font, color, high_score);

    //GAME LOOP
    while(!quit)
    {
        SDL_RenderPresent(renderer);
        if(win(board) && !win_check)
        {
            cout << "YOU WIN\n";
            win_check = true;
            cout << "Press ESC to quit, press N to start a new game, press arrow key to keep playing\n";
            if(e.type == SDL_KEYDOWN)
            {
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        quit = true;
                    }
                    else if(e.key.keysym.sym == SDLK_n)
                    {
                        new_game(board, win_check, score, renderer, texture, font, color, high_score);
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
                    new_game(board, win_check, score, renderer, texture, font, color, high_score);
                }
                else
                {
                    if(move_event(e) >= 0)
                    {
                        move_num(e, board, score, renderer, texture, font, color, high_score);
                        SDL_RenderPresent(renderer);
                    }
                }
            }
        }
        if(lose(board))
        {
            cout << "You lose\n";
            if(score > high_score)
            {
                ofstream out_put_file;
                out_put_file.open("high_score.txt", ofstream::trunc);
                out_put_file << score;
                out_put_file.close();
            }
            while(SDL_WaitEvent(&e))
            {
                SDL_RenderCopy(renderer,texture[19],NULL,NULL); //print the startmenu
                SDL_RenderPresent(renderer);
                if(e.type == SDL_KEYDOWN)
                {
                    if(e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 0;
                    }
                    if(e.key.keysym.sym == SDLK_n)
                    {
                        break;
                    }
                }
            }
            new_game(board, win_check, score, renderer, texture, font, color, high_score);
        }
    }
	//Free resources and close SDL
	close(renderer, window);
	return 0;
}

void init(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* texture[TEXTURE_NUM])
{
    //Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Init true type font
    if(TTF_Init() == -1) cout << "TTF_INIT error\n";

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
    texture[18] = IMG_LoadTexture(renderer,"startmenu.bmp");
    texture[19] = IMG_LoadTexture(renderer,"end_game.bmp");
    texture[20] = IMG_LoadTexture(renderer,"newgame_black.bmp");
    texture[21] = IMG_LoadTexture(renderer,"newgame_red.bmp");
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

void print_number(int n, int x, int y, SDL_Texture* texture[TEXTURE_NUM], SDL_Renderer* &renderer)
{
    SDL_Rect dest = {x, y, 119, 119}; //the destination rect
    switch(n)
    {
        case 2:
            SDL_RenderCopy(renderer, texture[1], NULL, &dest);
            break;
        case 4:
            SDL_RenderCopy(renderer, texture[2], NULL, &dest);
            break;
        case 8:
            SDL_RenderCopy(renderer, texture[3], NULL, &dest);
            break;
        case 16:
            SDL_RenderCopy(renderer, texture[4], NULL, &dest);
            break;
        case 32:
            SDL_RenderCopy(renderer, texture[5], NULL, &dest);
            break;
        case 64:
            SDL_RenderCopy(renderer, texture[6], NULL, &dest);
            break;
        case 128:
            SDL_RenderCopy(renderer, texture[7], NULL, &dest);
            break;
        case 256:
            SDL_RenderCopy(renderer, texture[8], NULL, &dest);
            break;
        case 512:
            SDL_RenderCopy(renderer, texture[9], NULL, &dest);
            break;
        case 1024:
            SDL_RenderCopy(renderer, texture[10], NULL, &dest);
            break;
        case 2048:
            SDL_RenderCopy(renderer, texture[11], NULL, &dest);
            break;
        case 4096:
            SDL_RenderCopy(renderer, texture[12], NULL, &dest);
            break;
        case 8192:
            SDL_RenderCopy(renderer, texture[13], NULL, &dest);
            break;
        case 16384:
            SDL_RenderCopy(renderer, texture[14], NULL, &dest);
            break;
        case 32768:
            SDL_RenderCopy(renderer, texture[15], NULL, &dest);
            break;
        case 65536:
            SDL_RenderCopy(renderer, texture[16], NULL, &dest);
            break;
        case 131072:
            SDL_RenderCopy(renderer, texture[17], NULL, &dest);
            break;
        default:
            break;
    }
}

void new_game(BOARD board[NUM][NUM], bool &win_check, int &score, SDL_Renderer* &renderer, SDL_Texture* texture[TEXTURE_NUM], TTF_Font* font, SDL_Color color, int high_score)
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
    index_to_num(board);
    index_to_num(board);

    print_board(board, score, renderer, texture, font, color, high_score);
    cout << "New Game\n";
}

INDEX random_position(BOARD board[NUM][NUM])
{
    INDEX index;
    bool check = true; // this variable to check that the new position do not contain any number
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

void index_to_num(BOARD board[NUM][NUM])
{
    INDEX a = random_position(board);
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

void print_board(BOARD board[NUM][NUM], int& score, SDL_Renderer* &renderer, SDL_Texture* texture[TEXTURE_NUM], TTF_Font* font, SDL_Color color,int high_score)
{
    cout << "PRINT BOARD\n";
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture[0],NULL,NULL); //print the background
	for(int i = 0; i < NUM; i++)
	{
		for(int j = 0; j < NUM; j++)
		{
			if(board[i][j].value)
			{
				print_number(board[i][j].value, get_index_row(j), get_index_col(i), texture, renderer);
				cout << setw(5) << board[i][j].value;
			}
			else
            {
                cout << setw(5) << ".";
            }
		}
		cout << endl;
	}
	print_score(score, 330, 57, renderer, font, color);
	cout << "SCORE = " << score << endl;
	print_score(high_score, 470, 57, renderer, font, color);
}

bool inside(int a)
{
    if(a >= 0 && a < NUM) return true;
    return false;
}

void move_num(SDL_Event &e, BOARD board[NUM][NUM], int& score, SDL_Renderer* &renderer, SDL_Texture* texture[TEXTURE_NUM], TTF_Font* font, SDL_Color color, int high_score)
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
                        score += board[nextI][nextJ].value;
                        board[nextI][nextJ].done = true;
                        board[i][j].done = true;
                        board[i][j].value = 0;
                        //print_board(board, score, renderer, texture, font, color);
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
        //print_board(board, score, renderer, texture);
        index_to_num(board); //genderate new number
       //DL_Delay(10);
        print_board(board, score, renderer, texture, font, color, high_score);
    }
    reset_false(board);
}



void reset_false(BOARD board[NUM][NUM])
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            board[i][j].done = false;
        }
    }
}

bool full_board(BOARD board[NUM][NUM])
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

bool win(BOARD board[NUM][NUM])
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

bool check_move_lose(BOARD board[NUM][NUM])
{
    for(int i = 0; i < NUM; i++)
    {
        for(int j = 0; j < NUM; j++)
        {
            if(equal_num(i, j, board))
            {
                return false;
            }
        }
    }
    return true;
}

bool lose(BOARD board[NUM][NUM])
{
    if(full_board(board) && check_move_lose(board)) return true;
    return false;
}

bool equal_num(const int &i,const int &j, BOARD board[NUM][NUM])
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

void close(SDL_Renderer* & renderer, SDL_Window* &window)
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
        if(SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)) //xac dinh su kien ban phim
            return;
        SDL_Delay(100);  //deday 100ms
    }
}

/*void LoadFromRenderText()
{
    //Load from render text
    SDL_Surface* textSurface = NULL;
    textSurface = TTF_RenderText_Solid(font, "HNMT", color);
    if(textSurface == NULL) cout << "textSurface error\n";
    SDL_Texture *text = NULL;
    text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text == NULL) cout << "text error\n";
    SDL_Rect textRect = {50, 50, 50, 50};
    SDL_RenderCopy(renderer, text, NULL, &textRect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(textSurface);
    textSurface = NULL;
}*/

void print_score(int& score, int x, int y, SDL_Renderer* &renderer, TTF_Font *font, SDL_Color color)
{
    string sscore = to_string(score);

    SDL_Surface* textSurface = NULL;
    textSurface = TTF_RenderText_Solid(font, sscore.c_str(), color);
    if(textSurface == NULL) cout << "textSurface error\n";

    SDL_Texture *text = NULL;
    text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text == NULL) cout << "text error\n";

    SDL_Rect textRect = {x, y, 40, 50};

    SDL_RenderCopy(renderer, text, NULL, &textRect);
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(textSurface);
    textSurface = NULL;
}

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

            	//MOUSE EVENT
    /*while(!quit)
    {
        //SDL_RenderCopy(renderer,texture[18],NULL,NULL); //print the startmenu
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    SDL_RenderCopy(renderer,texture[18],NULL,NULL); //print the startmenu
                    SDL_RenderPresent(renderer);
                }
                else if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    SDL_RenderCopy(renderer,texture[19],NULL,NULL); //print the endmenu
                    SDL_RenderPresent(renderer);
                }
            }
        }
    }*/
