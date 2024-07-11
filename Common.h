#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <iostream>

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
#define ZERO_OBJECTS 4

#define DECREASE_SPEED 0
#define INCREASE_SPEED 10

#define RIGHT 'r'
#define LEFT 'l'
#define UP 'u'
#define DOWN 'd'
#define NONE 'n'

