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

	simulation = new Simulation();
	exitGame = false;
}
bool Window::run()
{
	int t1 = SDL_GetTicks();
	double worldTime = 0;
	double timeInMenu = 0;

	while (!exitGame)
	{	
		int t2 = SDL_GetTicks();
		double delta = (t2 - t1) * 0.001;
		t1 = t2;
		timeInMenu += delta;

		DrawRectangle(screen, 0, 0, 960, 720, ALMOND, ALMOND);
		
		if (simulation->simulationStarted)
		{
			if (!simulation->checkifGameOver() && ((simulation->playerMode && simulation->playerMoved) || !simulation->playerMode))
				worldTime += delta;

			checkGameOver();
			handleObjects(delta);
			displayTexts(worldTime);
		}
		else
		{
			displayMenu(&timeInMenu);
		}

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			handleEvents(event, worldTime);
		}
		handlePlayerMovement(event, delta);
		
	}
	quit();
	return false;
}
void Window::handleObjects(double delta)
{
	for (int i = 0; i < simulation->objects.size(); i++)
	{
		if (!checkGameOver())
		{
			simulation->checkCollisions(&(simulation->objects[i]), i, delta);
			if((!simulation->objects[i].playerControlled && simulation->playerMoved) || !simulation->playerMode)
				simulation->objects[i].move(delta, NONE);
		}
		DrawSurface(screen, simulation->objects[i].image, simulation->objects[i].xPosition, simulation->objects[i].yPosition);

		char text[128];
		sprintf(text, "%d", simulation->objects[i].number);
		if(!simulation->objects[i].playerControlled)
			DrawRectangle(screen, simulation->objects[i].xPosition - 8, simulation->objects[i].yPosition - 8, 20, 14, NAVY, NAVY);
		else
			DrawRectangle(screen, simulation->objects[i].xPosition - 8, simulation->objects[i].yPosition - 8, 20, 14, GREEN, GREEN);

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
		int mvpTextShift = 0;

		sprintf(mvpText, "M V P : %s %d - points: %d", mvp->typeToString().c_str(), mvp->number, mvp->points);
		if (simulation->playerMode)
		{
			if (mvp == simulation->playerControlledObject)
			{
				sprintf(mvpText, "M V P : %s %d (you) - points: %d", mvp->typeToString().c_str(), mvp->number, mvp->points);
				mvpTextShift = 16;
			}
		}
			
		if (gameResult == ROCK_WIN)
		{
			sprintf(text, "R O C K S   W I N !");
			DrawString(screen, 410, 345, text, charset);
			DrawString(screen, 375 - mvpTextShift, 365, mvpText, charset);
		}
		else if (gameResult == PAPER_WIN)
		{
			sprintf(text, "P A P E R S   W I N !");
			DrawString(screen, 400, 345, text, charset);
			DrawString(screen, 370 - mvpTextShift, 365, mvpText, charset);
		}
		else if (gameResult == SCISSORS_WIN)
		{
			sprintf(text, "S C I S S O R S   W I N !");
			DrawString(screen, 380, 345, text, charset);
			DrawString(screen, 355 - mvpTextShift, 365, mvpText, charset);
		}
		else
		{
			sprintf(text, "N O T   E N O U G H   O B J E C T S");
			DrawString(screen, 342, 355, text, charset);
		}
		return true;
	}
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

	if (simulation->playerMode)
	{
		DrawRectangle(screen, 4, 29, 100, 20, ALMOND, NAVY);
		sprintf(text, "POINTS: %d", simulation->playerControlledObject->points);
		DrawString(screen, 10, 35, text, charset);
	}

	DrawRectangle(screen, 340, 4, 240, 20, ALMOND, NAVY);
	sprintf(text, "PRESS 'R' TO GO BACK TO MENU");
	DrawString(screen, 346, 10, text, charset);

	DrawRectangle(screen, 4, 646, 80, 20, ALMOND, NAVY);
	sprintf(text, "ROCK: %d", simulation->rockObjects);
	DrawString(screen, 10, 652, text, charset);

	DrawRectangle(screen, 4, 671, 90, 20, ALMOND, NAVY);
	sprintf(text, "PAPER: %d", simulation->paperObjects);
	DrawString(screen, 10, 677, text, charset);

	DrawRectangle(screen, 4, 696, 110, 20, ALMOND, NAVY);
	sprintf(text, "SCISSORS: %d", simulation->scissorsObjects);
	DrawString(screen, 10, 702, text, charset);

	DrawRectangle(screen, 846, 696, 110, 20, ALMOND, NAVY);
	sprintf(text, "SPEED: %.2lf", simulation->simulationSpeed);
	DrawString(screen, 852, 702, text, charset);

	DrawRectangle(screen, 846, 671, 110, 20, ALMOND, NAVY);
	sprintf(text, "\030 D      \031 A");							
	DrawString(screen, 852, 677, text, charset);

	if (simulation->playerMode)
	{
		DrawRectangle(screen, 416, 650, 140, 66, ALMOND, NAVY);
		sprintf(text, "MOVEMENT");
		DrawString(screen, 450, 660, text, charset);
		sprintf(text, "\030");						
		DrawString(screen, 486, 675, text, charset);
		sprintf(text, "\032");						
		DrawString(screen, 466, 685, text, charset);
		sprintf(text, "\031");							
		DrawString(screen, 486, 700, text, charset);
		sprintf(text, "\033 ");							
		DrawString(screen, 506, 685, text, charset);
	}
}
void Window::displayMenu(double* time)
{
	DrawRectangle(screen, 280, 70, 400, 580, NAVY, LIGHT_BLUE);

	char text[128];
	DrawRectangle(screen, 340, 78, 280, 44, ALMOND, NAVY);
	sprintf(text, "ROCK PAPER SCISSORS SIMULATION");
	DrawString(screen, 362, 94, text, charset);

	displayParametersSettings(time);

	if (simulation->rockObjectsSet && simulation->paperObjectsSet && simulation->scissorsObjectsSet)
	{
		DrawRectangle(screen, 338, 548, 284, 48, RED, RED);
		DrawRectangle(screen, 340, 550, 280, 44, RED, NAVY);

		if (*time < 0.4)
			sprintf(text, "");
		else if (*time >= 0.4 && *time < 1.2)
			sprintf(text, "PRESS 'S' TO START");
		else
		{
			sprintf(text, "PRESS 'S' TO START");
			*time = 0.0;
		}
	}
	else
	{
		DrawRectangle(screen, 340, 550, 280, 44, ALMOND, NAVY);
		sprintf(text, "PRESS 'S' TO START");
	}
	DrawString(screen, 408, 566, text, charset);

	DrawRectangle(screen, 340, 600, 280, 40, ALMOND, NAVY);
	sprintf(text, "AUTHOR: RADOSLAW GAJEWSKI");
	DrawString(screen, 380, 616, text, charset);
}
void Window::displayParametersSettings(double* time)
{
	char text[128];

	if (!simulation->rockObjectsSet)
	{
		DrawRectangle(screen, 338, 252, 284, 48, RED, RED);
		DrawRectangle(screen, 340, 254, 280, 44, RED, NAVY);

		if (*time < 0.6)
			sprintf(text, "ENTER THE NUMBER OF ROCKS: %d", simulation->rockObjects);
		else if (*time >= 0.6 && *time < 1)
			sprintf(text, "ENTER THE NUMBER OF ROCKS:");
		else
		{
			sprintf(text, "ENTER THE NUMBER OF ROCKS:");
			*time = 0.0;
		}
	}
	else
	{
		DrawRectangle(screen, 340, 254, 280, 44, ALMOND, NAVY);
		sprintf(text, "ENTER THE NUMBER OF ROCKS: %d", simulation->rockObjects);
	}
	DrawString(screen, 370, 270, text, charset);

	if (simulation->rockObjectsSet && !simulation->paperObjectsSet)
	{
		DrawRectangle(screen, 338, 306, 284, 48, RED, RED);
		DrawRectangle(screen, 340, 308, 280, 44, RED, NAVY);

		if (*time < 0.6)
			sprintf(text, "ENTER THE NUMBER OF PAPERS: %d", simulation->paperObjects);
		else if (*time >= 0.6 && *time < 1)
			sprintf(text, "ENTER THE NUMBER OF PAPERS:");
		else
		{
			sprintf(text, "ENTER THE NUMBER OF PAPERS:");
			*time = 0.0;
		}
	}
	else
	{
		DrawRectangle(screen, 340, 308, 280, 44, ALMOND, NAVY);
		sprintf(text, "ENTER THE NUMBER OF PAPERS: %d", simulation->paperObjects);
	}
	DrawString(screen, 364, 324, text, charset);

	if (simulation->rockObjectsSet && simulation->paperObjectsSet && !simulation->scissorsObjectsSet)
	{
		DrawRectangle(screen, 338, 360, 284, 48, RED, RED);
		DrawRectangle(screen, 340, 362, 280, 44, RED, NAVY);

		if (*time < 0.6)
			sprintf(text, "ENTER THE NUMBER OF SCISSORS: %d", simulation->scissorsObjects);
		else if (*time >= 0.6 && *time < 1)
			sprintf(text, "ENTER THE NUMBER OF SCISSORS:");
		else
		{
			sprintf(text, "ENTER THE NUMBER OF SCISSORS:");
			*time = 0.0;
		}
	}
	else
	{
		DrawRectangle(screen, 340, 362, 280, 44, ALMOND, NAVY);
		sprintf(text, "ENTER THE NUMBER OF SCISSORS: %d", simulation->scissorsObjects);
	}
	DrawString(screen, 356, 378, text, charset);

	Uint32 color;
	if (simulation->playerMode)
	{
		color = GREEN;
		sprintf(text, "PRESS 'P' TO PLAY AS ONE OF THE OBJECTS: ON");
	}
	else
	{
		color = RED;
		sprintf(text, "PRESS 'P' TO PLAY AS ONE OF THE OBJECTS: OFF");
	}
	DrawRectangle(screen, 298, 448, 364, 48, color, color);
	DrawRectangle(screen, 300, 450, 360, 44, color, NAVY);

	DrawString(screen, 306, 466, text, charset);

	DrawRectangle(screen, 340, 500, 280, 44, ALMOND, NAVY);
	sprintf(text, "PRESS 'R' TO RESET PARAMETERS");
	DrawString(screen, 365, 516, text, charset);
}
void Window::handleEvents(SDL_Event event, double worldTime)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			exitGame = true;
			break;
		case SDLK_d:
			if (simulation->simulationStarted && !simulation->checkifGameOver() && simulation->simulationSpeed < 15)
				simulation->changeSimulationSpeed(INCREASE_SPEED);
			break;
		case SDLK_a:
			if (simulation->simulationStarted && !simulation->checkifGameOver())
				simulation->changeSimulationSpeed(DECREASE_SPEED);
			break;
		case SDLK_s:
			if (!simulation->simulationStarted && simulation->rockObjectsSet && simulation->paperObjectsSet && simulation->scissorsObjectsSet)
				simulation->startSimulation();
			break;
		case SDLK_r:
			simulation = new Simulation();
			worldTime = 0;
			break;
		case SDLK_p:
			if (!simulation->simulationStarted)
				simulation->playerMode = !simulation->playerMode;
			break;
		case SDLK_0: case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4: case SDLK_5: case SDLK_6: case SDLK_7: case SDLK_8: case SDLK_9:
			if (!simulation->simulationStarted)
			{
				if (!simulation->rockObjectsSet)
				{
					simulation->rockObjects = event.key.keysym.sym - '0';
					simulation->rockObjectsSet = true;
				}
				else if (!simulation->paperObjectsSet)
				{
					simulation->paperObjects = event.key.keysym.sym - '0';
					simulation->paperObjectsSet = true;
				}
				else if (!simulation->scissorsObjectsSet)
				{
					simulation->scissorsObjects = event.key.keysym.sym - '0';
					simulation->scissorsObjectsSet = true;
				}
			}
			break;
		}
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
			exitGame = true;
	}
}
void Window::handlePlayerMovement(SDL_Event event, double delta)
{
	const Uint8* keyboardStateArray = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		if (!simulation->playerMoved && (keyboardStateArray[SDL_SCANCODE_UP] || keyboardStateArray[SDL_SCANCODE_DOWN] || keyboardStateArray[SDL_SCANCODE_LEFT] || keyboardStateArray[SDL_SCANCODE_RIGHT]))
			simulation->playerMoved = true;

		if (keyboardStateArray[SDL_SCANCODE_UP] && !(keyboardStateArray[SDL_SCANCODE_DOWN]))
		{
			if (simulation->playerMode && simulation->simulationStarted && !simulation->checkifGameOver())
				simulation->playerControlledObject->move(delta, UP);
		}
		else if (keyboardStateArray[SDL_SCANCODE_DOWN] && !keyboardStateArray[SDL_SCANCODE_UP])
		{
			if (simulation->playerMode && simulation->simulationStarted && !simulation->checkifGameOver())
				simulation->playerControlledObject->move(delta, DOWN);
		}
		if (keyboardStateArray[SDL_SCANCODE_RIGHT] && !keyboardStateArray[SDL_SCANCODE_LEFT])
		{
			if (simulation->playerMode && simulation->simulationStarted && !simulation->checkifGameOver())
				simulation->playerControlledObject->move(delta, RIGHT);
		}
		else if (keyboardStateArray[SDL_SCANCODE_LEFT] && !keyboardStateArray[SDL_SCANCODE_RIGHT])
		{
			if (simulation->playerMode && simulation->simulationStarted && !simulation->checkifGameOver())
				simulation->playerControlledObject->move(delta, LEFT);
		}
	}
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