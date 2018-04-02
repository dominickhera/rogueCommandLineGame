#ifndef __DHERA__DRAW__
#define __DHERA__DRAW__
#include <parse.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

typedef struct character
{
    int healthCount;
    int potionCount;
    int inventoryTotal;
    int attackCount;
    int goldTotal;

}Player;

typedef struct enemyStruct
{
	int enemyCount;
	int enemyHealthCount;
	int enemyAttackCount;
	int enemyAttackSpeed;
	int enemyY;
	int enemyX;
	int kill;
	char type; 

}Enemy;

void initCurses(Room * rooms);
char ** printRooms(int xVar, int yVar, Room * rooms, int index);
void printHorizontalHallway(int x, int y);
void printVerticalHallway(int x, int y);
void connectDoors(char ** roomMake[], Room * rooms);
void printDeadEnds(int startX, int startY, int xIncrement, int yIncrement, int randNum);
void movePlayer(char input, int * posY, int * posX);
void movePlayerInHallways(char input, int * posY, int * posX);
int checkInput(char input, int posY, int posX, Enemy * enemy, Player * player);
Enemy initMonster(int x, int y, int health, int attack, int speed, int kill, char typeOfEnemy);
int getMaxYRoom(Room * rooms, int x);
int getMaxYTop(Room * rooms);
int getMaxYBot(Room * rooms);
int getTotalY(Room * rooms);
int rightHallwayNum(Room * rooms);
void notification(char * text);
void initPlayer(Player * player);
void getStatus(Player player, int x, int y);
void clearNotifyLine();
int getNotifyY(Room * rooms);
int getNotifyX(Room * rooms);
void freeLevels(char ** curseRoom[], Room * rooms);
void freeRoom (Room * rooms);
void endGame();

#endif
