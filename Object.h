#pragma once
#include "Common.h"

class Object
{
public:
	int xPosition, yPosition;
	SDL_Surface* image;
	enum ObjectType type;
	void move(double delta);
protected:
	int direction;
};
enum ObjectType
{
	ROCK,
	PAPER,
	SCISSORS
};