#pragma once
#include "Common.h"

class Object
{
public:
	int xPosition, yPosition;
	SDL_Surface* image;
	enum ObjectType type;
};
enum ObjectType
{
	ROCK,
	PAPER,
	SCISSORS
};