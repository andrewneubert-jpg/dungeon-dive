#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "roomManip.h"
#include "stringManip.h"


int main(int numFile, char **fileName){ //take in input from terminal

	FILE *lineP = fopen(fileName[1],"r");                                                          
        int roomCount = 0;
        char lineB[900];

        roomCount = roomCounter(roomCount,lineB,lineP,sizeof(lineB)); //counts how many rooms are there

        rewind(lineP); //resets file line pointer, below is initial values

        Room *room;
        room = malloc(sizeof(Room)*(roomCount)); //gives size of array based off of how may rooms will be made
        int count  = -1;

        room = roomMaker(lineB, sizeof(lineB), lineP, room, count);

        char answer[50];//asks how many dungeons you want and returns an integer
        printf("\n\nhow many rooms in the dungeon do you want? ");
        fgets(answer,sizeof(answer),stdin);
        int numMake = atoi(answer);
        printf("\n");
        
        Room *dungeonRoom;
        dungeonRoom = malloc(sizeof(Room)*numMake);//gives size of array based off of how many rooms are wanted

        dungeonRoom = dungeonMaker(dungeonRoom, room, roomCount, numMake); //makes dungeon


        fclose(lineP);//closes file
        free(dungeonRoom); //clears up all space
        free(room);


return 0;
}
