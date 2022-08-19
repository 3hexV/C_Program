#ifndef _FILE_HANDLER_H_
#define _FILE_HANDLER_H_
#include "stdio.h"
#include "node_list.h"

#define LINE_TEXT_MAX 100

FILE *openFile(char *filepath, char *openmode, int debugFlag);
int writeStrToFile(char *filepath, char *str);
int readStrFromFile(char *filepath, char str[][LINE_TEXT_MAX]);
void addStrToFile(char *filepath, char *str);


#endif


