#include "ctype.h"
#include "inputcheck.h"
#include "gen_def.h"

int checkIntNum(int srcNum, int min, int max) {
	char tmpStr[100];
	srcNum = atoi(itoa(srcNum, tmpStr, 10));
	if((srcNum>=min)&&(srcNum<=max)){
		return 1;
	}
	return 0;
}

int checkDoubleNum(double srcNum, double min, double max) {
	char tmpStr[100];
	//srcNum = atof(ftoa(srcNum, tmpStr, 10));
	if((srcNum>=min)&&(srcNum<=max)){
		return 1;
	}
	return 0;
}

int checkCharIsAlpha(char srcChar) {
	return isalpha(srcChar);
}

int checkCharIsNumber(char srcChar) {
	return isdigit(srcChar);
}

int checkCharIsSpace(char srcChar) {
	return isspace(srcChar);
}

int checkCharIsOther(char srcChar) {
	return !(
	           checkCharIsAlpha(srcChar)
	           || checkCharIsNumber(srcChar)
	           || checkCharIsSpace(srcChar)
	       );
}

int checkStrIsAlpha(char *srcStr) {
	while(*srcStr) {
		if(!checkCharIsAlpha(*srcStr))
			return 0;
		srcStr++;
	}
	return 1;
}

int checkStrIsNumber(char *srcStr) {
	while(*srcStr) {
		if(!checkCharIsNumber(*srcStr))
			return 0;
		srcStr++;
	}
	return 1;
}

int checkStrIsSpace(char *srcStr) {
	while(*srcStr) {
		if(!checkCharIsSpace(*srcStr))
			return 0;
		srcStr++;
	}
	return 1;
}

int checkStrIsOther(char *srcStr) {
	while(*srcStr) {
		if(!checkCharIsOther(*srcStr))
			return 0;
		srcStr++;
	}
	return 1;
}
