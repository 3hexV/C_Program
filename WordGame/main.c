#include <stdio.h>
#include <stdlib.h>
//#include <ctpye.h>
#include "gui_menu_tool.h"
#include "richtext.h"
#include "filehandler.h"
#include "gen_def.h"
#include "main.h"

extern SELECTIOIN exSelection[WORD_ITEM_MAX];
extern SYSUSERGRADE sysUserGrade;
int trueSelectionAllCount[ITEM_COUNT] = {-1}, tureSelectionIndex=0;
int gameNowTimer = 0, exitFlag=-1;


int main() {
	char tmpMainInput;

	sysInit();
	
	mainBegin:
	clearScreen();
	showMainMenu();

	// 输入模块 
	do{
		printf("\n请输入：");
		scanf("%c", &tmpMainInput);
		fflush(stdin); // 清空输入缓存 
		if((tmpMainInput-'1'>=0)&&(tmpMainInput-'1'<=2)) break;
	}while(1);
	
	// 处理模块 
	switch(tmpMainInput){
		case '1': // 开始闯关 
			itemBeginGame();
			exitFlag = 1;
			break;
		case '2': // 积分规则 
			itemGradeRule();
			exitFlag = 1;
			break;
		case '3': // 退出系统 
			exitFlag = 0;
			break;
		default:
			break;
	}
	
	// 异常退出模块 
	if(exitFlag<=0){
		pSSuccess("[~]正常退出成功");
		return 0;
	}else{
		goto mainBegin; 
	}
	
	return 0;
}

void itemGradeRule(void){
	pSError("1.每次随机出现中译英、英译中(共10题)");
	pSWarning("2.每次答对奖励一分");
	pSSuccess("3.每次答错不扣分");
	
	printf("\n\n[~]最高成绩:\n");
	if(gameNowTimer!=0){
		printf("[时间]:%s\t[成绩]:%d\n", sysUserGrade.userGradeMax.nowTime, 
										sysUserGrade.userGradeMax.grade);
	}else{
		pSInfo("您未开始过游戏，没有最高记录！"); 
	}
	
	printf("[~]近10次成绩:\n");
	printUserGrade(0);
	wait();
}

void itemBeginGame(void){
	char nowTime[32] = {0}; 
	int len=0, i=0, maxIndex=0; 
	len = loadWordByFile(WORD_LIST_PATH);
	
	// 初始化这次成绩 
	sysUserGrade.userGradeTen[gameNowTimer].grade = 0;
	getNowTime(nowTime);
	strcpy(sysUserGrade.userGradeTen[gameNowTimer].nowTime, 
			nowTime); 
	
	// 开始游戏 
	for(i=0;i<ITEM_COUNT;i++){
		randSelection(len, i);
	}
	
	// 打印本次成绩
	printUserGrade(gameNowTimer+1);
//	printUserGrade(0);
	
	gameNowTimer++;
	
	// 清空答题记录 
	for(i=0;i<ITEM_COUNT;i++){
		trueSelectionAllCount[i] = -1;
	}
	
	// 统计最大分数 
	sysUserGrade.userGradeMax = sysUserGrade.userGradeTen[0];
	for(i=0;i<10;i++){
		if(sysUserGrade.userGradeTen[i].grade>sysUserGrade.userGradeMax.grade)
		{
			maxIndex = i;
		}
	}
	if(maxIndex!=0){
		sysUserGrade.userGradeMax = sysUserGrade.userGradeTen[maxIndex];
	}
	
	wait();
} 

// 打印成绩 
// mode: 0 全部成绩 
// 否则 打印对应的 下标的成绩 ，最大为10 
void printUserGrade(int mode){
	int i=0, n=(gameNowTimer<10)?gameNowTimer:10;
	if(mode==0){
		for(i=0;i<n;i++){  // <-----------------
			if(gameNowTimer!=0)
				printf("[次数]%d\t[时间]:%s\t[成绩]:%d\n", i+1, sysUserGrade.userGradeTen[i].nowTime, 
										sysUserGrade.userGradeTen[i].grade);
		}
		for(;i<10;i++){
			printf("[次数]%d\t[时间]:%s\t[成绩]:%s\n", i+1,"\\", "\\");
		}
	}else if(mode<=10){
		printf("[次数]%d\t[时间]:%s\t[成绩]:%d\n", mode, sysUserGrade.userGradeTen[mode-1].nowTime, sysUserGrade.userGradeTen[mode-1].grade);
	}else{
		printf("只保留近10次记录：\n[次数]%d\t[时间]:%s\t[成绩]:%d\n", 10, sysUserGrade.userGradeTen[9].nowTime, 
														sysUserGrade.userGradeTen[9].grade);
	}
}

// 系统必要的初始化 
void sysInit(void)
{
	int i=0;
	for(i=0;i<ITEM_COUNT;i++){
		trueSelectionAllCount[i] = -1;
	}
	
	srand(time(NULL));
}

// 随机出一个 问题
// 一个正确的 3个错误的
void randSelection(int itemLengthMax, int index){
	int i=0, randNum[4]={0}, tmpIndex=0;
	QUESTION exQuestion;
	
	puts("");
	
	// 产生4个伪随机数
	do{
		tmpIndex = rand()%itemLengthMax;
	}while(selectIndex(tmpIndex));
	
//	debug_showArr();
	
	randNum[0] = tmpIndex;
	
	if(tureSelectionIndex<ITEM_COUNT)
		trueSelectionAllCount[tureSelectionIndex++] = randNum[0]; // 记录做过的题目 
	
	randNum[1] = (randNum[0]+3)%itemLengthMax;
	randNum[2] = (randNum[1]+3)%itemLengthMax;
	randNum[3] = (randNum[2]+3)%itemLengthMax;
	
//	printf("%d , %d %d %d %d\n",itemLengthMax, randNum[0], randNum[1],randNum[2],randNum[3]);
	
	// 装载选项 
	i=0;	 
	exQuestion.pos[0] = exSelection[randNum[0]];
	exQuestion.pos[1] = exSelection[randNum[1]];
	exQuestion.pos[2] = exSelection[randNum[2]];
	exQuestion.pos[3] = exSelection[randNum[3]];
	
	exQuestion.trueSelection =  rand()%4; // 随机正确答案
	exQuestion.grade = 1; 
	exQuestion.mode = rand()%2+1; // 随机问题模式  
	
	// 显示
	// 题号 
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_LIGHT_BLUE);
	
	printf("%d.", index+1);
	
	if(exQuestion.mode == 1){ // 中译英 
		printf("[%s] 的正确翻译:\n", 
		exQuestion.pos[exQuestion.trueSelection].chineseWord);
	}else if(exQuestion.mode == 2){// 英译中  
		printf("[%s] 的正确翻译:\n", 
		exQuestion.pos[exQuestion.trueSelection].englishWord);
	}
	for(i=0;i<4;i++)
	{
		if(exQuestion.mode == 1){ // 中译英 
			printf("%c. %s\t\t", 'A'+i, exQuestion.pos[i].englishWord);
		}else if(exQuestion.mode == 2){// 英译中 
			printf("%c. %s\t\t", 'A'+i, exQuestion.pos[i].chineseWord); 
		}
	} 
	_setConsoleTextColor(GMT_B_BLACK,GMT_F_WHITE);
	
	puts("");
	
	// 统计这次的成绩 
	countUserGrade(&exQuestion);
}

void countUserGrade(QUESTION *tmpQuestion){
	 char tmpInput;
	
	do{
		printf("\n请输入答案：");
		tmpInput = getchar();
		fflush(stdin);
		if((((tmpInput-'A')<=3)&&((tmpInput-'A')>=0))||
			(((tmpInput-'a')<=3)&&((tmpInput-'a')>=0)))
			break;
	}while(1);
	
	// 加分 
	if(((tmpInput-'A')==tmpQuestion->trueSelection)
		||((tmpInput-'a')==tmpQuestion->trueSelection)){
			sysUserGrade.userGradeTen[gameNowTimer].grade += tmpQuestion->grade;
		}
}

// 查询 伪随机数 有无重复 
int selectIndex(int key){
	int i=0, end=ITEM_COUNT-1;
	int low=0,high=0,mid=0;
	// 排序 
	while(end){
		for(i=0;i<=end;i++)
		{
			if(trueSelectionAllCount[i]>trueSelectionAllCount[i+1]){
				SWAP(trueSelectionAllCount[i], trueSelectionAllCount[i+1]);
			}
		}
		end--;
	}
//	printf("Key:%d\n", key);
	// 二分法
	low = 0, high = ITEM_COUNT-1;
	while(low<high){
		mid = (low+high)/2;
		if(trueSelectionAllCount[mid] == key){
//			puts("true");
			return 1;
		}else if(trueSelectionAllCount[mid] > key){
			high = mid-1;
		}else{
			low = mid+1;
		}
	}
//	puts("false");
	return 0;
} 

// 载入单词
int loadWordByFile(char *filePath){
	int i=0, readedLength=0, j=0;
	char tmpWordString[WORD_ITEM_MAX][WORD_STRING_LENGTH_MAX], tmpString[2][WORD_STRING_LENGTH_MAX];
	readedLength = readStrFromFile(WORD_LIST_PATH , tmpWordString); // 载入单词文件
	for(i=0;i<readedLength;i++){
		// 去除换行 
		j = strlen(tmpWordString[i]);
		tmpWordString[i][j-1] = tmpWordString[i][j];
		
		// 切割字符串 
		if(splitString(tmpWordString[i], tmpString))
		{
			// 载入 
			strcpy(exSelection[i].englishWord, tmpString[0]);
			strcpy(exSelection[i].chineseWord, tmpString[1]);
		//	printf("%s @ %s\n", exSelection[i].englishWord, exSelection[i].chineseWord);
		}
	} 
	return readedLength;
} 

// 拆分字符串 dev:space(ASCII:\s \t) 
int splitString(char *posString, char resString[][WORD_STRING_LENGTH_MAX]){
	char *p = posString;
	int i=0;
	if(isspace(posString[i])) return 0;
	
	// english
	while(isalpha(*p))
	{
		(*resString)[i++] = *p;
		p++;
	}
	(*resString)[i] = '\0';
	resString++;
	
	while(isspace(*p)) p++;
	
	// chinese
	i=0;
	while(*p)
	{
		(*resString)[i++] = *p;
		p++;
	}
	(*resString)[i] = '\0';
	return 1;
}

// 主界面 
void showMainMenu(void){
	char itemText[3][50] = {"1.开始练习","2.积分规则","3.退出练习"};
	initMenu("单词闯关游戏",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(16);
	showMenu(); 
}

void debug_showArr(void){
	int i=0;
	for(i=0;i<ITEM_COUNT;i++){
		if(i%5==0)
			puts("");
		printf("%d\t", trueSelectionAllCount[i]);
	}
}
