#pragma once
#include "Object.h"
class Rock : public Object
{
public:
	Rock(int x, int y)
	{
		xPosition = x;
		yPosition = y;
		image = SDL_LoadBMP("./images/rock.bmp");
		type = ROCK;
		direction = (rand() % 4) * 90 + 45;
	}
};

