#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "roomManip.h"
#include "stringManip.h"

int roomCounter(int roomCount, char *lineB, FILE *lineP, int sizeLineB){ //in room manip
        while(fgets(lineB,sizeLineB,lineP) != NULL){ //counts # of rooms
                char splitBy[] = ":";
                char *tok = strtok(lineB,splitBy); //identifies each room by seeing how many lines include the phrase -Room name-
                        if(strcmp("Room Name",tok)==0){
                                roomCount++;
                        }
        }
        return roomCount;
}

Room* roomMaker(char *lineB, int sizeLineB, FILE *lineP,Room *room, int count){  //in room manip
        while(fgets(lineB,sizeLineB,lineP) != NULL){//reads line until end of file
                char splitBy[] = ":";
                char *tok = stringTrimmer1(splitBy, tok, lineB);

                if(strcmp("Room Name",tok)==0){//identifies the type of info
                        tok = stringTrimmer2(splitBy,tok);
                        count++;
                        strcpy(room[count].name,tok);//adds room info to structure [rooms names seperated by the room count, that is how they are distinct structures]
                }
                else if(strcmp("Room Code",tok)==0){
                        tok = stringTrimmer2(splitBy,tok);
                        strcpy(room[count].id,tok);
                }
                else if(strcmp("Room Description",tok)==0){
                        tok = stringTrimmer2(splitBy,tok);
                        strcpy(room[count].description,tok);

                }
        }
        return room;

}


Room* dungeonMaker(Room *dungeonRoom, Room *room, int roomCount, int numMake){ //in room manip

        srand(time(NULL));
        for(int count = 0;count<numMake;count++){//randomly picks the room and assigns it to a new array
                int numChoice = (rand() % roomCount);
                strcpy(dungeonRoom[count].id,room[numChoice].id); //copys infor from the random room to the room of the dungeon
                strcpy(dungeonRoom[count].name,room[numChoice].name);
                strcpy(dungeonRoom[count].description,room[numChoice].description);
                if(count != 0){
                        dungeonRoom[count].west = &dungeonRoom[count-1];// assigns east and west linking and prints the info as proof
                        dungeonRoom[count-1].east = &dungeonRoom[count];
                        printf("right of %s: %s\n", dungeonRoom[count-1].name,dungeonRoom[count-1].east->name);
                        printf("\ndungeon room %d: %s\n",count,dungeonRoom[count].name);
                        printf("left of %s: %s\n", dungeonRoom[count].name,dungeonRoom[count].west->name);
                }
                else{
                        printf("dungeon room %d: %s <------ starting room\n",count,dungeonRoom[count].name);//I wanted it to print something slightly different for the first room (marking the first room)
                }
        }
        return dungeonRoom;

}
