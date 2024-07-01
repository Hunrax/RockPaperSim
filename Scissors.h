#pragma once
#include "Object.h"
class Scissors : public Object
{
public:
	Scissors(int x, int y)
	{
		xPosition = x;
		yPosition = y;
		image = SDL_LoadBMP("./images/scissors.bmp");
		type = SCISSORS;
	}
};

