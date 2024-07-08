#pragma once
#include "Common.h"

class Object
{
public:
	Object(int x, int y, enum ObjectType objectType, int objectNumber);
	int xPosition, yPosition, direction, number, points;
	SDL_Surface* image;
	enum ObjectType type;
	void move();
};
enum ObjectType
{
	ROCK,
	PAPER,
	SCISSORS
};