#ifndef LBUTTON_H
#define LBUTTON_H

#include <SDL.h>

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition(int x, int y);

		//Handles mouse event
		bool Inside(int BUTTON_WIDTH, int BUTTON_HEIGHT, int x, int y);

	private:
		//Top left position
		SDL_Point mPosition;
};


#endif // LBUTTON_H
