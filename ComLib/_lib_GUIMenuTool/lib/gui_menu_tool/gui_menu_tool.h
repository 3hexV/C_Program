#ifndef GUI_MENU_TOOL_H
#define GUI_MENU_TOOL_H

#include <stdio.h>
#include <windows.h>


/*
	GUI设计工具库（专用，非通用） 
	作者：3hex (2020.9.26) 
	用法：
		char itemText[3][50] = {"1.Star","2.Stop","3.Quit"};
		initMenu("Menu",itemText,sizeof(itemText)/sizeof(itemText[0]));
		createMenu(20,13);
		showMenu(); 
*/ 


/*
	1.颜色定义（背景色和前景色） 
*/
// 1.1 背景色定义 
#define GMT_B_BLACK 	 		0x00
#define GMT_B_HALF_BLUE  		0x10
#define GMT_B_HALF_GREEN 		0x20
#define GMT_B_HALF_LIGHT_BLUE 	0x30
#define GMT_B_HALF_RED 			0x40
#define GMT_B_HALF_PURPLE 		0x50
#define GMT_B_HALF_YELLOW 		0x60
#define GMT_B_HALF_WHITE 		0x70
#define GMT_B_HALF_GRAY 		0x80
#define GMT_B_BLUE  			0x90
#define GMT_B_GREEN  			0xa0
#define GMT_B_LIGHT_BLUE  		0xb0
#define GMT_B_RED	  			0xc0
#define GMT_B_PURPLE  			0xd0
#define GMT_B_YELLOW  			0xe0
#define GMT_B_WHITE  			0xf0

// 1.2 前景色定义 
#define GMT_F_BLACK 	 		0x00
#define GMT_F_HALF_BLUE  		0x01
#define GMT_F_HALF_GREEN 		0x02
#define GMT_F_HALF_LIGHT_BLUE 	0x03
#define GMT_F_HALF_RED 			0x04
#define GMT_F_HALF_PURPLE 		0x05
#define GMT_F_HALF_YELLOW 		0x06
#define GMT_F_HALF_WHITE 		0x07
#define GMT_F_HALF_GRAY 		0x08
#define GMT_F_BLUE  			0x09
#define GMT_F_GREEN  			0x0a
#define GMT_F_LIGHT_BLUE  		0x0b
#define GMT_F_RED	  			0x0c
#define GMT_F_PURPLE  			0x0d
#define GMT_F_YELLOW  			0x0e
#define GMT_F_WHITE  			0x0f

#define STRING_MAX 50
#define MENU_ITEM_COUNT_MAX 10

typedef struct _Menu{
	char title[STRING_MAX];
	char itemText[MENU_ITEM_COUNT_MAX][STRING_MAX];
	unsigned int itemCount;
}MENU;

typedef struct _Menu_Style{
	int textStyle[2];
	int margin[2];
	char charType;
}MENU_STYLE;

// 设置字体颜色 
void setConsoleTextColor(int backgroundColor,int foregroundColor);

// 设置字体位置，通过xy坐标 
void setConsoleTextPositionByXY(int x,int y);

// 重置所有属性 
void resetAll();

// 清屏 
void clearScreen();

// 初始化菜单 
void initMenu(char title[STRING_MAX],char itemText[MENU_ITEM_COUNT_MAX][STRING_MAX],unsigned int itemCount);

// 显示菜单 
void showMenu();

// 创建一个菜单 
void createMenu(unsigned int marginLeft,unsigned int styleID);

// 菜单风格选择器 
void menuStyleSelecter(unsigned int styleID);

#endif
