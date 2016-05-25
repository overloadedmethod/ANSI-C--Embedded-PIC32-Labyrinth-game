#pragma once
#include "Game.h"





Level* initLevel(int size);
int isLegalBranch(int x, int y, Level* level);
void generateCurvyBranch(Level* level);
void generateLabyrinth(Level* level);
int isWithinBounds(int x, int y, int n);
void DestroyLevel();
