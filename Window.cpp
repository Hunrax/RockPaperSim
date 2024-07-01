#include "Window.h"
#include "HelperFunctions.h"	

Window::Window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		exit(0);
	}

	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);

	if (rc != 0)
	{
		SDL_Quit();
		exit(0);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "BULLET HELL");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	charset = SDL_LoadBMP("./images/cs8x8.bmp");
	if (charset == NULL)
	{
		quit();
		exit(0);
	}
	SDL_SetColorKey(charset, true, 0x000000);
}

bool Window::run()
{
	simulation = new Simulation(5, 5, 5);
	simulation->startSimulation();
	DrawRectangle(screen, 0, 0, 960, 720, ALMOND, ALMOND); 

	exitGame = false;
	while (!exitGame)
	{	

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		for (Object object : simulation->objects)
		{
			DrawSurface(screen, object.image, object.xPosition, object.yPosition);
		}

		SDL_Event event; // EVENTY

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					exitGame = 1;
			}
		}
	}
	quit();
	return false;
}

void Window::quit()
{
	if (charset)
		SDL_FreeSurface(charset);
	if (screen)
		SDL_FreeSurface(screen);
	if(scrtex)
		SDL_DestroyTexture(scrtex);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}