#include "filehandler.h"
#include <stdio.h>


FILE *openFile(char *filepath, char *openmode)
{
	FILE *f;
	if((f = fopen(filepath, openmode)) == NULL)
	{
		puts("[ERROR]文件打开出错！");
	}
	return f;
}
 
int writeStrFromFile(char *filepath, char *str)
{
	FILE *f;
	
	f = openFile(filepath, "w");
	if(f==NULL) return 0;
	
	fprintf(f, "%s\n", str);
	fclose(f);
	return 1;
}

void addStrFromFile(char *filepath, char *str)
{
	FILE *f;
	
	f = openFile(filepath, "a+");
	if(f==NULL) return;
	
	fputs(str, f);
	fclose(f);
	return;
}

int readStrFromFile(char *filepath, char str[][LINE_TEXT_MAX])
{
	FILE *f;
	int i=0;
	
	f = openFile(filepath, "r");
	if(f==NULL) return 0;
	
	while(1)
	{
		fgets(str[i], LINE_TEXT_MAX, f);
//		printf("%s",str[i]);
		i++;
		if(feof(f)) break;
	}
	fclose(f);
	return i;
}




