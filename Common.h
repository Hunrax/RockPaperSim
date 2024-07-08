#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include "windows.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 720

#define OBJECT_SIZE 40
#define OBJECT_AMOUNT 5

#define ROCK_WIN 1
#define PAPER_WIN 2
#define SCISSORS_WIN 3

