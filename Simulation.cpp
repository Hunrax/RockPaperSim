#include "Simulation.h"

Simulation::Simulation()
{
	rockObjects = 0;
	paperObjects = 0;
	scissorsObjects = 0;

	rockObjectsSet = false;
	paperObjectsSet = false;
	scissorsObjectsSet = false;

	simulationSpeed = 1.0;
	simulationStarted = false;
	playerMode = false;
	playerMoved = false;
}
void Simulation::generateObject(enum ObjectType type)
{
	bool correctCoordinates = false;
	int x, y;
	while (correctCoordinates == false)
	{
		y = rand() % (SCREEN_HEIGHT - 2 * OBJECT_SIZE) + OBJECT_SIZE;
		x = rand() % (SCREEN_WIDTH - 2 * OBJECT_SIZE) + OBJECT_SIZE;

		if (objects.size() > 1)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (abs((objects[i].xPosition - x)) + abs((objects[i].yPosition - y)) < OBJECT_SIZE * (OBJECT_SIZE / (OBJECT_AMOUNT * 3)))
				{
					correctCoordinates = false;
					break;
				}
				correctCoordinates = true;
			}
		}
		else
			correctCoordinates = true;
	}
	bool sameNumber = true;
	int randomNumber;
	while (sameNumber == true)
	{
		randomNumber = rand() % 99 + 1;
		if (objects.size() > 1)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (randomNumber == objects[i].number)
				{
					sameNumber = true;
					break;
				}
				sameNumber = false;
			}
		}
		else
			sameNumber = false;
	}
	objects.push_back(Object(x, y, type, randomNumber));
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

	if (playerMode)
		drawPlayerControlledObject();

	simulationStarted = true;
}
void Simulation::checkCollisions(Object* object, int objectIndex, double delta)
{
	for (int i = objectIndex; i < objects.size(); i++)
	{
		if (HitboxFunction(object->xPosition, object->yPosition, OBJECT_SIZE / 4 * 3, OBJECT_SIZE / 4 * 3, objects[i].xPosition, objects[i].yPosition, OBJECT_SIZE / 4 * 3, OBJECT_SIZE / 4 * 3))
		{
			int tempDirection = objects[i].direction;
			objects[i].direction = object->direction;
			object->direction = tempDirection;

			if (object->direction == objects[i].direction)
				object->direction -= 90;

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
void Simulation::drawPlayerControlledObject()
{
	if (objects.size() > 0)
	{
		int randomNumber = rand() % objects.size();
		objects[randomNumber].playerControlled = true;
		playerControlledObject = &objects[randomNumber];
	}
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

			second->points++;
			first->points--;

			rockObjects--;
			paperObjects++;
		}
		if (second->type == SCISSORS)
		{
			second->type = ROCK;
			second->image = SDL_LoadBMP("./images/rock.bmp");

			first->points++;
			second->points--;

			scissorsObjects--;
			rockObjects++;
		}
	}
	else if (first->type == PAPER)
	{
		if (second->type == SCISSORS)
		{
			first->type = SCISSORS;
			first->image = SDL_LoadBMP("./images/scissors.bmp");

			second->points++;
			first->points--;

			paperObjects--;
			scissorsObjects++;
		}
		if (second->type == ROCK)
		{
			second->type = PAPER;
			second->image = SDL_LoadBMP("./images/paper.bmp");

			first->points++;
			second->points--;

			rockObjects--;
			paperObjects++;
		}
	}
	else if (first->type == SCISSORS)
	{
		if (second->type == PAPER)
		{
			second->type = SCISSORS;
			second->image = SDL_LoadBMP("./images/scissors.bmp");

			first->points++;
			second->points--;

			paperObjects--;
			scissorsObjects++;
		}
		if (second->type == ROCK)
		{
			first->type = ROCK;
			first->image = SDL_LoadBMP("./images/rock.bmp");

			second->points++;
			first->points--;

			scissorsObjects--;
			rockObjects++;
		}
	}
}
int Simulation::checkifGameOver()
{
	if (rockObjects + paperObjects + scissorsObjects < 2)
		return ZERO_OBJECTS;
	if (rockObjects == 0 && paperObjects == 0)
		return SCISSORS_WIN;
	if (rockObjects == 0 && scissorsObjects == 0)
		return PAPER_WIN;
	if (paperObjects == 0 && scissorsObjects == 0)
		return ROCK_WIN;

	return 0;
}
Object* Simulation::findMVP()
{
	Object* mvp = new Object(0, 0, ROCK, 0);
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].points > mvp->points)
			mvp = &objects[i];
	}
	return mvp;
}

void Simulation::changeSimulationSpeed(int value)
{
	if (value == INCREASE_SPEED)
		simulationSpeed *= 1.5;
	else if (value == DECREASE_SPEED)
		simulationSpeed /= 1.5;

	if (simulationSpeed > 15)
		simulationSpeed = 15;

	for (int i = 0; i < objects.size(); i++)
		objects[i].speed = simulationSpeed;
}
