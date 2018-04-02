#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parse.h"

//opens file, closes it to prevent memory leaks, begins paarsing file to a char array for actually parsing the info.
Room * parseFile(char * filename) 
{ 

    FILE * openLevel;

    openLevel = fopen(filename, "r");
    Room * rooms = malloc(sizeof(Room) * 6); 

    int counter = 0;
    char line [256]; 



    while(fgets(line, 256, openLevel) != NULL) 
    {
        int length = 0;

        length = strlen(line);
        if (line[length - 1] == '\n'){
            line[length - 1] = '\0';
        } else {
            line[length] = '\0';
        }
        //parseRoom(line, length);
        realParse(&rooms[counter], line, length);
        memset(line, '\0', 256);
        counter++;

    }

    fclose(openLevel);

    return rooms; 

}

void realParse(Room * rooms, char * line, int length)
{

    rooms->totalDoors = 0;
    rooms->totalItems = 0;
    rooms->x = 0;
    rooms->y = 0;
    rooms->roomItems = NULL;
    rooms->doorPosition = NULL;
    rooms->doorLocation = NULL;

    for(int i = 0; i < length; i++)
    {
        if (line[i] == 'X') 
        {
            //x
            if (line [i - 2] == 0) 
            {
                if (isdigit(line[i - 1]))
                {
                    rooms->x = atoi(&line[i-1]);
                }
            }
            else if (isdigit(line[i - 2])) //12X12
            {
                rooms->x = (line[i - 2] - '0') * 10 + (line[i - 1] - '0');

            }
            //y
            if (isdigit(line[i + 2])) 
            {
                rooms->y = (line[i + 1] - '0') * 10 + (line[i + 2] - '0');
            }
            else if (isdigit(line[i + 1])) //1 char
            {  
                rooms->y = atoi(&line[i + 1]);
            }

            continue; 
        }

        if (line[i] == 'd')
        {
            if (isalpha(line[i + 1]))
            {
                if(rooms->totalDoors == 0){
                    rooms->doorLocation = malloc(sizeof(char)* 1);
                } else {
                    rooms->doorLocation = realloc(rooms->doorLocation, sizeof(char)* (rooms->totalDoors + 1));
                }
                rooms->doorLocation[rooms->totalDoors] = line[i + 1];
            }
            else 
            {
                puts("Missing baring");
                exit(1);
            }
            if (isdigit(line[i + 2]))
            {
                if (isdigit(line[i + 3])) //2 number
                {
                    if(rooms->totalDoors == 0) {
                        rooms->doorPosition = malloc(sizeof(int)* 1);
                    } else {
                        rooms->doorPosition = realloc(rooms->doorPosition, sizeof(int)* (rooms->totalDoors + 1));
                    }
                    rooms->doorPosition[rooms->totalDoors] = (line[i + 2] - '0') * 10 + (line[i + 3] - '0');
                }
                else //1 number
                {
                    if(rooms->totalDoors == 0) {
                        rooms->doorPosition = malloc(sizeof(int)* 1);
                    } else {
                        rooms->doorPosition = realloc(rooms->doorPosition, sizeof(int)* (rooms->totalDoors + 1));
                    }
                    rooms->doorPosition[rooms->totalDoors] = atoi(&line[i + 2]);
                }

            }
            else 
            {
                puts("yo missin a dig");
            }

            rooms->totalDoors++; 
            continue; 
        }

        if (isalpha(line[i]) && isdigit(line[i + 1]))
        {

            if (line[i - 1] != 'd')
            {
                if(rooms->totalItems == 0){
                    rooms->roomItems = malloc(sizeof(item)* 1);
                } else {
                    rooms->roomItems = realloc(rooms->roomItems, sizeof(item)* (rooms->totalItems + 1));
                }
                if(line[i + 2] == ',')//e4,15
                {
                    rooms->roomItems[rooms->totalItems].itemY = atoi(&line[i + 1]); 
                    if (isdigit(line[i + 4]))
                    {
                        rooms->roomItems[rooms->totalItems].itemX = (line[i + 3] - '0') * 10 + (line[i +4] - '0');
                    }
                    else if (isdigit(line[i + 3]))
                    {
                        rooms->roomItems[rooms->totalItems].itemX = atoi(&line[i + 3]);

                    }
                }
                else if(isdigit(line[i + 2]))
                {
                    //2 numbers
                    if(line[i + 3] == ',')
                    {
                        rooms->roomItems[rooms->totalItems].itemY = (line[i + 1] - '0') * 10 + (line[i + 2] - '0');
                        if (isdigit(line[i + 5]))
                        {
                            rooms->roomItems[rooms->totalItems].itemX = (line[i + 4] - '0') * 10 + (line[i + 5] - '0');
                        }
                        else if (isdigit(line[i + 4]))
                        {
                            rooms->roomItems[rooms->totalItems].itemX = atoi(&line[i + 4]);

                        }
                    }
                    else                    {   
                        puts("bro its done yo"); 
                        exit(1);
                    }
                }
                // g11,4   g4,11  g11,11

                rooms->roomItems[rooms->totalItems].itemType = line[i]; 

                rooms->totalItems++; 
                continue; 
            }
        }
    }
}

