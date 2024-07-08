#pragma once
#include "Common.h"

class Object
{
public:
	Object(int x, int y, enum ObjectType objectType, int objectNumber);
	double xPosition, yPosition, speed;
	int direction, number, points;
	SDL_Surface* image;
	enum ObjectType type;
	void move(double delta);
	std::string typeToString();
};
enum ObjectType
{
	ROCK,
	PAPER,
	SCISSORS
};