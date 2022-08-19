#include "richtext.h"
#include <stdio.h>
#include <time.h>
#include <windows.h>
/*
	功能：打印提示字符串（蓝色字体） 
*/  


// 等待 、过渡 
void wait(void){
	printf("Enter键继续...");
	fflush(stdin);
	getchar();
}


void pSCursor(char *tmpString)
{
	_setConsoleTextColor(GMT_B_RED,GMT_F_HALF_WHITE);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

void pSInfo(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_HALF_LIGHT_BLUE);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCInfo(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_HALF_LIGHT_BLUE);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	功能：打印警报字符串（黄色字体） 
*/  
void pSWarning(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_YELLOW);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCWarning(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_YELLOW);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	功能：打印错误符串（红色字体） 
*/  
void pSError(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_RED);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCError(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_RED);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	功能：打印正确提示字符串（绿色字体） 
*/  
void pSSuccess(char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_GREEN);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}
void pSCSuccess(char *tmpC, char *tmpString)
{
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_GREEN);
	printf("%s",tmpC);
	puts(tmpString);
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
}

/*
	功能：设置字体颜色
	参数：背景色，前景色（字体颜色）[可以使用整数] 
	返回：无 
*/  
void _setConsoleTextColor(int backgroundColor,int foregroundColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor | foregroundColor);
}
