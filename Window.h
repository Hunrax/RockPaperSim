#pragma once
#include "Common.h"
#include "Simulation.h"

class Window
{
public:
	Window();
	bool run();
	void quit();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* charset;
	SDL_Texture* scrtex;
	SDL_Surface* screen;
	SDL_Surface* background;
	Simulation* simulation;
	bool exitGame;
};

