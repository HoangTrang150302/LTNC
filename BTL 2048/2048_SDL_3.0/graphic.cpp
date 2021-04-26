#include "GRAPHIC.h"
#include "LButton.h"
#include "LOGIC_GAME.h"
using namespace std;

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
    window = SDL_CreateWindow("2048_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Load texture
	surface.push_back(SDL_LoadBMP("background.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[0])); //background 2048

	for(int i = 1; i <= 17; i++)
    {
        double a = pow(2, i*1.0);
        string sa = to_string((int)a);
        string path = sa + ".bmp";
        surface.push_back(SDL_LoadBMP(path.c_str()));
        texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[i]));
    }

	surface.push_back(SDL_LoadBMP("startmenu.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[18]));

	surface.push_back(SDL_LoadBMP("youlose.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[19]));

	surface.push_back(SDL_LoadBMP("play.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[20]));

	surface.push_back(SDL_LoadBMP("youwin.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[21]));

	surface.push_back(SDL_LoadBMP("newgame.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[22]));

	surface.push_back(SDL_LoadBMP("quit.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[23]));

	surface.push_back(SDL_LoadBMP("continue.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[24]));
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

int GRAPHIC::move_event()
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

void GRAPHIC::start_menu(LOGIC_GAME &game)
{
	//START MENU
	bool check = false;
    LButton button1;
    button1.setPosition(110, 581);
	while(!check)
    {
        while(SDL_PollEvent(&e))
        {
            loadMedia(18, 0, 0); //print the startmenu
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(button1.Inside(surface[20]->w, surface[20]->h, e.button.x, e.button.y))
                {
                    loadMedia(20, button1.mPosition.x, button1.mPosition.y); //play
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        cout << "mouse button down\n";
                        if(e.button.button == SDL_BUTTON_LEFT)
                        {
                            game.new_game();
                            update(game.NUM, game.board, game.score, game.high_score);
                            check = true;
                        }
                    }
                 }
            }
         }
        SDL_RenderPresent(renderer);
    }
}

void GRAPHIC::win_menu(LOGIC_GAME &game)
{
    bool check = false;
    LButton button[3];
    button[1].setPosition(110, 213); //continue
    button[2].setPosition(110, 398); //new game
    button[3].setPosition(110, 585); //quit
    while(!check)
    {
        while(SDL_PollEvent(&e))
        {
            loadMedia(21, 0, 0); //you win pic
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(button[1].Inside(surface[24]->w, surface[24]->h, e.button.x, e.button.y))
                {
                    loadMedia(24, button[1].mPosition.x, button[1].mPosition.y); //continue button
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        cout << "mouse button down\n";
                        if(e.button.button == SDL_BUTTON_LEFT)
                        {
                            update(game.NUM, game.board, game.score, game.high_score);
                            check = true;
                        }
                     }
                 }

                 if(button[2].Inside(surface[22]->w, surface[22]->h, e.button.x, e.button.y))
                 {
                    loadMedia(22, button[2].mPosition.x, button[2].mPosition.y); //new game button
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        game.new_game();
                        update(game.NUM, game.board, game.score, game.high_score);
                        check = true;
                    }
                 }

                 if(button[3].Inside(surface[23]->w, surface[23]->h, e.button.x, e.button.y))
                 {
                    loadMedia(23, button[3].mPosition.x, button[3].mPosition.y); //quit button
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        check = true;
                        game.quit = true;
                    }
                 }
            }
       }
       SDL_RenderPresent(renderer);
    }
}

void GRAPHIC::lose_menu(LOGIC_GAME &game)
{
    bool check = false;
    LButton button[2];
    button[1].setPosition(110, 313); //new game
    button[2].setPosition(110, 535); //quit
    while(!check)
    {
        while(SDL_PollEvent(&e))
        {
            loadMedia(19, 0, 0); //you lose
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(button[1].Inside(surface[22]->w, surface[22]->h, e.button.x, e.button.y))
                {
                    loadMedia(22, button[1].mPosition.x, button[1].mPosition.y); //new game button
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        cout << "mouse button down\n";
                        if(e.button.button == SDL_BUTTON_LEFT)
                        {
                            game.new_game();
                            update(game.NUM, game.board, game.score, game.high_score);
                            check = true;
                        }
                    }
                }

                if(button[2].Inside(surface[23]->w, surface[23]->h, e.button.x, e.button.y))
                {
                    loadMedia(23, button[2].mPosition.x, button[2].mPosition.y); //quit button
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        game.quit = true;
                        check = true;
                    }
                }
           }
       }
       SDL_RenderPresent(renderer);
    }
}

void GRAPHIC::close()
{
	//Free loaded image
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	for(unsigned int i = 0; i < surface.size(); i++)
    {
        free(surface[i]);
        surface[i] = NULL;
    }

    for(unsigned int i = 0; i < texture.size(); i++)
    {
        SDL_DestroyTexture(texture[i]);
        texture[i] = NULL;
    }

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
