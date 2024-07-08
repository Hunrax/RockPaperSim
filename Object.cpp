#include "Object.h"

Object::Object(int x, int y, enum ObjectType objectType, int objectNumber)
{
	xPosition = x;
	yPosition = y;
	type = objectType;
	direction = (rand() % 4) * 90 + 45;
	number = objectNumber;
	points = 0;

	if (objectType == PAPER)
		image = SDL_LoadBMP("./images/paper.bmp");
	else if (objectType == SCISSORS)
		image = SDL_LoadBMP("./images/scissors.bmp");
	else if (objectType == ROCK)
		image = SDL_LoadBMP("./images/rock.bmp");
}
void Object::move(double delta)
{
	double speed = 1 * delta * 100;

	if (direction > 360)
		direction -= 360;
	if (direction < 0)
		direction += 360;

	if (direction == 45)
	{
		if (xPosition < SCREEN_WIDTH - (OBJECT_SIZE / 2) && yPosition > (OBJECT_SIZE / 2))
		{
			xPosition += 1 * speed;
			yPosition -= 1 * speed;
		}
		else
		{
			if (xPosition >= SCREEN_WIDTH - (OBJECT_SIZE / 2))
				direction -= 90;
			else
				direction += 90;
		}
	}
	else if (direction == 135)
	{
		if (xPosition < SCREEN_WIDTH - (OBJECT_SIZE / 2) && yPosition < SCREEN_HEIGHT - (OBJECT_SIZE / 2))
		{
			xPosition += 1 * speed;
			yPosition += 1 * speed;
		}
		else
		{
			if (xPosition >= SCREEN_WIDTH - (OBJECT_SIZE / 2))
				direction += 90;
			else
				direction -= 90;
		}
	}
	else if (direction == 225)
	{
		if (xPosition > (OBJECT_SIZE / 2) && yPosition < SCREEN_HEIGHT - (OBJECT_SIZE / 2))
		{
			xPosition -= 1 * speed;
			yPosition += 1 * speed;
		}
		else
		{
			if (yPosition >= SCREEN_HEIGHT - (OBJECT_SIZE / 2))
				direction += 90;
			else
				direction -= 90;
		}
	}
	else if (direction == 315)
	{
		if (xPosition > (OBJECT_SIZE / 2) && yPosition > (OBJECT_SIZE / 2))
		{
			xPosition -= 1 * speed;
			yPosition -= 1 * speed;
		}
		else
		{
			if (yPosition <= OBJECT_SIZE / 2)
				direction -= 90;
			else
				direction += 90;
		}
	}
}
std::string Object::typeToString()
{
	if (type == PAPER)
		return "Paper";
	else if (type == SCISSORS)
		return "Scissors";
	else if (type == ROCK)
		return "Rock";
}