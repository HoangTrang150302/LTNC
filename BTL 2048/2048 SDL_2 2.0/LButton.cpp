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

bool LButton::Inside(int BUTTON_WIDTH, int BUTTON_HEIGHT, int x, int y)
{
    //Check if mouse is in button
	bool inside = true;

	if(x < mPosition.x || x > mPosition.x + BUTTON_WIDTH || y < mPosition.y || y > mPosition.y + BUTTON_HEIGHT)
    {
        inside = false;
    }
    return inside;
}
