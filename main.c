#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Room{ //making the structure
        char name[100];//probably gave a little bit more space than I need
        char id[50];
        char description[900];
	struct Room *north;
	struct Room *east;
	struct Room *south;
	struct Room *west;
} Room;



int main(int numFile, char **fileName){ //take in input from terminal

        FILE *lineP = fopen(fileName[1],"r");                                                           //----------start of initial room array maker-------------
        int roomCount = 0;
        char lineB[900];

        
	
	
	while(fgets(lineB,sizeof(lineB),lineP) != NULL){ //counts # of rooms
        char splitBy[] = ":";
        char *tok = strtok(lineB,splitBy);
        if(strcmp("Room Name",tok)==0){
        roomCount++;
                }
        }





        rewind(lineP); //resets file line pointer, below is initial values
        Room **room;	
        room = malloc(sizeof(Room*)*(roomCount));
        int  count = 0;
        
	
	
	while(fgets(lineB,sizeof(lineB),lineP) != NULL){//reads line until end of file                        
        char splitBy[] = ":";
        char *tok = strtok(lineB,splitBy);//splits the line by : to see what type of data it is



        if(strcmp("Room Name",tok)==0){//identifies the type of info
                tok = strtok(NULL,splitBy);// gets the second half of the line (type of info:info)
                tok = strtok(tok,"\n");//takes away the \n at the end
                tok++;//takes away the space at the front
                count++;
                room[count] = malloc(sizeof(Room));
                strcpy(room[count]->name,tok);//adds room info to structure [rooms names seperated by the room count, that is how they are distinct structures]
                }
        else if(strcmp("Room Code",tok)==0){
                tok = strtok(NULL,splitBy);
                tok = strtok(tok, "\n");//same as above
                tok++;
                strcpy(room[count]->id,tok);
        }
        else if(strcmp("Room Description",tok)==0){
                tok = strtok(NULL,splitBy);
                tok = strtok(tok, "\n");
                tok++;
                strcpy(room[count]->description,tok);
                printf("Room %s: %s ---------- room[%d]\n",room[count]->id,room[count]->name,count);//prints the output when it gets to the last part of the room
        	}
        }
											//---------- end of initial room array maker
	room[1]->east = room[2];
	printf("room[2] code: %s\n",room[2]->id);
	printf("room east of room[1] code: %s\n",room[1]->east->id);
	
	int roomNumlist[roomCount];
	for(int count=0; count <roomCount; count ++){
	roomNumlist[count]= count+1;
	printf("room slot[%d]: %d\n",count,count+1);
	
	}


	

        fclose(lineP);//closes file
        for(int count = 1; count < roomCount+1; count++){
                free(room[count]);
        }
        free(room);									
 

return 0;
}

