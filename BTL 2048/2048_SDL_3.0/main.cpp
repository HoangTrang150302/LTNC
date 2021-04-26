#include <fstream>
#include "GRAPHIC.h"
#include "LOGIC_GAME.h"
using namespace std;

int main(int argc, char* argv[])
{
    LOGIC_GAME game;

    GRAPHIC graphic; // game graphic

    //The 4x4 board
    game.board = new BOARD *[game.NUM];

    for(int i = 0; i < game.NUM; i++)
    {
        *(game.board + i) = new BOARD [game.NUM];
    }

    //INIT Window
	graphic.init();

    //INPUT FILE HIGH SCORE
    ifstream high_score_file;
    high_score_file.open("high_score.txt");
    high_score_file >> game.high_score;
    cout << "HIGH SCORE: " << game.high_score << endl;
    high_score_file.close();

	srand(time(0));

	//START MENU
	graphic.start_menu(game);

    //GAME LOOP
    while(!game.quit)
    {
        //check if the player win or not
        if(game.win() && !game.win_check)
        {
            cout << "YOU WIN\n";
            game.win_check = true;

            //WIN MENU
            graphic.win_menu(game);
        }

        while(SDL_PollEvent(&graphic.e))
        {
            if(graphic.e.type == SDL_KEYDOWN)
            {
                if(graphic.e.key.keysym.sym == SDLK_ESCAPE)
                {
                    game.quit = true;
                }
                else if(graphic.e.key.keysym.sym == SDLK_n)
                {
                    game.new_game();
                    graphic.update(game.NUM, game.board, game.score, game.high_score);
                }
                else
                {
                    int direction = graphic.move_event();
                    if(direction >= 0)
                    {
                        if(game.move_num(direction))
                        {
                            game.generate_new_number(); //genderate new number
                            if(game.score >= game.high_score)
                            {
                                game.high_score = game.score;
                            }
                            graphic.update(game.NUM, game.board, game.score, game.high_score);
                        }
                    }
                }
            }
            SDL_RenderPresent(graphic.renderer);
        }

        if(game.lose())
        {
            cout << "You lose\n";

            //OUTPUT HIGH SCORE
            ofstream out_put_file;
            out_put_file.open("high_score.txt", ofstream::trunc);
            out_put_file << game.high_score;
            out_put_file.close();

            //LOSE MENU
            graphic.lose_menu(game);
        }
    }
    delete game.board;
	//Free resources and close SDL
	graphic.close();
	return 0;
}
