#ifndef _MAIN_H_
#define _MAIN_H_

#define WORD_ITEM_MAX 100
#define WORD_STRING_LENGTH_MAX 100
#define WORD_LIST_PATH "./data/wordlist.txt"
#define ITEM_COUNT 10

// 单词结构体 
typedef struct _Selection{
	char englishWord[100];
	char chineseWord[100];
}SELECTIOIN;

// 选项 
typedef struct _Question{
	SELECTIOIN pos[4]; // 选项 
	int trueSelection; // 正确答案下标 
	int grade;    // 分数
	int mode; // 问题模式  1：中译英  2：英译中 
}QUESTION;

// 用户单次成绩结构体
typedef struct _UserGrade{
	char nowTime[32];
	int grade;
}USERGRADE; 

// 用户成绩结构体
typedef struct _SysUserGrade{
	USERGRADE userGradeTen[10];
	USERGRADE userGradeMax;
}SYSUSERGRADE; 

SYSUSERGRADE sysUserGrade;

SELECTIOIN exSelection[WORD_ITEM_MAX];

void sysInit(void);
int splitString(char *posString, char resString[][WORD_STRING_LENGTH_MAX]);
int loadWordByFile(char *filePath);
void showMainMenu(void);
void randSelection(int itemLengthMax, int index);
int selectIndex(int key);

void itemBeginGame(void);
void itemGradeRule(void);
void printUserGrade(int mode);

void countUserGrade(QUESTION *tmpQuestion);

void debug_showArr(void);

#endif
 
