#ifndef _INPUT_CHECK_H_
#define _INPUT_CHECK_H_


int checkIntNum(int srcNum, int min, int max);
int checkDoubleNum(double srcNu, double min, double max);
int checkCharIsAlpha(char srcChar);
int checkCharIsNumber(char srcChar);
int checkCharIsSpace(char srcChar);
int checkCharIsOther(char srcChar);
int checkStrIsAlpha(char *srcStr);
int checkStrIsNumber(char *srcStr);
int checkStrIsSpace(char *srcStr);
int checkStrIsOther(char *srcStr);



#endif
