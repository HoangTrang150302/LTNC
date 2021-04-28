#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <SDL_ttf.h>
#include <cmath>
#include <vector>
#include "LOGIC_GAME.h"
using namespace std;

class GRAPHIC
{
    public:
        void init();
        int log2(int n);
        void loadMedia(int ob,int x,int y);
        void print_number(int n, int x, int y);
        void update(const int &NUM, BOARD** board, int &score, int& high_score);
        void print_score(int& score, int x, int y);
        void close();

        //Convert keyboard event to dirRow, dirCol index number
        int move_event();

        //MENU
        void start_menu(LOGIC_GAME&);
        void win_menu(LOGIC_GAME&);
        void lose_menu(LOGIC_GAME&);

        //SOUND
        void play_sound(int n);

       //Screen dimension constants
        const int SCREEN_WIDTH = 596;
        const int SCREEN_HEIGHT = 762;

        //Background coordinate
        const int START_ROW = 35;
        const int START_COL = 192;
        const int STEP = 136;

        //Image surface and texture
        vector<SDL_Surface*> surface;
        vector<SDL_Texture*> texture;

        //Sound effect
        vector<Mix_Chunk*> music;

        //The window we'll be rendering to
        SDL_Window* window = NULL;

        //The window renderer
        SDL_Renderer* renderer = NULL;

        //SDL event
        SDL_Event e;
};

#endif // GRAPHIC_H
