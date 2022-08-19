#include <stdio.h>
#include <stdlib.h>
#include "rand_data.h"


int main(void) {
	int i=0;
	
	randInit();
	
	for(i=0;i<100;i++){
//		puts(randStr(3, 3));
//		printf("%d\n", randNum(5,10));
		printf("%lf\n", randDouble(0, 5, 8));
//		puts(randStr(5, 1234));
//		putchar(randChar(2));
	}
	
	return 0;
}
