#include "Object.h"

Object::Object(int x, int y, enum ObjectType objectType, int objectNumber)
{
	xPosition = x;
	yPosition = y;
	type = objectType;
	direction = (rand() % 4) * 90 + 45;
	number = objectNumber;

	if (objectType == PAPER)
		image = SDL_LoadBMP("./images/paper.bmp");
	else if (objectType == SCISSORS)
		image = SDL_LoadBMP("./images/scissors.bmp");
	else if (objectType == ROCK)
		image = SDL_LoadBMP("./images/rock.bmp");

}

void Object::move()
{
	if (direction > 360)
		direction -= 360;
	if (direction < 0)
		direction += 360;

	if (direction == 45)
	{
		if (xPosition < SCREEN_WIDTH - (OBJECT_SIZE / 2) && yPosition > (OBJECT_SIZE / 2))
		{
			xPosition += 1;
			yPosition -= 1;
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
			xPosition += 1;
			yPosition += 1;
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
			xPosition -= 1;
			yPosition += 1;
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
			xPosition -= 1;
			yPosition -= 1;
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