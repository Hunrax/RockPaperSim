#pragma once
#include "Object.h"

class Simulation
{
public:
	Simulation(int rocks, int papers, int scissors)
	{
		rockObjects = rocks;
		paperObjects = papers;
		scissorsObjects = scissors;
	}
	void generateObject(enum ObjectType type);
	void startSimulation();
	std::vector<Object> objects;
private:
	int rockObjects, paperObjects, scissorsObjects;
};

