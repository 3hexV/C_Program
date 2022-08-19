#ifndef _RICH_TEXT_H_
#define _RICH_TEXT_H_

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

int getNowTime(char *nowTime);
void wait(void);

// 设置字体颜色 
void _setConsoleTextColor(int backgroundColor,int foregroundColor);

void pSCursor(char *tmpString);

void pSInfo(char *tmpString); 
void pSCInfo(char *tmpC, char *tmpString);

void pSWarning(char *tmpString); 
void pSCWarning(char *tmpC, char *tmpString);

void pSError(char *tmpString); 
void pSCError(char *tmpC, char *tmpString);

void pSSuccess(char *tmpString); 
void pSCSuccess(char *tmpC, char *tmpString);

#endif
