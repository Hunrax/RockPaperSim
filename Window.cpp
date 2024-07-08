#include "Window.h"
#include "HelperFunctions.h"	

Window::Window()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
		exit(0);

	int rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	if (rc != 0)
	{
		SDL_Quit();
		exit(0);
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "ROCK PAPER SCISSORS SIMULATION");

	icon = SDL_LoadBMP("./images/rock.bmp");
	SDL_SetWindowIcon(window, icon);

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_ENABLE);

	charset = SDL_LoadBMP("./images/cs8x8.bmp");
	if (charset == NULL)
	{
		quit();
		exit(0);
	}
	SDL_SetColorKey(charset, true, 0x000000);

	simulation = new Simulation(OBJECT_AMOUNT, OBJECT_AMOUNT, OBJECT_AMOUNT);
	exitGame = false;
}
bool Window::run()
{
	simulation->startSimulation();

	int t1 = SDL_GetTicks();
	double worldTime = 0;

	while (!exitGame)
	{	
		int t2 = SDL_GetTicks();
		double delta = (t2 - t1) * 0.001;
		t1 = t2;

		if(!simulation->checkifGameOver())
			worldTime += delta;

		DrawRectangle(screen, 0, 0, 960, 720, ALMOND, ALMOND);
		
		handleObjects(delta);

		displayTexts(worldTime);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					exitGame = true;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					exitGame = true;
			}
		}
	}
	quit();
	return false;
}
void Window::displayTexts(double worldTime)
{
	char text[128];
	DrawRectangle(screen, 749, 4, 207, 20, ALMOND, NAVY);
	sprintf(text, "AUTHOR: RADOSLAW GAJEWSKI");
	DrawString(screen, 755, 10, text, charset);

	DrawRectangle(screen, 4, 4, 120, 20, ALMOND, NAVY);
	sprintf(text, "TIME: %.1lf s", worldTime);
	DrawString(screen, 10, 10, text, charset);

	DrawRectangle(screen, 4, 696, 80, 20, ALMOND, NAVY);
	sprintf(text, "ROCK: %d", simulation->rockObjects);
	DrawString(screen, 10, 702, text, charset);

	DrawRectangle(screen, 445, 696, 90, 20, ALMOND, NAVY);
	sprintf(text, "PAPER: %d", simulation->paperObjects);
	DrawString(screen, 449, 702, text, charset);

	DrawRectangle(screen, 846, 696, 110, 20, ALMOND, NAVY);
	sprintf(text, "SCISSORS: %d", simulation->scissorsObjects);
	DrawString(screen, 850, 702, text, charset);
	DrawString(screen, 850, 702, text, charset);
}
void Window::handleObjects(double delta)
{
	for (int i = 0; i < simulation->objects.size(); i++)
	{
		if (!checkGameOver())
		{
			simulation->objects[i].move(delta);
			simulation->checkCollisions(&(simulation->objects[i]), i);
		}
		DrawSurface(screen, simulation->objects[i].image, simulation->objects[i].xPosition, simulation->objects[i].yPosition);

		char text[128];
		sprintf(text, "%d", simulation->objects[i].number);
		DrawRectangle(screen, simulation->objects[i].xPosition - 8, simulation->objects[i].yPosition - 8, 20, 14, NAVY, NAVY);

		int textShift = 0;
		if (simulation->objects[i].number < 10)
			textShift = 4;

		DrawString(screen, simulation->objects[i].xPosition - 5 + textShift, simulation->objects[i].yPosition - 5, text, charset);
	}
}
bool Window::checkGameOver()
{
	char text[128];
	char mvpText[128];
	int gameResult = simulation->checkifGameOver();

	if (gameResult != 0)
	{
		DrawRectangle(screen, 300, 320, 360, 80, ALMOND, NAVY);

		Object* mvp = simulation->findMVP();
		sprintf(mvpText, "M V P : %s %d - points: %d", mvp->typeToString().c_str(), mvp->number, mvp->points);

		if (gameResult == ROCK_WIN)
		{
			sprintf(text, "R O C K S   W I N !");
			DrawString(screen, 410, 345, text, charset);
			DrawString(screen, 375, 365, mvpText, charset);
		}
		else if (gameResult == PAPER_WIN)
		{
			sprintf(text, "P A P E R S   W I N !");
			DrawString(screen, 400, 345, text, charset);
			DrawString(screen, 370, 365, mvpText, charset);
		}
		else if (gameResult == SCISSORS_WIN)
		{
			sprintf(text, "S C I S S O R S   W I N !");
			DrawString(screen, 380, 345, text, charset);
			DrawString(screen, 355, 365, mvpText, charset);
		}
		return true;
	}
	return false;
}
void Window::quit()
{
	if (charset)
		SDL_FreeSurface(charset);
	if (screen)
		SDL_FreeSurface(screen);
	if (icon)
		SDL_FreeSurface(icon);
	if (scrtex)
		SDL_DestroyTexture(scrtex);
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}