#pragma once
#include "Common.h"
#include "Simulation.h"

class Window
{
public:
	Window();
	bool run();
	void quit();
	void displayTexts(double worldTime);
	void handleObjects();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* scrtex;
	SDL_Surface* charset;
	SDL_Surface* screen;
	SDL_Surface* background;
	SDL_Surface* icon;
	Simulation* simulation;
	bool exitGame;
};

