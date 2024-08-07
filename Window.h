#pragma once
#include "Simulation.h"

class Window
{
public:
	Window();
	bool run();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* scrtex;
	SDL_Surface* charset;
	SDL_Surface* screen;
	SDL_Surface* icon;
	Simulation* simulation;
	bool exitGame;
	void quit();
	void displayTexts(double worldTime);
	void handleObjects(double delta);
	bool checkGameOver();
	void displayMenu(double* time);
	void displayParametersSettings(double* time);
	void handleEvents(SDL_Event event, double* worldTime);
	void handlePlayerMovement(SDL_Event event, double delta);
};

