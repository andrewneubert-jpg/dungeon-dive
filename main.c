#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct Room{ //making the structure
        char name[100];//probably gave a little bit more space than I need
        char id[50];
        char description[900];
        struct Room *north;
        struct Room *east;
        struct Room *south;
        struct Room *west;
} Room;

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

char *stringTrimmer1(char *splitBy,char *tok, char *lineB){  //in string manip
	tok = strtok(lineB,splitBy); //the first split, returns the string saying what type of info it it
	return tok;
}

char *stringTrimmer2(char *splitBy,char *tok){  //in string manip
	tok = strtok(NULL,splitBy); //cleans up the data
	tok = strtok(tok,"\n");
	tok++;
	return tok;
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


int question(){  //in room manip
 	char answer[50];//asks how many dungeons you want and returns an integer
        printf("\n\nhow many rooms in the dungeon do you want? ");
        fgets(answer,sizeof(answer),stdin);
        int numMake = atoi(answer);
        printf("\n");
	return numMake;
}


Room* dungeonMaker(Room *dungeonRoom, Room *room, int roomCount, int numMake){ //in room manip

        srand(time(NULL));
        for(int count = 0;count<numMake;count++){//randomly picks the room and assigns it to a new array
                int numChoice = (rand() % roomCount);
                strcpy(dungeonRoom[count].id,room[numChoice].id);
                strcpy(dungeonRoom[count].name,room[numChoice].name);
                strcpy(dungeonRoom[count].description,room[numChoice].description);
                if(count != 0){
                        dungeonRoom[count].west = &dungeonRoom[count-1];
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



int main(int numFile, char **fileName){ //take in input from terminal

	FILE *lineP = fopen(fileName[1],"r");                                                           //----------start of initial room array maker-------------
        int roomCount = 0;
        char lineB[900];

        roomCount = roomCounter(roomCount,lineB,lineP,sizeof(lineB));

        rewind(lineP); //resets file line pointer, below is initial values

        Room *room;
        room = malloc(sizeof(Room)*(roomCount));
        int count  = -1;

        room = roomMaker(lineB, sizeof(lineB), lineP, room, count);

        int numMake = question();
        Room *dungeonRoom;
        dungeonRoom = malloc(sizeof(Room)*numMake);

        dungeonRoom = dungeonMaker(dungeonRoom, room, roomCount, numMake);


        fclose(lineP);//closes file
        free(dungeonRoom);
        free(room);


return 0;
}
