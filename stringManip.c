#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "stringManip.h"

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

