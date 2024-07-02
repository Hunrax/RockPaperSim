#pragma once
#include "Object.h"
class Paper : public Object
{
public:
	Paper(int x, int y)
	{
		xPosition = x;
		yPosition = y;
		image = SDL_LoadBMP("./images/paper.bmp");
		type = PAPER;
		direction = (rand() % 4) * 90 + 45;
	}
};

