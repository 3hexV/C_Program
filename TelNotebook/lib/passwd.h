#ifndef _PASSWORD_H_
#define _PASSWORD_H_

#include <stdio.h>
#include <windows.h>
#include "richtext.h"
#include "file_handler.h"

#define PW_FIILE_PATH "./data/pw.txt" // encode: ANSI content:default password

int loadPWStr(void);
int checkPWStr(void);
void updatePWData(char *passwd, int errorCount); 

#endif
