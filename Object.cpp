#include "Object.h"

void Object::move(double delta)
{
	double speed = 1 * delta * 1000 / TIMESPEED;

	if (direction == 45 || direction == 90 || direction == 135)
		if (xPosition < SCREEN_WIDTH - (OBJECT_SIZE / 2))
			xPosition += 1;
		else
			direction += 90;

	else if (direction == 225 || direction == 270 || direction == 315)
		if (xPosition > (OBJECT_SIZE / 2))
			xPosition -= 1;
		else
			direction += 90;

	if (direction == 135 || direction == 180 || direction == 225)
		if (yPosition < SCREEN_HEIGHT - (OBJECT_SIZE / 2))
			yPosition += 1;
		else
			direction += 90;

	else if (direction == 45 || direction == 315 || direction == 360)
		if (yPosition > (OBJECT_SIZE / 2))
			yPosition -= 1;
		else
			direction += 90;

	if (direction > 360)
		direction -= 360; 
}