#include "Object.h"

Object::Object(int x, int y, enum ObjectType objectType, int objectNumber)
{
	xPosition = x;
	yPosition = y;
	type = objectType;
	direction = (rand() % 4) * 90 + 45;
	number = objectNumber;
	points = 0;
	speed = 1.0;
	playerControlled = false;

	if (objectType == PAPER)
		image = SDL_LoadBMP("./images/paper.bmp");
	else if (objectType == SCISSORS)
		image = SDL_LoadBMP("./images/scissors.bmp");
	else if (objectType == ROCK)
		image = SDL_LoadBMP("./images/rock.bmp");
}
void Object::move(double delta, char playerDirection)
{
	double finalSpeed = 1 * delta * 100 * speed;

	if (!playerControlled)
	{
		if (direction > 360)
			direction -= 360;
		if (direction < 0)
			direction += 360;

		if (direction == 45)
		{
			if (xPosition < SCREEN_WIDTH - (OBJECT_SIZE / 2) && yPosition >(OBJECT_SIZE / 2))
			{
				xPosition += 1 * finalSpeed;
				yPosition -= 1 * finalSpeed;
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
				xPosition += 1 * finalSpeed;
				yPosition += 1 * finalSpeed;
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
				xPosition -= 1 * finalSpeed;
				yPosition += 1 * finalSpeed;
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
				xPosition -= 1 * finalSpeed;
				yPosition -= 1 * finalSpeed;
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
	else
	{
		if (playerDirection == RIGHT && xPosition < SCREEN_WIDTH - (OBJECT_SIZE / 2))
			xPosition += 2 * finalSpeed;
		else if (playerDirection == LEFT && xPosition > (OBJECT_SIZE / 2))
			xPosition -= 2 * finalSpeed;

		if (playerDirection == DOWN && yPosition < SCREEN_HEIGHT - (OBJECT_SIZE / 2))
			yPosition += 2 * finalSpeed;
		else if (playerDirection == UP && yPosition > (OBJECT_SIZE / 2))
			yPosition -= 2 * finalSpeed;
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