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
	void checkCollisions(Object* object, int objectIndex);
	std::vector<Object> objects;
private:
	int rockObjects, paperObjects, scissorsObjects;
	bool HitboxFunction(int fMiddleX, int fMiddleY, int fSizeX, int fSizeY, int sMiddleX, int sMiddleY, int sSizeX, int sSizeY);
	bool IsPointInRect(int pointX, int pointY, int minX, int maxX, int minY, int maxY);
	void changeObject(Object* first, Object* second);
};

