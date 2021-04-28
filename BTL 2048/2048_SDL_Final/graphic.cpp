#include "GRAPHIC.h"
#include "LButton.h"
using namespace std;

void GRAPHIC::init()
{
    //Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Init true type font
    if(TTF_Init() < 0) cout << "TTF_INIT error\n";

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize!\n" << SDL_GetError() << endl;
    }

    //Create window
    window = SDL_CreateWindow("2048_Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    //Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Load texture
	surface.push_back(SDL_LoadBMP("graphic/background.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[0])); //background 2048

	for(int i = 1; i <= 17; i++)
    {
        double a = pow(2, i*1.0);
        string sa = to_string((int)a);
        string path = "graphic/" + sa + ".bmp";
        surface.push_back(SDL_LoadBMP(path.c_str()));
        texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[i]));
    }

	surface.push_back(SDL_LoadBMP("graphic/startmenu.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[18]));

	surface.push_back(SDL_LoadBMP("graphic/youlose.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[19]));

	surface.push_back(SDL_LoadBMP("graphic/play.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[20]));

	surface.push_back(SDL_LoadBMP("graphic/youwin.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[21]));

	surface.push_back(SDL_LoadBMP("graphic/newgame.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[22]));

	surface.push_back(SDL_LoadBMP("graphic/quit.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[23]));

	surface.push_back(SDL_LoadBMP("graphic/continue.bmp"));
	texture.push_back(SDL_CreateTextureFromSurface(renderer, surface[24]));

	//Load music
	music.push_back(Mix_LoadWAV("button_click.wav"));
    music.push_back(Mix_LoadWAV("win.wav"));
    music.push_back(Mix_LoadWAV("lose.wav"));
    music.push_back(Mix_LoadWAV("start.wav"));
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

void GRAPHIC::play_sound(int n)
{
    Mix_PlayChannel(-1, music[n], 0);
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

void GRAPHIC::print_score(int& score, int x, int y) //x, y are the position to load the score
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

    int _x = x + (129 - textSurface->w)/2; //129: the score box's width
    int _y = y + (67 - textSurface->h)/2; //67: the score box's height

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
    button1.setPosition(110, 581); //play button
    play_sound(3); //start.wav
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
                            play_sound(0); //button_click.wav
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
    button[1].setPosition(110, 213); //continue button
    button[2].setPosition(110, 398); //new game button
    button[3].setPosition(110, 585); //quit button
    play_sound(1);
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
                            play_sound(0);
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
                        play_sound(0);
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
                        play_sound(0);
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
    SDL_Delay(1000);
    play_sound(2); //lose sound
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
                            play_sound(0);
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
                        play_sound(0);
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

	//Free the sound effect
	for(unsigned int i = 0; i < music.size(); i++)
    {
        Mix_FreeChunk(music[i]);
        music[i] = NULL;
    }

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
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
