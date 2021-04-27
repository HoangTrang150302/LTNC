2048 GAME REFERENCES:
1. 2048 Logic Game
https://www.youtube.com/watch?v=tGWhk47ZIm4
2. 2048 SDL
https://lazyfoo.net/tutorials/SDL/index.php
3. 2048 Load Image SDL
https://bitbucket.org/thailamha/tictactoe/src/master/draw.cpp
4. 2048 number Image
https://github.com/melehean/2048-SDL/tree/master/2048_SDL/GRAFIKA

HOW TO PLAY:
1. Start Menu
Press PLAY to enter the game
(You cannot quit the game at this stage)
2. The main game
- Use arrow keys to play
- Press N to start a new game
- Press ESC to quit the current game
3. If you get to the 2048 title, the win menu will be displayed
- Click "continue" button to keep playing 
- Click "new game" button to start a new game
- Click "quit" button to quit game
4. If you lose, the lose menu will be displayed
- Click "new game" button to start a new game
- Click "quit" button to quit game

SOME MODIFICATIONS:
1. Logic game: All the logic game functions are in LOGIC_GAME.h and LOGIC_GAME.cpp file
- Use struct BOARD consists of 2 members value and done instead of the use of int 4x4 array: the BOARD class
- Generate both "2" and "4" number instead of just "2" number.
- Add score and high score
- Add lose and win condition
2. Game graphic: All the graphic functions are in LOGIC_GAME.h and LOGIC_GAME.cpp file
- Update screen function
- Show menu function, show button
- Print score and high score
- Play sound effect: when click any button the sound effect will be played
- Load image to the screen
