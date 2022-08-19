#include "gui_menu_tool.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

/*
	简单GUI设计工具库（专用，非通用） 
	作者：3hex (2020.9.26) 
	用法：
		char itemText[3][50] = {"1.Star","2.Stop","3.Quit"};
		initMenu("Menu",itemText,sizeof(itemText)/sizeof(itemText[0]));
		createMenu(20,13);
		showMenu(); 

*/ 
MENU menu;
MENU_STYLE menuStyle = {{GMT_B_BLACK,GMT_F_WHITE}, '-'};
 
/*
	功能：初始化菜单 
	参数：标题，条目列表，条某数量 
	返回：无 
*/
void initMenu(char title[STRING_MAX],char itemText[MENU_ITEM_COUNT_MAX][STRING_MAX],unsigned int itemCount)
{
	unsigned int i=0;
	strcpy(menu.title,title);
	menu.itemCount = itemCount;
	
	for(i=0;i<itemCount;i++)
	{
		strcpy(menu.itemText[i],itemText[i]);
	}
} 

/*
	功能：创建一个菜单 
	参数：marginLeft[左边距], styleID[风格]
	返回：无 
*/
/*
	styleID: AB
	A: 1:'*' 2:'-'(def) 3:'#'
	B: 1:B_BLACK F_WHITE(def) 2:B_RED F_WHITE 3: B_WHITE F_BLACK
	ex: 23表示 使用"#"作为边界字符，采用白底黑字 
*/ 
void createMenu(unsigned int marginLeft,unsigned int styleID)
{
	menuStyleSelecter(styleID);
	menuStyle.margin[0] = marginLeft;
	menuStyle.margin[1] = 0;
}

/*
	功能：显示菜单  
	参数：无 
	返回：无 
*/
void showMenu()
{
	int i=0,j=0;
	//clearScreen();
	setConsoleTextColor(menuStyle.textStyle[0], menuStyle.textStyle[1]);
	setConsoleTextPositionByXY(menuStyle.margin[0],menuStyle.margin[1]);
	
	putchar(menuStyle.charType);
	printf("\t\t");
	printf(menu.title);
	printf("\t\t");
	putchar(menuStyle.charType);
	setConsoleTextPositionByXY(menuStyle.margin[0],1+menuStyle.margin[1]);
	
	
	for(i=0;i<menu.itemCount;i++){
		setConsoleTextPositionByXY(menuStyle.margin[0],i+2+menuStyle.margin[1]);
		putchar(menuStyle.charType);
		printf("\t\t");
		printf(menu.itemText[i]);
		printf("\t\t");
		putchar(menuStyle.charType);
	}
	resetAll();
}

/*
	功能：菜单风格选择器，根据styleID对菜单进行风格设计 
	参数：无 
	返回：无 
*/
void menuStyleSelecter(unsigned int styleID)
{
	switch(styleID/10)
	{
		case 1:
			menuStyle.charType = '*';
			break;
		case 21:
			menuStyle.charType = '-';
			break;
		case 3:
			menuStyle.charType = '#';
			break;
		default:
			menuStyle.charType = '-';
			break;	
	}
	
	switch(styleID%10)
	{
		case 1:
			menuStyle.textStyle[0] = GMT_B_BLACK;
			menuStyle.textStyle[1] = GMT_F_WHITE;
			break;
		case 2:
			menuStyle.textStyle[0] = GMT_B_RED;
			menuStyle.textStyle[1] = GMT_F_WHITE;
			break;
		case 3:
			menuStyle.textStyle[0] = GMT_B_WHITE;
			menuStyle.textStyle[1] = GMT_F_BLACK;
			break;
		default:
			menuStyle.textStyle[0] = GMT_B_BLACK;
			menuStyle.textStyle[1] = GMT_F_WHITE;
			break;	
	}
}

/*
	功能：设置字体颜色
	参数：背景色，前景色（字体颜色）[可以使用整数] 
	返回：无 
*/  
void setConsoleTextColor(int backgroundColor,int foregroundColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor | foregroundColor);
}

/*
	功能：设置字体位置，通过xy坐标 
	参数：x,y 
	返回：无 
*/  
void setConsoleTextPositionByXY(int x,int y)
{
	COORD c;
	c.X = x, c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);	
} 

/*
	功能：重置所有属性  
	参数：无
	返回：无 
*/ 
void resetAll()
{
	setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
} 

/*
	功能：清屏  
	参数：无
	返回：无 
*/  
void clearScreen()
{
	system("cls");
}

