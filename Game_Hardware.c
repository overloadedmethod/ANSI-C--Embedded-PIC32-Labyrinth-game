

//#include <p32xxxx.h>
#include  "Header Files\Game.h"
#pragma once

#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

void initPortD(void);
void initPortB(void);
void initPortE(void);
void initPortF(void);
void initLcd(void);
void writeLcd(unsigned int num, int lcd_cs);
void drawElement(unsigned int* element, int x, int y, int lcd);
unsigned int* translateFromMatrix(int x, int y, Level* level);
void drawMatrixElement(int matrix_x, int matrix_y, Level* level);
void drawLevel(Level* level);
int move(Player* player, Level* level, int x, int y);


unsigned int* wall[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
unsigned int* prize[8] = { 0x00, 0x0C, 0x3A, 0x4E, 0x7E, 0x3E, 0x0C, 0x00 };
unsigned int* player[8] = { 0x00, 0x08, 0xE4, 0x3F, 0x3F, 0xE4, 0x08, 0x00 };
unsigned int* escape[8] = { 0xFC, 0x28, 0xFF, 0x99, 0x99, 0xFF, 0x28, 0xFC };
unsigned int* path[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


int getInput(){
	setvbuf(stdin, 0, _IONBF, 0);
	return _getch();
}

void draw(Level* level){
	int i, j;
	system("cls");
	for (i = 0; i < level->VerticalSize; i++) {
		for (j = 0; j < level->HorizontalSize; j++)
			_putch('0' + level->labyrinth[i][j]);
		_putch('\n');
	}
	printf("\nITEMS LEFT TO TAKE:%d", level->itemsLeft);
}


int render(int code, Level* level){
	switch (code){
	case WALL:return NO_RENDER_NEEDED;
	case PATH:draw(level);
		return RENDERED;
	case ESCAPE:system("cls");
		printf("YOU WON!");
		return CANNOT_RENDER;
	case CANNOT_ESCAPE:return NO_RENDER_NEEDED;
	}
}

void runGame(Player* player, Level* level){
	int rendered = RENDERED;
	printf("PRESS ANY KEY TO CONTINUE");
	do{
		switch (getInput()){
		case 'w':move(player, level, player->x, player->y - 1); break;//up
		case 's':move(player, level, player->x, player->y + 1); break;//down
		case 'a':move(player, level, player->x - 1, player->y); break;//left
		case 'd':move(player, level, player->x + 1, player->y); break;//right
		case 'q':rendered = CANNOT_RENDER; break;
		}
	} while (rendered != CANNOT_RENDER);
}


void initPortD(void)
{
unsigned int portMap;

portMap = TRISD;
portMap &= 0xFFFFFF4F;
TRISD = portMap;
PORTDbits.RD4 = 0;
PORTDbits.RD5 = 0;
PORTDbits.RD7 = 0;
}

void initPortB(void)
{
unsigned int portMap;

portMap = TRISB;
portMap &= 0xFFFF7FFF;
TRISB = portMap;
PORTBbits.RB15 = 0;
}

void initPortE(void)
{
unsigned int portMap;

portMap = TRISE;
portMap &= 0xFFFFFF00;
TRISE = portMap;
PORTE = 0x00;
}

void initPortF(void)
{
unsigned int portMap;

portMap = TRISF;
portMap &= 0xFFFFFEF8;
TRISF = portMap;
PORTFbits.RF8 = 1;
}

void delay(void)
{
unsigned int i;

for (i = 0; i<6400; i++);
}

void initLcd(void)
{
int CONTROL[4] = { 0x40, 0xB8, 0xFF, 0x3F };
int i;

PORTDbits.RD5 = 0;
PORTBbits.RB15 = 0;
PORTF = 0x01;
PORTDbits.RD7 = 0;
PORTDbits.RD7 = 1;
PORTF = 0x02;
PORTDbits.RD7 = 0;
PORTDbits.RD7 = 1;
PORTFbits.RF8 = 1;

for (i = 0; i < 4; i++)
{
PORTE = CONTROL[i];
PORTF = 0x01;
PORTDbits.RD4 = 1;//enable=1
PORTDbits.RD4 = 0;//enable=0
delay();
PORTF = 0x02;
PORTDbits.RD4 = 1;//enable=1
PORTDbits.RD4 = 0;//enable=0
delay();
}
PORTFbits.RF8 = 1;
}

void writeXY(int x, int y, int lcd_cs)
{
PORTDbits.RD5 = 0;
PORTBbits.RB15 = 0;
PORTF = lcd_cs;
PORTE = 0x40 + x;
PORTDbits.RD4 = 1;//enable=1
PORTDbits.RD4 = 0;//enable=0
delay();
PORTE = 0xB8 + y;
PORTDbits.RD4 = 1;//enable=1
PORTDbits.RD4 = 0;//enable=0
delay();
PORTFbits.RF8 = 1;
}

void writeLcd(unsigned int num, int lcd_cs)
{
int i;

PORTDbits.RD5 = 0;
PORTBbits.RB15 = 1;
PORTF = lcd_cs;
PORTE = num;
PORTDbits.RD4 = 1;//enable=1
PORTDbits.RD4 = 0;//enable=0
delay();
PORTFbits.RF8 = 1;
}

void drawElement(unsigned int* element, int x, int y, int lcd) {
	int i;
	for (i = 0; i < 8; i++){
		writeXY(x + i, y, lcd);
		writeLcd(element[i], lcd);
	}
}

unsigned int* translateFromMatrix(int x, int y, Level* level){
	switch (level->labyrinth[y][x / 8]){
	case PLAYER:return player;
	case PATH:return path;
	case PRIZE:return prize;
	case WALL:return wall;
	case ESCAPE:return escape;
	}
}

void drawMatrixElement(int matrix_x, int matrix_y, Level* level){
	unsigned int* element = 0;
	switch (level->labyrinth[matrix_y][matrix_x]){
	case PLAYER:element = player; break;
	case PATH:element = path; break;
	case PRIZE:element = prize; break;
	case WALL:element = wall; break;
	case ESCAPE:element = escape; break;
	}
	if (matrix_x >= level->HorizontalSize / 2)drawElement(element, matrix_x * 8, matrix_y, 2);
	else drawElement(element, matrix_x * 8, matrix_y, 1);
}

void drawLevel(Level* level){
	int i, j;
	for (i = 0; i < level->VerticalSize; i++) {
		for (j = 0; j < level->HorizontalSize; j++)
			drawMatrixElement(i, j, level);
	}
}

int move(Player* player, Level* level, int x, int y){
	switch (level->labyrinth[y][x]){
	case PRIZE: level->itemsLeft--;
	case PATH:
		level->labyrinth[player->y][player->x] = PATH;
		drawMatrixElement(player->x, player->y, level);
		player->y = y;
		player->x = x;
		level->labyrinth[y][x] = PLAYER;
		drawMatrixElement(x, y, level);

		return PATH;
	case WALL:buzzer(); return WALL;
	case ESCAPE:if (level->itemsLeft == 0)return ESCAPE;
		return CANNOT_ESCAPE;
		}
	}

void buzzer()
{
	TRISE = 0xff;
	PORTF = 3;
	TRISG = 0;
	PORTDbits.RD4 = 1;
	PORTDbits.RD4 = 0;
	if (PORTEbits.RE6 == 1){ PORTGbits.RG15 = 1; }
	else{
		PORTGbits.RG15 = 0;
	}

}
