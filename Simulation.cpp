#include "Simulation.h"
#include "Rock.h"
#include "Paper.h"
#include "Scissors.h"

void Simulation::generateObject(ObjectType type)
{
	int y = rand() % SCREEN_HEIGHT;
	int x = rand() % SCREEN_WIDTH;
	switch (type)
	{
		case ROCK:
			objects.push_back(Rock(x, y));
			break;
		case PAPER:
			objects.push_back(Paper(x, y));
			break;
		case SCISSORS:
			objects.push_back(Scissors(x, y));
			break;
	}
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
