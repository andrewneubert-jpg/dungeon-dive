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

int roomCounter(int roomCount, char *lineB, FILE *lineP, int sizeLineB){
	while(fgets(lineB,sizeLineB,lineP) != NULL){ //counts # of rooms
        	char splitBy[] = ":";
        	char *tok = strtok(lineB,splitBy);
        		if(strcmp("Room Name",tok)==0){
        			roomCount++;
                	}
        }
	return roomCount;
}

Room* roomMaker(char *lineB, int sizeLineB, FILE *lineP,Room *room, int count){
	while(fgets(lineB,sizeLineB,lineP) != NULL){//reads line until end of file
        	char splitBy[] = ":";
        	char *tok = strtok(lineB,splitBy);//splits the line by : to see what type of data it is

        	if(strcmp("Room Name",tok)==0){//identifies the type of info
                	tok = strtok(NULL,splitBy);// gets the second half of the line (type of info:info)
                	tok = strtok(tok,"\n");//takes away the \n at the end
               		tok++;//takes away the space at the front
                	count++;

                	strcpy(room[count].name,tok);//adds room info to structure [rooms names seperated by the room count, that is how they are distinct structures]
                }
       		else if(strcmp("Room Code",tok)==0){
                	tok = strtok(NULL,splitBy);
               		tok = strtok(tok, "\n");//same as above
                	tok++;
                	strcpy(room[count].id,tok);
                }
        	else if(strcmp("Room Description",tok)==0){
                	tok = strtok(NULL,splitBy);
                	tok = strtok(tok, "\n");
                	tok++;
                	strcpy(room[count].description,tok);

                }
        }
	return room;

}


int question(){
 	char answer[50];
        printf("\n\nhow many rooms in the dungeon do you want? ");
        fgets(answer,sizeof(answer),stdin);
        int numMake = atoi(answer);
        printf("\n");
	return numMake;
}
Room* dungeonMaker(Room *dungeonRoom, Room *room, int roomCount, int numMake){

        srand(time(NULL));
        for(int count = 0;count<numMake;count++){
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
                        printf("dungeon room %d: %s <------ starting room\n",count,dungeonRoom[count].name);
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
