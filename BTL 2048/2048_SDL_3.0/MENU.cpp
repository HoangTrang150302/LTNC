#include "LButton.h"
#include "GRAPHIC.h"

void start_menu(GRAPHIC &graphic, SDL_Event &e)
{
	//START MENU
	bool check = false;
	while(!check)
    {
        LButton button1;
        button1.setPosition(110, 581);
        while(SDL_PollEvent(&e))
        {
            graphic.loadMedia(18, 0, 0); //print the startmenu
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(button1.Inside(graphic.surface[20]->w, graphic.surface[20]->h, e.button.x, e.button.y))
                {
                    graphic.loadMedia(20, button1.mPosition.x, button1.mPosition.y); //play
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        cout << "mouse button down\n";
                        if(e.button.button == SDL_BUTTON_LEFT)
                        {
                            new_game(win_check, score, NUM, board);
                            graphic.update(NUM, board, score, high_score);
                            check = true;
                        }
                    }
                 }
            }
         }
        SDL_RenderPresent(graphic.renderer);
    }
}

void win_menu(GRAPHIC &graphic, SDL_Event &e)
{
            //WIN MENU
            while(!check)
            {
                LButton button[3];
                button[1].setPosition(110, 213); //continue
                button[2].setPosition(110, 398); //new game
                button[3].setPosition(110, 585); //quit
                while(SDL_PollEvent(&e))
                {
                    graphic.loadMedia(21, 0, 0); //you win pic
                    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(button[1].Inside(graphic.surface[24]->w, graphic.surface[24]->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(24, button[1].mPosition.x, button[1].mPosition.y); //continue button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                cout << "mouse button down\n";
                                if(e.button.button == SDL_BUTTON_LEFT)
                                {
                                    graphic.update(NUM, board, score, high_score);
                                    check = true;
                                }
                            }
                         }

                        if(button[2].Inside(graphic.surface[22]->w, graphic.surface[22]->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(22, button[2].mPosition.x, button[2].mPosition.y); //new game button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                    new_game(win_check, score, NUM, board);
                                    graphic.update(NUM, board, score, high_score);
                                    check = true;
                            }
                         }

                        if(button[3].Inside(graphic.surface[23]->w, graphic.surface[23]->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(23, button[3].mPosition.x, button[3].mPosition.y); //quit button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                return 0;
                            }
                         }
                    }
                 }
                 SDL_RenderPresent(graphic.renderer);
              }
}

void lose_menu(GRAPHIC &graphic, SDL_Event &e)
{
            //LOSE MENU
            bool check = false;
            while(!check)
            {
                LButton button[2];
                button[1].setPosition(110, 313); //new game
                button[2].setPosition(110, 535); //quit
                while(SDL_PollEvent(&e))
                {
                    graphic.loadMedia(19, 0, 0); //you lose
                    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(button[1].Inside(graphic.surface[22]->w, graphic.surface[22]->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(22, button[1].mPosition.x, button[1].mPosition.y); //new game button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                cout << "mouse button down\n";
                                if(e.button.button == SDL_BUTTON_LEFT)
                                {
                                    new_game(win_check, score, NUM, board);
                                    graphic.update(NUM, board, score, high_score);
                                    check = true;
                                }
                            }
                         }

                        if(button[2].Inside(graphic.surface[23]->w, graphic.surface[23]->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(23, button[2].mPosition.x, button[2].mPosition.y); //quit button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                return 0;
                            }
                         }
                    }
                 }
                 SDL_RenderPresent(graphic.renderer);
              }
}
