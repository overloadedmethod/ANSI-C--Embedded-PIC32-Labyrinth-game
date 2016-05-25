#pragma once

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <conio.h>

typedef struct Level_def{
	int VerticalSize,HorizontalSize, itemsLeft;
	int** labyrinth;
}Level;

typedef struct Player_def{
	int x, y;
}Player;



#define WALL 0
#define PATH 5
#define PLAYER 8
#define PRIZE 3
#define ESCAPE 7
#define CANNOT_ESCAPE -2
#define NO_RENDER_NEEDED -3
#define RENDERED -4
#define CANNOT_RENDER -5

move(Player* player, Level* level, int x, int y);
int getInput();
void draw(Level* level);
int render(int code, Level* level);
void runGame(Player* player, Level* level);
