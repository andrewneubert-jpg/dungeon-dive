#ifndef ROOMMANIP_H
#define ROOMMANIP_H
#include <stdio.h>

typedef struct Room{ //making the structure
        char name[100];//probably gave a little bit more space than I need
        char id[50];
        char description[900];
        struct Room *north;
        struct Room *east;
        struct Room *south;
        struct Room *west;
} Room;
		   
int roomCounter(int roomCount, char *lineB, FILE *lineP, int sizeLineB); //forward declaring the functions
Room* roomMaker(char *lineB, int sizeLineB, FILE *lineP,Room *room, int count);
Room* dungeonMaker(Room *dungeonRoom, Room *room, int roomCount, int numMake);
#endif
