#pragma once
#include "Object.h"

class Simulation
{
public:
	int rockObjects, paperObjects, scissorsObjects;
	bool rockObjectsSet, paperObjectsSet, scissorsObjectsSet;
	std::vector<Object> objects;
	bool simulationStarted;
	double simulationSpeed;
	Simulation();
	void startSimulation();
	void checkCollisions(Object* object, int objectIndex, double delta);
	int checkifGameOver();
	Object* findMVP();
	void changeSimulationSpeed(int value);
private:
	void generateObject(enum ObjectType type);
	bool HitboxFunction(int fMiddleX, int fMiddleY, int fSizeX, int fSizeY, int sMiddleX, int sMiddleY, int sSizeX, int sSizeY);
	bool IsPointInRect(int pointX, int pointY, int minX, int maxX, int minY, int maxY);
	void changeObject(Object* first, Object* second);
};

