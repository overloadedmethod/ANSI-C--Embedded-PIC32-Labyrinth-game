#include "Header Files\Level.h"
#include "Header Files\Player.h"

Player* initPlayer(int levelSize){
	Player* player = (Player*)malloc(sizeof(Player));
	player->x = 5;
	player->y = 2;
	return player;
}


void main(){
	int size = 20;
	Level* level = initLevel(size);
	Player* player = initPlayer(size);
	runGame(player, level);
}
