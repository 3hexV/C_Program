#ifndef _PASSWORD_H_
#define _PASSWORD_H_

#include <stdio.h>
#include <windows.h>
#include "richtext.h"
#include "filehandler.h"

#define PW_FIILE_PATH "./data/pw.txt" // encode: ANSI content:default password

/* 
 	filename : passwd.h/.c 
 	version  : v1.0
	content  : √‹¬Î—È÷§API 
 	author   : 3hex
 	date     : 2020-11-18 
*/ 

void loadPWStr(void);
int checkPWStr(void);
void updatePWData(char *passwd, int errorCount); 

#endif
