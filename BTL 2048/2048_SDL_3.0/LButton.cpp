#include "LButton.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

bool LButton::Inside(int BUTTON_WIDTH, int BUTTON_HEIGHT, int pos_x, int pos_y)
{
    //Check if mouse is in button
	bool inside = true;

	if(pos_x < mPosition.x || pos_x > mPosition.x + BUTTON_WIDTH || pos_y < mPosition.y || pos_y > mPosition.y + BUTTON_HEIGHT)
    {
        inside = false;
    }
    return inside;
}
