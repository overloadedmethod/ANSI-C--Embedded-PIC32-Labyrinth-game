#include "Header Files\Level.h"


int lab[8][16] = {
	{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, ESCAPE, WALL, WALL, WALL, WALL, WALL, },
	{ WALL, PATH, PATH, PATH, PRIZE, WALL, PRIZE, PATH, PRIZE, WALL, PATH, WALL, PATH, PATH, PATH, WALL },
	{ WALL, PATH, WALL, PATH, WALL, PLAYER, WALL, PATH, WALL, WALL, PATH, WALL, PRIZE, WALL, PATH, WALL },
	{ WALL, PATH, WALL, PATH, PATH, PATH, PATH, PATH, WALL, WALL, PATH, WALL, PATH, PATH, PATH, WALL },
	{ WALL, PATH, PATH, WALL, WALL, WALL, WALL, PATH, WALL, WALL, PATH, WALL, PATH, WALL, WALL, WALL },
	{ WALL, WALL, PATH, PATH, PATH, PATH, WALL, PATH, WALL, WALL, PATH, PATH, PATH, PATH, PRIZE, WALL },
	{ WALL, PRIZE, PATH, WALL, WALL, PRIZE, WALL, PATH, PATH, PATH, PRIZE, WALL, WALL, WALL, WALL, WALL },
	{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, } };

Level* initLevel(int size){

	int i, j;

	Level* level = (Level*)malloc(sizeof(Level));
	level->VerticalSize = 8;
	level->HorizontalSize = 16;
	level->itemsLeft = 8;

	level->labyrinth = (int**)malloc(sizeof(int*)* level->VerticalSize);

	for (i = 0; i < level->VerticalSize; i++) {
		level->labyrinth[i] = (int*)malloc(sizeof(int)* level->HorizontalSize);
		for (j = 0; j < level->HorizontalSize; j++)
			level->labyrinth[i][j] = lab[i][j];
	}

	return level;
}
