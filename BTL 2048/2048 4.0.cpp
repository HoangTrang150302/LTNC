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

SDL_Surface* surface[TEXTURE_NUM]; //the surface for image
SDL_Texture* texture[TEXTURE_NUM]; //the texture for image

//The window we'll be rendering to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* renderer = NULL;

BOARD board[NUM][NUM];

//FUNCTION PROTOTYPE

//Starts up SDL and creates window
void init();

//Start a new game
void new_game(bool &win_check, int &score, int &high_score);

//Convert keyboard event to dirRow, dirCol index number
int move_event(SDL_Event &e);

//Print the number on the board
void print_board(int& score, int &high_score);

//Check whether the index inside the board or not
bool inside(int);

//Postion to number on the board
void generate_new_number();

//Move number
void move_num(SDL_Event &e, int& score, int& high_score);

//Print image corresponding to number
void print_number(int n, int x, int y) ;

//Reset the board.done to false
void reset_false();

//Check if the player get to 2048 title
bool win();

//Check if the player lose or not
bool lose();

void close();
void print_score(int& score, int x, int y);

void loadMedia(int ob,int x,int y)
{
	SDL_Rect dest = {x, y,surface[ob]->w,surface[ob]->h};
    SDL_RenderCopy(renderer, texture[ob], NULL, &dest);
}

int main(int argc, char* argv[])
{
    //Variable Declaration
    int score = 0; // the player score
    bool win_check = false; //the player could only win once
    bool quit = false; //quit game

    SDL_Event e; //event

    //INIT Window
	init();

    //INPUT FILE HIGH SCORE
    ifstream high_score_file;
    high_score_file.open("high_score.txt");
    int high_score; //high score
    high_score_file >> high_score;
    cout << "HIGH SCORE: " << high_score << endl;
    high_score_file.close();

	srand(time(0));

	//START MENU
	bool quitstart = false;
	while(!quitstart)
    {
        while(SDL_PollEvent(&e))
        {
            loadMedia(18, 0, 0); //print the startmenu
            SDL_RenderPresent(renderer);
            loadMedia(20, 120, 450); //new game black
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(!(e.button.x >= 120 && e.button.x <= 120+364 && e.button.y >= 450 && e.button.y <= 450+90))
                {
                     loadMedia(20, 120, 450); //new game black
                }
                else
                {
                    loadMedia(21, 120, 450); // new game red
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
    new_game(win_check, score, high_score);
    //GAME LOOP
    while(!quit)
    {
        SDL_RenderPresent(renderer);
        if(win() && !win_check)
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
                     new_game(win_check, score, high_score);
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
                    new_game(win_check, score, high_score);
                }
                else
                {
                    if(move_event(e) >= 0)
                    {
                        move_num(e, score, high_score);
                        SDL_RenderPresent(renderer);
                    }
                }
            }
        }
        if(lose())
        {
            cout << "You lose\n";
            while(SDL_WaitEvent(&e))
            {
                loadMedia(19, 0, 0); //print the startmenu

                //OUTPUT HIGH SCORE
                ofstream out_put_file;
                out_put_file.open("high_score.txt", ofstream::trunc);
                out_put_file << score;
                out_put_file.close();
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
            new_game(win_check, score, high_score);
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

	//Init true type font
    if(TTF_Init() == -1) cout << "TTF_INIT error\n";

    //Create window
    window = SDL_CreateWindow("2048_Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Load texture
    surface[0] = SDL_LoadBMP("background.bmp");
	texture[0] = SDL_CreateTextureFromSurface(renderer, surface[0]);

    surface[1] = SDL_LoadBMP("2.bmp");
    texture[1] = SDL_CreateTextureFromSurface(renderer, surface[1]);

    surface[2] = SDL_LoadBMP("4.bmp");
    texture[2] = SDL_CreateTextureFromSurface(renderer, surface[2]);

    surface[3] = SDL_LoadBMP("8.bmp");
    texture[3] = SDL_CreateTextureFromSurface(renderer, surface[3]);

    surface[4] = SDL_LoadBMP("16.bmp");
    texture[4] = SDL_CreateTextureFromSurface(renderer, surface[4]);

    surface[5] = SDL_LoadBMP("32.bmp");
    texture[5] = SDL_CreateTextureFromSurface(renderer, surface[5]);

    surface[6] = SDL_LoadBMP("64.bmp");
    texture[6] = SDL_CreateTextureFromSurface(renderer, surface[6]);

    surface[7] = SDL_LoadBMP("128.bmp");
    texture[7] = SDL_CreateTextureFromSurface(renderer, surface[7]);

    surface[8] = SDL_LoadBMP("256.bmp");
    texture[8] = SDL_CreateTextureFromSurface(renderer, surface[8]);

    surface[9] = SDL_LoadBMP("512.bmp");
    texture[9] = SDL_CreateTextureFromSurface(renderer, surface[9]);

    surface[10] = SDL_LoadBMP("1024.bmp");
    texture[10] = SDL_CreateTextureFromSurface(renderer, surface[10]);

    surface[11] = SDL_LoadBMP("2048.bmp");
    texture[11] = SDL_CreateTextureFromSurface(renderer, surface[11]);

    surface[12] = SDL_LoadBMP("4096.bmp");
    texture[12] = SDL_CreateTextureFromSurface(renderer, surface[12]);

    surface[13] = SDL_LoadBMP("8192.bmp");
    texture[13] = SDL_CreateTextureFromSurface(renderer, surface[13]);

    surface[14] = SDL_LoadBMP("16384.bmp");
    texture[14] = SDL_CreateTextureFromSurface(renderer, surface[14]);

    surface[15] = SDL_LoadBMP("32768.bmp");
    texture[15] = SDL_CreateTextureFromSurface(renderer, surface[15]);

    surface[16] = SDL_LoadBMP("65536.bmp");
    texture[16] = SDL_CreateTextureFromSurface(renderer, surface[16]);

    surface[17] = SDL_LoadBMP("131072.bmp");
    texture[17] = SDL_CreateTextureFromSurface(renderer, surface[17]);

    surface[18] = SDL_LoadBMP("startmenu.bmp");
    texture[18] = SDL_CreateTextureFromSurface(renderer, surface[18]);

    surface[19] = SDL_LoadBMP("end_game.bmp");
    texture[19] = SDL_CreateTextureFromSurface(renderer, surface[19]);

    surface[20] = SDL_LoadBMP("newgame_black.bmp");
    texture[20] = SDL_CreateTextureFromSurface(renderer, surface[20]);

    surface[21] = SDL_LoadBMP("newgame_red.bmp");
    texture[21] = SDL_CreateTextureFromSurface(renderer, surface[21]);
}

void print_number(int n, int x, int y)
{
    switch(n)
    {
        case 2:
            loadMedia(1, x, y);
            break;
        case 4:
            loadMedia(2, x, y);
            break;
        case 8:
            loadMedia(3, x, y);
            break;
        case 16:
            loadMedia(4, x, y);
            break;
        case 32:
            loadMedia(5, x, y);
            break;
        case 64:
            loadMedia(6, x, y);
            break;
        case 128:
            loadMedia(7, x, y);
            break;
        case 256:
            loadMedia(8, x, y);
            break;
        case 512:
            loadMedia(9, x, y);
            break;
        case 1024:
            loadMedia(10, x, y);
            break;
        case 2048:
            loadMedia(11, x, y);
            break;
        case 4096:
            loadMedia(12, x, y);
            break;
        case 8192:
            loadMedia(13, x, y);
            break;
        case 16384:
            loadMedia(14, x, y);
            break;
        case 32768:
            loadMedia(15, x, y);
            break;
        case 65536:
            loadMedia(16, x, y);
            break;
        case 131072:
            loadMedia(17, x, y);
            break;
        default:
            break;
    }
}

void new_game(bool &win_check, int &score, int &high_score)
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
    generate_new_number();
    generate_new_number();

    print_board(score, high_score);
    cout << "New Game\n";
}

void generate_new_number()
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
    int n = rand() % 10;
    if(n == 0)
    {
        board[index.row][index.col].value = 4;
    }
    else
    {
        board[index.row][index.col].value = 2;
    }
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

void print_board(int& score, int &high_score)
{
    cout << "PRINT BOARD\n";
    SDL_RenderClear(renderer);
    loadMedia(0,0,0); //print the background
	for(int i = 0; i < NUM; i++)
	{
		for(int j = 0; j < NUM; j++)
		{
			if(board[i][j].value)
			{
				print_number(board[i][j].value, START_ROW + STEP*j, START_COL + STEP*i);
				cout << setw(5) << board[i][j].value;
			}
			else
            {
                cout << setw(5) << ".";
            }
		}
		cout << endl;
	}
	SDL_RenderPresent(renderer);
	print_score(score, 330, 57);
	cout << "SCORE = " << score << endl;
	print_score(high_score, 470, 57);
}

bool inside(int a)
{
    if(a >= 0 && a < NUM) return true;
    return false;
}

void move_num(SDL_Event &e, int& score, int& high_score)
{
    int direction = move_event(e);
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
        for (int i = startLine; inside(i); i+= lineStep)
        {
            for (int j = startColumn; inside(j); j+= columnStep)
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
        generate_new_number(); //genderate new number
        if(score >= high_score)
        {
            high_score = score;
        }
        print_board(score, high_score);
    }
    reset_false();
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

bool lose()
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
            if(inside(e))
            {
                if(board[a][e].value == board[a][d].value)
                {
                    return false;
                }
            }
            if(inside(f))
            {
                if(board[a][f].value == board[a][d].value)
                {
                    return false;
                }
            }
            if(inside(b))
            {
                if(board[b][d].value == board[a][d].value)
                {
                    return false;
                }
            }
            if(inside(c))
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
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void print_score(int& score, int x, int y)
{
    string sscore = to_string(score);
    SDL_Color color = {255, 255, 255, 255};
    TTF_Font *font = TTF_OpenFont("Roboto-Black.ttf", 30);

    SDL_Surface* textSurface = NULL;
    textSurface = TTF_RenderText_Solid(font, sscore.c_str(), color);
    if(textSurface == NULL) cout << "textSurface error\n";

    SDL_Texture *text = NULL;
    text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text == NULL) cout << "text error\n";

    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};

    SDL_RenderCopy(renderer, text, NULL, &textRect);
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(textSurface);
    textSurface = NULL;
}
