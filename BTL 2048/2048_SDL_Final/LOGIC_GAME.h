#ifndef LOGIC_GAME_H
#define LOGIC_GAME_H

#include "BOARD.h"
#include "LButton.h"

class LOGIC_GAME
{
    public:
        LOGIC_GAME();

        //Start a new game
        void new_game();

        //Check whether the index inside the board or not
        bool inside(int a);

        //Postion to number on the board
        void generate_new_number();

        //Move number
        bool move_num(int direction);

        //Reset the board.done to false
        void reset_false();

        //Check if the player get to 2048 title
        bool win();

        //Check if the player lose or not
        bool lose();

        const int NUM = 4;
        BOARD **board;
        bool win_check = false; //the player can only win once
        int score = 0;
        int high_score;
        bool quit = false;
};

#endif // LOGIC_GAME_H
