#ifndef _RAND_DATA_H_
#define _RAND_DATA_H_

typedef unsigned int uint;

// date
void randInit();
int randNum(int min, int max);
double randDouble(int begin, int end, uint valueLen);
char *randStr(uint strLength, uint seekId);
char randChar(uint seekId);

int getNowTime(char *nowTime);

#endif
