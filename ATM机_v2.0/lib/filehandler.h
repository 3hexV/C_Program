#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_
#include "stdio.h"

#define LINE_TEXT_MAX 50

FILE *openFile(char *filepath, char *openmode);
int writeStrFromFile(char *filepath, char *str);
int readStrFromFile(char *filepath, char str[][LINE_TEXT_MAX]);
void addStrFromFile(char *filepath, char *str);


#endif


