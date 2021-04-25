#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <SDL_ttf.h>
#include <cmath>
#include "BOARD.h"

class GRAPHIC
{
    public:
        GRAPHIC();
        ~GRAPHIC();

        void init();
        int log2(int n);
        void loadMedia(int ob,int x,int y);
        void print_number(int n, int x, int y);
        void update(const int &NUM, BOARD** board, int &score, int& high_score);
        void print_score(int& score, int x, int y);
        void close();

        SDL_Surface* getSurface(int n);
        SDL_Renderer* getRenderer();

    private:
        //Screen dimension constants
        const int SCREEN_WIDTH = 596;
        const int SCREEN_HEIGHT = 762;

        //Background coordinate
        const int START_ROW = 35;
        const int START_COL = 192;
        const int STEP = 136;

        SDL_Surface* surface[25]; //the surface for image
        SDL_Texture* texture[25]; //the texture for image

        //The window we'll be rendering to
        SDL_Window* window = NULL;

        //The window renderer
        SDL_Renderer* renderer = NULL;

};

#endif // GRAPHIC_H
