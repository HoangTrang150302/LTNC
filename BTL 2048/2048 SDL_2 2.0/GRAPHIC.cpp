#include "GRAPHIC.h"
using namespace std;

GRAPHIC::GRAPHIC()
{
    //ctor
}

GRAPHIC::~GRAPHIC()
{
    //dtor
}

void GRAPHIC::init()
{
    //Screen dimension constants
    const int SCREEN_WIDTH = 596;
    const int SCREEN_HEIGHT = 762;

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

	for(int i = 1; i <= 17; i++)
    {
        double a = pow(2, i*1.0);
        string sa = to_string((int)a);
        string path = sa + ".bmp";
        surface[i] = SDL_LoadBMP(path.c_str());
        texture[i] = SDL_CreateTextureFromSurface(renderer, surface[i]);
    }

    surface[18] = SDL_LoadBMP("startmenu.bmp");
    texture[18] = SDL_CreateTextureFromSurface(renderer, surface[18]);

    surface[19] = SDL_LoadBMP("youlose.bmp");
    texture[19] = SDL_CreateTextureFromSurface(renderer, surface[19]);

    surface[20] = SDL_LoadBMP("play.bmp");
    texture[20] = SDL_CreateTextureFromSurface(renderer, surface[20]);

    surface[21] = SDL_LoadBMP("youwin.bmp");
    texture[21] = SDL_CreateTextureFromSurface(renderer, surface[21]);

    surface[22] = SDL_LoadBMP("newgame.bmp");
    texture[22] = SDL_CreateTextureFromSurface(renderer, surface[22]);

    surface[23] = SDL_LoadBMP("quit.bmp");
    texture[23] = SDL_CreateTextureFromSurface(renderer, surface[23]);

    surface[24] = SDL_LoadBMP("continue.bmp");
    texture[24] = SDL_CreateTextureFromSurface(renderer, surface[24]);
}

int GRAPHIC::log2(int n)
{
    int count = 0;
    while(n != 1)
    {
        n = n/2;
        count++;
    }
    return count;
}

void GRAPHIC::print_number(int n, int x, int y)
{
    loadMedia(log2(n), x, y);
}

void GRAPHIC::loadMedia(int ob,int x,int y)
{
	SDL_Rect dest = {x, y,surface[ob]->w,surface[ob]->h};
    SDL_RenderCopy(renderer, texture[ob], NULL, &dest);
}

void GRAPHIC::update(const int &NUM, BOARD** board, int &score, int& high_score)
{
    cout << "PRINT BOARD\n";
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
	print_score(score, 292, 50);
	cout << "SCORE = " << score << endl;
	print_score(high_score, 432, 50);
	cout << "HIGH_SCORE = " << high_score << endl;
}

void GRAPHIC::print_score(int& score, int x, int y)
{
    string sscore = to_string(score);
    SDL_Color color = {255, 255, 255, 255};
    TTF_Font *font = TTF_OpenFont("Roboto-Black.ttf", 35);

    SDL_Surface* textSurface = NULL;
    textSurface = TTF_RenderText_Solid(font, sscore.c_str(), color);
    if(textSurface == NULL) cout << "textSurface error\n";

    SDL_Texture *text = NULL;
    text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text == NULL) cout << "text error\n";

    int _x = x + (129 - textSurface->w)/2;
    int _y = y + (67 - textSurface->h)/2;

    SDL_Rect textRect = {_x, _y, textSurface->w, textSurface->h};

    SDL_RenderCopy(renderer, text, NULL, &textRect);

    SDL_FreeSurface(textSurface);
    textSurface = NULL;
}

SDL_Surface* GRAPHIC::getSurface(int n)
{
    return surface[n];
}

SDL_Renderer* GRAPHIC::getRenderer()
{
    return renderer;
}

void GRAPHIC::close()
{
	//Free loaded image
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	for(int i = 0; i < 25; i++)
    {
        free(surface[i]);
        surface[i] = NULL;
    }

    for(int i = 0; i < 25; i++)
    {
        SDL_DestroyTexture(texture[i]);
        texture[i] = NULL;
    }

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
