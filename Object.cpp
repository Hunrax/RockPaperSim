#include "Object.h"

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