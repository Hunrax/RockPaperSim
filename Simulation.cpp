#include "Simulation.h"

void Simulation::generateObject(ObjectType type)
{
	int y = rand() % (SCREEN_HEIGHT - 2 * OBJECT_SIZE) + OBJECT_SIZE;
	int x = rand() % (SCREEN_WIDTH - 2 * OBJECT_SIZE) + OBJECT_SIZE;
	
	objects.push_back(Object(x, y, type));
}

void Simulation::startSimulation()
{
	srand(time(NULL));
	for (int i = 0; i < rockObjects; i++)
		generateObject(ROCK);
	for (int i = 0; i < paperObjects; i++)
		generateObject(PAPER);
	for (int i = 0; i < scissorsObjects; i++)
		generateObject(SCISSORS);
}
void Simulation::checkCollisions(Object* object, int objectIndex)
{
	for (int i = objectIndex; i < objects.size(); i++)
	{
		if (HitboxFunction(object->xPosition, object->yPosition, OBJECT_SIZE / 4 * 3, OBJECT_SIZE / 4 * 3, objects[i].xPosition, objects[i].yPosition, OBJECT_SIZE / 4 * 3, OBJECT_SIZE / 4 * 3))
		{
			if (object->direction < 180)
				object->direction += 180;
			else
				object->direction -= 180;

			if (objects[i].direction < 180)
				objects[i].direction += 180;
			else
				objects[i].direction -= 180;

			changeObject(object, &(objects[i]));
		}
	}
}

bool Simulation::IsPointInRect(int pointX, int pointY, int minX, int maxX, int minY, int maxY)
{
	if (pointX > minX && pointX < maxX && pointY > minY && pointY < maxY)
		return true;
	return false;
}

bool Simulation::HitboxFunction(int fMiddleX, int fMiddleY, int fSizeX, int fSizeY, int sMiddleX, int sMiddleY, int sSizeX, int sSizeY)
{
	if (IsPointInRect(fMiddleX - fSizeX / 2, fMiddleY - fSizeY / 2, sMiddleX - sSizeX / 2, sMiddleX + sSizeX / 2, sMiddleY - sSizeY / 2, sMiddleY + sSizeY / 2))
		return true;
	if (IsPointInRect(fMiddleX + fSizeX / 2, fMiddleY + fSizeY / 2, sMiddleX - sSizeX / 2, sMiddleX + sSizeX / 2, sMiddleY - sSizeY / 2, sMiddleY + sSizeY / 2))
		return true;
	if (IsPointInRect(fMiddleX - fSizeX / 2, fMiddleY + fSizeY / 2, sMiddleX - sSizeX / 2, sMiddleX + sSizeX / 2, sMiddleY - sSizeY / 2, sMiddleY + sSizeY / 2))
		return true;
	if (IsPointInRect(fMiddleX + fSizeX / 2, fMiddleY - fSizeY / 2, sMiddleX - sSizeX / 2, sMiddleX + sSizeX / 2, sMiddleY - sSizeY / 2, sMiddleY + sSizeY / 2))
		return true;

	return false;
}

void Simulation::changeObject(Object* first, Object* second)
{
	if (first->type == ROCK)
	{
		if (second->type == PAPER)
		{
			first->type = PAPER;
			first->image = SDL_LoadBMP("./images/paper.bmp");
		}
		if (second->type == SCISSORS)
		{
			second->type = ROCK;
			second->image = SDL_LoadBMP("./images/rock.bmp");
		}
	}
	else if (first->type == PAPER)
	{
		if (second->type == SCISSORS)
		{
			first->type = SCISSORS;
			first->image = SDL_LoadBMP("./images/scissors.bmp");
		}
		if (second->type == ROCK)
		{
			second->type = PAPER;
			second->image = SDL_LoadBMP("./images/paper.bmp");
		}
	}
	else if (first->type == SCISSORS)
	{
		if (second->type == PAPER)
		{
			second->type = SCISSORS;
			second->image = SDL_LoadBMP("./images/scissors.bmp");
		}
		if (second->type == ROCK)
		{
			first->type = ROCK;
			first->image = SDL_LoadBMP("./images/rock.bmp");
		}
	}
}