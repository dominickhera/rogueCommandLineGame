#include "draw.h"
#include "parse.h"
#include <ctype.h> 
//calls the room print function to print all the rooms, makes sure to print them at an offset so they all dont print right next to eachother
//also handles the game loop that looks for user interaction and checks the input against another function to see how to respond
void initCurses(Room * rooms)
{

    Player player;
    initPlayer(&player);
    Enemy * enemy = malloc(sizeof(Enemy) * 20);
    char * s = malloc(sizeof(char) * 256);
    char ** roomMake[6];
    char input;
    int smallRandNum = 0;
    int bigRandNum = 0;
    int charY = 0;
    int charX = 0;
    int testOffset = 0;
    int midOffset = 0;
    int topOffset = 0;
    int botOffset = 0;
    int hallwayOne = 0;
    int hallwayTwo = 0;
    int hallwayThree = 0;
    int hallwayFour = 0;
    srand(time(NULL));

    initscr();
    noecho();

    for (int i = 0; i < 6; i ++)
    {
        int yRoom = 0;
        int xRoom = 0;
        xRoom = rooms[i].x;
        yRoom = rooms[i].y;
        roomMake[i] = printRooms(yRoom,xRoom, rooms, i);
    }

    getStatus(player, getNotifyY(rooms), getNotifyX(rooms));

    int offset = 0;
    int maxTop = 0;
    int yOffset = 5;
    int enemyCounter = 0;

    for (int j = 0; j < 6; j++)
    {
        if (j <= 2)
        {
            if (j == 0)
            {
                maxTop = rooms[j].y;
                offset = 0;
            }
            else
            {
                offset = offset + (rooms[j - 1].x  + 7);
                if(rooms[j].y > maxTop)
                {
                    maxTop = rooms[j].y;
                }
            }

            for(int i=0;i<rooms[j].y;i++)
            {
                for(int k=0;k<rooms[j].x;k++)
                {

                    int yEnemy = i + yOffset;
                    int xEnemy = k + 6;

                    if (roomMake[j][i][k] == 'T')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 50, 5, 3, 0,'T');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'A')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 5, 1, 2, 0, 'A');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'B')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 5, 5, 4, 0, 'B');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'S')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 5, 5, 4, 0, 'S');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'Z')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 15, 5, 3, 0,'Z');
                        enemyCounter++; 
                    }
                    mvaddch(i + yOffset, k + offset + 6, roomMake[j][i] [k]);
                }
            }

        }
        else if (j > 2 && j < 6)
        {
            if(j == 3)
            {
                offset = 0;
            }
            else if (j > 3)
            {
                offset = offset + (rooms[j - 1].x  + 7);
            }

            for(int i=0;i<rooms[j ].y;i++)
            {
                for(int k=0;k<rooms[j ].x;k++)
                {

                    int yEnemy = k + offset;
                    int xEnemy = i;

                    if (roomMake[j][i][k] == 'T')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 50, 5, 3, 0, 'T');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'A')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 5, 1, 2, 0,'A');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'B')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 2, 5, 4, 0, 'B');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'S')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 5, 5, 4, 0, 'S');
                        enemyCounter++; 
                    }
                    else if(roomMake[j][i][k] == 'Z')
                    {
                        enemy[enemyCounter] = initMonster(xEnemy, yEnemy, 15, 5, 3, 0, 'Z');
                        enemyCounter++; 
                    }

                    mvaddch(i + (maxTop + (yOffset * 2)), k + offset + 6, roomMake[j][i] [k]);
                }
            }

        }

    }

    topOffset = (yOffset/2);
    midOffset = (getMaxYTop(rooms) + (maxTop/2));
    botOffset = (getMaxYTop(rooms) + getMaxYBot(rooms) + (topOffset) + (midOffset/2));
    hallwayOne = (getMaxYRoom(rooms, 2) + (yOffset * 1.5));
    hallwayTwo = ((getMaxYRoom(rooms, 2) + getMaxYRoom(rooms, 1) + (yOffset * 2.75)));
    hallwayThree = (getMaxYRoom(rooms, 4) + (yOffset * 1.5));
    hallwayFour = ((getMaxYRoom(rooms, 5) + getMaxYRoom(rooms, 4) + (yOffset * 2.75)) + 2);
    testOffset = ((yOffset * 4) + rightHallwayNum(rooms));
    printHorizontalHallway(testOffset, topOffset); //top horizontal hallway
    printHorizontalHallway(testOffset, midOffset); //middle horizontal hallway
    printHorizontalHallway(testOffset, botOffset); //bot horizontal hallyway
    printVerticalHallway((botOffset), topOffset);//most left hallway
    printVerticalHallway((botOffset), (testOffset));//most right hallway
    printVerticalHallway(midOffset, hallwayOne);
    printVerticalHallway(midOffset, hallwayTwo);
    printVerticalHallway(botOffset, hallwayThree);
    printVerticalHallway(botOffset, hallwayFour);

    charX = (rooms->heroX);
    charY = (rooms->heroY);
    connectDoors(roomMake, rooms);
    mvaddch(charY, charX, '@');
    move(charY, charX);
    refresh();

    //main game loop
    do
    {
        char condition;
        refresh();
        input = getch();
        condition = checkInput(input, charY, charX, enemy, &player);
        switch (condition)
        {
            case 1:
                clearNotifyLine();
                movePlayer(input,&charY,&charX);
                getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                break;
            case 2:
                clearNotifyLine();
                sprintf(s, "you walked through a door");
                notification(s);
                movePlayerInHallways(input,&charY,&charX);
                getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                break;
            case 3:
                smallRandNum = (rand() % 50);
                player.goldTotal += smallRandNum;
                getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                movePlayer(input,&charY,&charX);
                sprintf(s, "You picked up %d gold!", smallRandNum);
                notification(s);
                break;
            case 4:
                clearNotifyLine();
                bigRandNum = rand()%(250-50 + 1) + 50;
                player.goldTotal += bigRandNum;
                movePlayer(input,&charY,&charX);
                sprintf(s, "You picked up %d gold!", bigRandNum);
                notification(s);
                getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                break;
            case 5:
                movePlayer(input,&charY,&charX);
                input = 'q';
                break;
            case 6:
                clearNotifyLine();
                movePlayer(input,&charY,&charX);
                sprintf(s, "You picked up a potion");
                notification(s);
                player.potionCount++;
                getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                break;
            case 7:
                if(player.healthCount == 50)
                {
                    sprintf(s, "You already have full health!");
                    notification(s);
                    getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                }
                else if (player.potionCount > 0)
                {
                    player.potionCount--;
                    sprintf(s, "You now have full health!");
                    notification(s);
                    player.healthCount = 50;
                    getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                } 
                else 
                {
                    sprintf(s, "You have no potions left!");
                    notification(s);
                    getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                }
                break;
            case 8:
                if (player.inventoryTotal < 5)
                {

                    player.inventoryTotal++;
                    sprintf(s, "You add the item to your inventory");
                    notification(s);
                    getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                }
                else
                {
                    sprintf(s, "You trip over the item and break it. good going.");
                    notification(s);
                    movePlayer(input,&charY,&charX);
                    getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
                }
            case 9:
                clearNotifyLine();
                movePlayerInHallways(input,&charY,&charX);
                getStatus(player, getNotifyY(rooms), getNotifyX(rooms));
            default:
                break;
        }
        move(charY, charX);
        refresh();
    }while(input != 'q');
    printf("Congratulations, you collected %d gold!\n", player.goldTotal);
    freeLevels(roomMake, rooms);
    freeRoom(rooms);
    endGame();
    return;
}
// main function that actually prints out the rooms
//mallocs and then begins to assign each character to the cureRoom file
//prints out items, large switch case to determine what actual character to print out for each item
char ** printRooms(int yVar, int xVar, Room * rooms, int index)
{
    char ** curseRoom;

    curseRoom = malloc(sizeof(char*) *yVar);
    if(curseRoom == NULL)
    {
        printf("failed to allocate memory for room\n");
        exit(1);
    }

    for(int i=0;i<yVar;i++)
    {
        curseRoom[i] = malloc(sizeof(char) *xVar);
        if(curseRoom[i] == NULL)
        {
            printf("failed to allocate memory for room \n");
            exit(1);
        }
    }

    for(int i=0;i<xVar;i++)
    {
        curseRoom[0][i] = '-';

    }

    for(int i=0;i<xVar;i++)
    {
        curseRoom[yVar - 1] [i] = '-';
    }

    for(int i=0;i<yVar;i++)
    {
        curseRoom[i] [0] = '|';//|
    }

    for(int i=0;i<yVar;i++)
    {
        curseRoom[i] [xVar - 1] = '|';
    }


    for(int i=1;i<yVar-1;i++)
    {
        for(int k=1;k<xVar-1;k++)
        {
            curseRoom[i][k] = '.';
        }
    }

    for(int i=0; i<rooms[index].totalDoors; i++)
    {
        if((rooms[index].doorLocation[i]) == 'e')
        {
            curseRoom[rooms[index].doorPosition[i] - 1][xVar - 1] = '+';
        }
        else if((rooms[index].doorLocation[i]) == 'n')
        {
            curseRoom[0][rooms[index].doorPosition[i] - 1] = '+';
        }
        else if((rooms[index].doorLocation[i]) == 's')
        {
            curseRoom[yVar - 1][rooms[index].doorPosition[i] - 1] = '+';
        }
        else if((rooms[index].doorLocation[i]) == 'w')
        {
            curseRoom[rooms[index].doorPosition[i] - 1][0] = '+';
        }

    }

    for(int i=0; i<rooms[index].totalItems; i++)
    {
        if (rooms[index].roomItems[i].itemType == 'g')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX ] = '*';
        } 
        else if (rooms[index].roomItems[i].itemType == 'G')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = '8';
        }
        else if (rooms[index].roomItems[i].itemType == 'z')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = '<';
        }
        else if (rooms[index].roomItems[i].itemType == 'w')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = ')';
        }
        else if (rooms[index].roomItems[i].itemType == 'W')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = '(';
        }
        else if (rooms[index].roomItems[i].itemType == 'm')
        {
            int randomNum = 0;
            randomNum = rand() % 4;

            if (randomNum == 0)
            {
                curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = 'A';
            }
            else if (randomNum == 1)
            {
                curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = 'B';
            }
            else if (randomNum == 2)
            {
                curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = 'Z';
            }
            else if (randomNum == 3)
            {
                curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = 'S';
            }
            randomNum = 0;
        }
        else if (rooms[index].roomItems[i].itemType == 'p')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = '!';
        }
        else if (rooms[index].roomItems[i].itemType == 'a')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = '<';
        }
        else if (rooms[index].roomItems[i].itemType == 'M')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = 'T';
        }
        else if (rooms[index].roomItems[i].itemType == 'e')
        {
            curseRoom[rooms[index].roomItems[i].itemY][rooms[index].roomItems[i].itemX] = ']';
        }
        else if (rooms[index].roomItems[i].itemType == 'h')
            rooms->heroY = rooms[index].roomItems[i].itemY;
        rooms->heroX = rooms[index].roomItems[i].itemX;
    }

    return curseRoom;
}

void printHorizontalHallway(int x, int y)
{
    move(y, 0);
    for(int i=2; i<x+1; i++)
    {
        mvaddch(y, i, '#');  
    }

}

void printVerticalHallway(int x, int y)
{
    move(y, 0);
    for(int i=2; i<x; i++)
    {
        mvaddch(i, y, '#');
    }
}

void connectDoors(char ** roomMake[], Room * rooms)
{
    int offset = 0;
    int maxTop = 0;
    int yOffset = 0;



    for(int i = 0; i<6; i++)
    {
        offset = offset + (rooms[i - 1].x  + 6);
        if (i <= 2)
        {
            if (i == 0)
            {
                maxTop = rooms[i].y;
                offset = 0;
            }
            else
            {
                offset = offset + (rooms[i - 1].x  + 6);
                if(rooms[i].y > maxTop)
                {
                    maxTop = rooms[i].y;
                }
            }
            yOffset = 5;
        }
        else if (i > 2 && i < 6)
        {
            if(i == 3)
            {
                offset = 0;
            }
            else if (i > 3)
            {
                offset = offset + (rooms[i - 1].x  + 6);
            }
            yOffset = maxTop + (yOffset * 2);
        }
        for(int j = 0; j < rooms[i].totalDoors; j++)
        {
            if(j == 0)
            {
                switch(rooms[i].doorLocation[j])
                {
                    case 'w':

                        break;
                    case 'e':

                        break;
                    case 'n':

                        break;
                    case 's':

                        break;
                }
            }
            else if (j > 0)
            {

                switch(rooms[i].doorLocation[j])
                {
                    case 'n':
                        printDeadEnds((rooms[i].doorPosition[j] + 5 + offset), (0 + yOffset), 0, -1, 3);
                        break;
                    case 's':
                        printDeadEnds((rooms[i].doorPosition[j] + offset + 5) ,(rooms[i].y - 1 + yOffset), 0, 1, 6);
                        break;
                    case 'w':
                        printDeadEnds((1 + 5 + offset), (rooms[i].doorPosition[j] - 1 + yOffset), -1, 0, 3);
                        break;
                    case 'e':
                        printDeadEnds((rooms[i].x - 1 + 5 + offset), (rooms[i].doorPosition[j] - 1 + yOffset), 1, 0, 3);
                        break;
                }

            }

        }

    }

}

void printDeadEnds(int startX, int startY, int xIncrement, int yIncrement, int randNum)
{
    move((startY), (startX));
    for(int i = 0; i < randNum; i++)
    { 
        startY = startY + yIncrement;
        startX = startX + xIncrement;
        mvaddch((startY), (startX), '#');
    }
}

void notification(char * text)
{
    for (int i = 0; i < 50; i++)
    {
        mvaddch(0,i,' ');
    }
    mvprintw(0,0, text);
    return; 
}

//checks the input of what character the user typed and responds accordingly
//also deals with collision control to make sure the hero doesnt go through walls
//also contains conditions for numerous possible items that the user can run into
int checkInput(char input, int posY, int posX, Enemy * enemy, Player * player)
{
    char space;
    switch(input)
    {
        case 'w':
            posY -= 1;
            break;
        case 'a':
            posX -= 1;
            break;
        case 's':
            posY += 1;
            break;
        case 'd':
            posX += 1;
            break;
        case 'r':
            clearNotifyLine();
            break;
        case 'p':
            return 7;
            break;
    }

    space = mvinch(posY, posX) & A_CHARTEXT;

    for (int i = 0; i < 20; i++)
    {
        if (enemy[i].enemyX == posX && enemy[i].enemyY == posY)
        {
            int randomNum = ((rand() % 9)+1);

            if(enemy[i].enemyHealthCount <= 0)
            {
                clearNotifyLine();
                mvaddch(enemy[i].enemyY, enemy[i].enemyX, '.');
                move(0,0);
                printw("you killed the monster");
            } 
            else if(player->healthCount <= 0)
            {
                return 5;
            }
            else if (randomNum > enemy[i].enemyAttackSpeed)
            {
                clearNotifyLine();
                enemy[i].enemyHealthCount -= player->attackCount; 
                move(0,0);
                printw("enemy health is now %d", enemy[i].enemyHealthCount);

            }
            else
            {
                player->healthCount -= enemy[i].enemyAttackCount;
                move(0,0);
                printw("player lost %d health", enemy[i].enemyAttackCount);       
            }
        }
    }

    int enemyX = 0; 
    int enemyY = 0; 
    int moveCount = 0;

    for (int i = 0; i < 20; i ++)
    {
        if (enemy[i].kill == 0)
        {
            if(enemy[i].type == 'B')
            {
                enemyX = enemy[i].enemyX;
                enemyY = enemy[i].enemyY;

                int random = rand() % 4 + 1; 
                switch(random)
                {
                    case 0: 
                        enemyX -= 1;
                        break;
                    case 1: 
                        enemyY -= 1; 
                        break;
                    case 2:
                        enemyX += 1; 
                        break;
                    case 3: 
                        enemyY += 1; 
                        break;
                } 
                random = 0;
                char next = mvinch(enemyY,enemyX) & A_CHARTEXT;

                if(next == '.')
                {
                    mvaddch(enemy[i].enemyY, enemy[i].enemyX, '.');
                    enemy[i].enemyY = enemyY;
                    enemy[i].enemyX = enemyX; 
                    mvaddch(enemy[i].enemyY, enemy[i].enemyX, 'B');
                }
            }
        }
        else if(enemy[i].type == 'T')
        {
            enemyX = enemy[i].enemyX;
            enemyY = enemy[i].enemyY;
            moveCount = 0;
            switch(moveCount)
            {
                case 0: 
                    enemyX -= 1;
                    moveCount++;
                    break;
                case 1: 
                    enemyY -= 1;
                    moveCount++; 
                    break;
                case 2: 
                    enemyX += 1;
                    moveCount++; 
                    break;
                case 3: 
                    enemyY += 1;
                    moveCount = 0;
                    break;
            } 

            char next = mvinch(enemyY,enemyX) & A_CHARTEXT;


            if(next == '.')
            {
                mvaddch(enemy[i].enemyY, enemy[i].enemyX, '.');
                enemy[i].enemyY = enemyY;
                enemy[i].enemyX = enemyX; 
                mvaddch(enemy[i].enemyY, enemy[i].enemyX, 'T');
            }
        }
        else 
            if(enemy[i].type == 'Z')
            {
                moveCount = 0;
                enemyX = enemy[i].enemyX;
                enemyY = enemy[i].enemyY;

                switch(moveCount)
                {
                    case 0: 
                        enemyX -= 1;
                        moveCount++;
                        break;
                    case 1: 
                        enemyX += 1;
                        moveCount = 0; 
                        break;
                } 

                char next = mvinch(enemyY,enemyX) & A_CHARTEXT;


                if(next == '.')
                {
                    mvaddch(enemy[i].enemyY, enemy[i].enemyX, '.');
                    enemy[i].enemyY = enemyY;
                    enemy[i].enemyX = enemyX; 
                    mvaddch(enemy[i].enemyY, enemy[i].enemyX, 'Z');
                }
            }
            else if(enemy[i].type == 'S')
            {
                enemyX = enemy[i].enemyX;
                enemyY = enemy[i].enemyY;
                moveCount = 0;
                switch(moveCount)
                {
                    case 0:
                        enemyY -= 1;
                        moveCount++;
                        break;
                    case 1:
                        enemyY -= 1;
                        moveCount++; 
                        break;
                    case 2:
                        enemyY += 1;
                        moveCount++; 
                        break;
                    case 3: 
                        enemyY += 1;
                        moveCount = 0;
                        break;
                } 

                char next = mvinch(enemyY,enemyX) & A_CHARTEXT;


                if(next == '.')
                {
                    mvaddch(enemy[i].enemyY, enemy[i].enemyX, '.');
                    enemy[i].enemyY = enemyY;
                    enemy[i].enemyX = enemyX; 
                    mvaddch(enemy[i].enemyY, enemy[i].enemyX, 'T');

                }
            }

    }

    switch(space)
    {
        case '#':
            return 9;
        case '.':
            return 1;
            break;
        case '+':
            return 2;
        case '|':
            return 0;
        case '-':
            return 0;
        case '*':
            return 3;
        case '8':
            return 4;
        case '<':
            return 5;
        case '>':
            return 5;
        case '!':
            return 6;
        case ')':
            return 8;
        case '(':
            return 8;
        case ']':
            return 8;
        case ' ':
            return 0;
        case 'Z':
            return 10;
        case 'A':
            return 10;
        case 'B':
            return 10;
        case 'S':
            return 10;
        case 'T':
            return 10;
        default:
            return 1;
    }

    return 0;
}

//basic move function to move player around in rooms
void movePlayer(char input, int * posY, int * posX)
{
    switch(input)
    {
        case 'w':
            mvaddch(*posY, *posX, '.');
            *posY -= 1;
            break;
        case 'a':
            mvaddch(*posY, *posX, '.');
            *posX -= 1;
            break;
        case 's':
            mvaddch(*posY, *posX, '.');
            *posY += 1;
            break;
        case 'd':
            mvaddch(*posY, *posX, '.');
            *posX += 1;
            break;
        default:
            return;
    }
    mvaddch(*posY, *posX, '@');
    move(*posY, *posX);
}

//seperate move function to handle moving around within hallways
void movePlayerInHallways(char input, int * posY, int * posX)
{
    switch(input)
    {
        case 'w':
            mvaddch(*posY, *posX, '#');
            *posY -= 1;
            break;
        case 'a':
            mvaddch(*posY, *posX, '#');
            *posX -= 1;
            break;
        case 's':
            mvaddch(*posY, *posX, '#');
            *posY += 1;
            break;
        case 'd':
            mvaddch(*posY, *posX, '#');
            *posX += 1;
            break;
        default:
            return;
    }
    mvaddch(*posY, *posX, '@');
    move(*posY, *posX);
}

int getMaxYRoom(Room * rooms, int x)
{
    int maxY = 0;
    maxY = rooms[x].y;
    rooms[x].y = maxY;

    return maxY;
}

int getMaxYTop(Room * rooms)
{
    int maxY = 0;
    for(int i = 0; i<3; i++)
    {
        if (rooms[i].y > maxY)
        {
            maxY = rooms[i].y;
        }
    }
    return maxY;
}

int getMaxYBot(Room * rooms)
{
    int maxY = 0;
    for(int i = 3; i<6; i++)
    {
        if (rooms[i].y > maxY)
        {
            maxY = rooms[i].y;
        }
    }
    return maxY;
}

int getTotalY(Room * rooms)
{
    int maxY = 0;
    int temp = 0;
    for(int i = 0; i<6; i++)
    {
        if (rooms[i].y > maxY)
        {
            maxY = rooms[i].y;
        }
        temp += maxY;
    }
    return temp;
}

int rightHallwayNum(Room * rooms)
{

    int maxYTop = 0;
    int maxYBot = 0;
    int tempTop = 0;
    int tempBot = 0;
    int finalTemp = 0;
    for(int i = 0; i<3; i++)
    {
        if (rooms[i].y > maxYTop)
        {
            maxYTop = rooms[i].y;
        }
        tempTop += maxYTop;
    }

    for(int i = 3; i<6; i++)
    {
        if (rooms[i].y > maxYBot)
        {
            maxYBot = rooms[i].y;
        }
        tempBot += maxYBot;
    }

    if(tempTop > tempBot)
    {
        finalTemp = tempTop;
    }
    else
    {
        finalTemp = tempBot;
    }

    return finalTemp;

}

//clears the notification line
void clearNotifyLine()
{
    move(0,0);
    clrtoeol();
}

//prints the status bar with all the player information in it
void getStatus(Player player, int x, int y)
{
    move(x, y);
    printw(" Health: %d | Potions: %d | Attack: %d | Inventory: %d/5 | Gold: %d ", player.healthCount, player.potionCount, player.attackCount, player.inventoryTotal, player.goldTotal);
}

//initialises all the parts of the player struct to their starting amounts as specified by the requirements provided
void initPlayer(Player * player)
{
    player->healthCount = 50;
    player->goldTotal = 0;
    player->potionCount = 1;
    player->inventoryTotal = 0;
    player->attackCount = 5;
}

Enemy initMonster(int x, int y, int health, int attack, int speed, int kill, char typeOfEnemy)
{
    Enemy * temp = malloc(sizeof(Enemy)); 
    temp->enemyX = x;
    temp->enemyY = y;
    temp->enemyHealthCount = health;
    temp->enemyAttackCount = attack;
    temp->enemyAttackSpeed = speed; 
    temp->kill = 0;
    temp->type = typeOfEnemy; 

    return *temp; 

}


//gets the x barring of the notifications
int getNotifyX(Room * rooms)
{
    int notifyX = 0;

    return notifyX;
}

//gets the y barring of the notifications
int getNotifyY(Room * rooms)
{

    int notifyY = 0;

    notifyY = ((getTotalY(rooms)/2) + 5);

    return notifyY;
}

//frees all the memory used to prevent memory leaks if only the program compiled on pi that is
void freeLevels(char ** curseRoom[], Room * rooms)
{
    for(int i=0;i<6;i++)
    {
        for(int j=0; j < rooms[i].y; j++)
        {
            free(curseRoom[i][j]);   
        }
        free(curseRoom[i]);
    }
}

void freeRoom (Room * rooms)
{
    for (int i = 0; i < 6; i++)
    {
        free(rooms[i].roomItems);
        free(rooms[i].doorPosition);
        free(rooms[i].doorLocation);
    }
    free(rooms);
}


//merely ends the game and gets out of ncurses
void endGame()
{
    endwin();
}
