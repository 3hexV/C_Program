#include "file_handler.h"
#include <stdio.h>


FILE *openFile(char *filepath, char *openmode, int debugFlag)
{
	FILE *f;
	if((f = fopen(filepath, openmode)) == NULL)
	{
		if(debugFlag==1){
			puts("[ERROR]文件打开出错！");
		}
		return NULL; 
	}
	return f;
}
 
int writeStrToFile(char *filepath, char *str)
{
	FILE *f;
	
	f = openFile(filepath, "w", 1);
	if(f==NULL) return 0;
	
	fprintf(f, "%s\n", str);
	fclose(f);
	return 1;
}

void addStrToFile(char *filepath, char *str)
{
	FILE *f;
	
	f = openFile(filepath, "a+", 1);
	if(f==NULL) return;
	
	fprintf(f, "%s\n", str);
	fclose(f);
	return;
}

int readStrFromFile(char *filepath, char str[][LINE_TEXT_MAX])
{
	FILE *f;
	int i=0;
	
	f = openFile(filepath, "r", 1);
	if(f==NULL) return 0;
	
	while(1)
	{
		fgets(str[i], LINE_TEXT_MAX, f);
		i++;
		if(feof(f)) break;
	}
	fclose(f);
	return i;
}




