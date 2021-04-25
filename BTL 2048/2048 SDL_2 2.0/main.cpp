#include <fstream>
#include "LButton.h"
#include "GRAPHIC.h"
using namespace std;

//Board number of row and col
const int NUM = 4;

//FUNCTION PROTOTYPE

//Start a new game
void new_game(bool &win_check, int &score, const int &NUM, BOARD** board);

//Convert keyboard event to dirRow, dirCol index number
int move_event(SDL_Event &e);

//Check whether the index inside the board or not
bool inside(int a, const int &NUM);

//Postion to number on the board
void generate_new_number(const int &NUM, BOARD** board);

//Move number
bool move_num(int direction, int& score, const int &NUM, BOARD** board);

//Reset the board.done to false
void reset_false(const int &NUM, BOARD** board);

//Check if the player get to 2048 title
bool win(const int &NUM, BOARD** board);

//Check if the player lose or not
bool lose(const int &NUM, BOARD** board);

int main(int argc, char* argv[])
{
    //Variable Declaration
    int score = 0; // the player score
    bool win_check = false; //the player could only win once
    bool quit = false; //quit game

    //The 4x4 board
    BOARD **board = new BOARD *[NUM];
    for(int i = 0; i < NUM; i++)
    {
        *(board + i) = new BOARD [NUM];
    }

    SDL_Event e; //event

    GRAPHIC graphic; // game graphic

    //INIT Window
	graphic.init();

    //INPUT FILE HIGH SCORE
    ifstream high_score_file;
    high_score_file.open("high_score.txt");
    int high_score; //high score
    high_score_file >> high_score;
    cout << "HIGH SCORE: " << high_score << endl;
    high_score_file.close();

	srand(time(0));

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
                if(button1.Inside(graphic.getSurface(20)->w, graphic.getSurface(20)->h, e.button.x, e.button.y))
                {
                    graphic.loadMedia(20, 110, 581); //play
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
        SDL_RenderPresent(graphic.getRenderer());
    }

    //GAME LOOP
    while(!quit)
    {
        if(win(NUM, board) && !win_check)
        {
            cout << "YOU WIN\n";
            win_check = true;
            bool check = false;

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
                        if(button[1].Inside(graphic.getSurface(24)->w, graphic.getSurface(24)->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(24, 110, 213); //continue button
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

                        if(button[2].Inside(graphic.getSurface(22)->w, graphic.getSurface(22)->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(22, 110, 398); //new game button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                    new_game(win_check, score, NUM, board);
                                    graphic.update(NUM, board, score, high_score);
                                    check = true;
                            }
                         }

                        if(button[3].Inside(graphic.getSurface(23)->w, graphic.getSurface(23)->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(23, 110, 585); //quit button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                return 0;
                            }
                         }
                    }
                 }
                 SDL_RenderPresent(graphic.getRenderer());
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
                    new_game(win_check, score, NUM, board);
                    graphic.update(NUM, board, score, high_score);
                }
                else
                {
                    int event_num = move_event(e);
                    if(event_num >= 0)
                    {
                        if(move_num(event_num, score, NUM, board))
                        {
                            generate_new_number(NUM, board); //genderate new number
                            if(score >= high_score)
                            {
                                high_score = score;
                            }
                            graphic.update(NUM, board, score, high_score);
                        }
                    }
                }
            }
            SDL_RenderPresent(graphic.getRenderer());
        }

        if(lose(NUM, board))
        {
            cout << "You lose\n";

            //OUTPUT HIGH SCORE
            ofstream out_put_file;
            out_put_file.open("high_score.txt", ofstream::trunc);
            out_put_file << high_score;
            out_put_file.close();

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
                        if(button[1].Inside(graphic.getSurface(22)->w, graphic.getSurface(22)->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(22, 110, 313); //new game button
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

                        if(button[2].Inside(graphic.getSurface(23)->w, graphic.getSurface(23)->h, e.button.x, e.button.y))
                        {
                            graphic.loadMedia(23, 110, 535); //quit button
                            if(e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                return 0;
                            }
                         }
                    }
                 }
                 SDL_RenderPresent(graphic.getRenderer());
              }
        }

    }
    delete board;
	//Free resources and close SDL
	graphic.close();
	return 0;
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
