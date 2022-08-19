#include <stdio.h>
#include <stdlib.h>
#include "gui_menu_tool.h"  // 菜单API 
#include "richtext.h"       // 富文本API 
#include "file_handler.h"	// 文件操作API 
#include "gen_def.h"		// 通用宏定义API 
#include "main.h"
#include "node_list.h"		// 链表操作API 
#include "passwd.h"			// 密码登陆API 
#include "rand_data.h"      
#include "inputcheck.h"     


#define S_N 5
int exitFlag=0; // >0:正常退出  ==0:正常退出  <0:异常退出
NODE *nodeHead = NULL;

int main() {
	char userInput;
	char tmpPW[100];

	// 第一次使用系统
	if(checkFirstUser()==1) {
		pSInfo("[~]第一次使用系统，系统自检启动中...");
		// check...
		Sleep(1000);

		pSInfo("[~]正在进行必要配置，请耐心等待...");
		// config...
		Sleep(500);

		pSInfo("[~]即将完成配置...");
		// finally config...
		Sleep(500);

		printf("[~]第一次使用，请设置密码：");
		// set load passwd
		gets(tmpPW); 
		updatePWData(tmpPW, 0);
		pSSuccess("[~]登陆密码设置成功");
		

		Sleep(500);
		pSSuccess("[~]启动完成");
		wait();
	}

	// 系统初始
	systemInit();
	
	loadPWStr();
	// 验证密码
	if(checkPWStr()==-1) {
		wait();
		return 0;
	}
	wait();

	// 菜单初始化
begin:
	mainMenu();

	// 输入检测模块
	do {
		printf("\n请输入:");

		userInput = getchar();
		fflush(stdin);
		if(((userInput-'0')>=1)&&((userInput-'0')<=8)) {
			break;
		} else {
			mainMenu();
		}
	} while(1);


	// 功能选择模块
	switch(userInput) {
		case '1': // 录入
			funcInputInfo();
			exitFlag = 1;
			break;
		case '2': // 删除
			funcDelStdInfo();
			exitFlag = 2;
			break;
		case '3': // 打印
			funcPrintListNew();
			exitFlag = 3;
			break;
		case '4': // 查询
			funcSearchInfo();
			exitFlag = 4;
			break;
		case '5': // 保存
			if(saveInfoToDataFile()) {
				pSSuccess("[~]保存数据成功");
			} else {
				pSError("[~]保存数据失败");
			}
			exitFlag = 5;
			break;
		case '6': // 加载
			if(loadInfoFromDataFile()) {
				pSSuccess("[~]载入成功");
			} else {
				pSError("[~]载入失败");
			}
			exitFlag = 6;
			break;
		case '7': // 退出
			exitFlag = 0;
			break;
		case '8': //
			randTenInfo();
			exitFlag = 8;
			break;
		default:
			exitFlag = -1; // 输入异常
			break;
	}

	// 异常退出处理模块
	if(exitFlag<0) { // 异常退出
		pSError("[~]系统发生错误，退出系统");
		exit(exitFlag);
	} else if(exitFlag==0) {
		//...
		pSSuccess("[~]系统正常退出");
		exit(exitFlag);
	} else {
		//...
		wait();
		goto begin;
	}

	return 0;
}

void randTenInfo(void) {
	int i=0;
	DATA tmpData;

	for(i=0; i<10; i++) {
		tmpData = randNodeData();
		insertNodeByEnd(nodeHead, tmpData);
	}
	pSSuccess("[~]随机生成10条记录成功");

}

// 系统参数 初始化
void systemInit(void) {
	srand(time(NULL));

	// 初始化头节点
	nodeHead = createNullList();

	// 载入 文件中的数据
	loadInfoFromDataFile();

}

int checkFirstUser(void) {
	FILE *fp = openFile(USER_FIRST_USE_PATH, "rb", 0);
	if(fp==NULL) { // 第一次使用系统
		fp = openFile(USER_FIRST_USE_PATH, "wb", 0);
		return 1;
	} else {    // 不是第一次使用系统
		return 0;
	}
}

void funcPrintListNew(void) {
	pSInfo("[~]所有记录：");
	printList(nodeHead, 0);
}

void funcDelStdInfo(void) {
	char inputDataId[100];
	char tmpChar;

	// 用户输入模块
	do {
		mainMenu();
		fflush(stdin);

		// 学号
		printf("\n[~]请输入姓名（删除）:");
		gets(inputDataId);
		delNodeByPosDataStrRe(nodeHead, inputDataId); // 删除

		printf("\n是否继续删除? y/n：\n");

		fflush(stdin);
		tmpChar = getchar();

		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // 非y/Y 跳出
			pSInfo("[~]返回主菜单");
			break;
		}
	} while(1);

}


void funcSearchInfo(void) {
	char inputDataId[100];
	char tmpChar;

	// 用户输入模块
	do {
		mainMenu();
		fflush(stdin);

		// 学号
		printf("\n[~]请输入姓名（查询）:");
		gets(inputDataId);
		fflush(stdin);

		searchNodeByPosDataStr(nodeHead, inputDataId);

		printf("\n是否继续查询? y/n：\n");

		fflush(stdin);
		tmpChar = getchar();

		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // 非y/Y 跳出
			pSInfo("[~]返回主菜单");
			break;
		}
	} while(1);

}

void funcInputInfo(void) {
	int i=0, nowUserTimer=0, newNodeCount=0;
	char tmpChar;
	DATA tmpData;

	// 用户输入模块
	do {
		mainMenu();
		nowUserTimer++;
		printf("\n当前正在录入第%3d个信息\n", nowUserTimer);

		// 
		printf("\n[~]请输入姓名:");
		scanf("%s", tmpData.name);
		fflush(stdin);

		// 
		printf("\n[~]请输入城市:");
		scanf("%s", tmpData.city);
		fflush(stdin);

		// 
		printf("\n[~]请输入省:");
		scanf("%s", tmpData.province);
		fflush(stdin);

		// 
		printf("\n[~]请输入国家:");
		scanf("%s", tmpData.state);
		fflush(stdin);

		// 
		printf("\n[~]请输入电话:");
		scanf("%s", tmpData.tel);
		fflush(stdin);

		// 数据 插入到链表中
		insertNodeByEnd(nodeHead, tmpData);
		newNodeCount++;

		printf("该记录录入完成，是否继续录入? y/n：\n");
		fflush(stdin);
		tmpChar = getchar();
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // 非y/Y 跳出
			pSInfo("[~]结束录入");
			printf("新增%3d条记录\n", newNodeCount);
			break;
		}
	} while(1);
}

// 从文件中 载入数据
int loadInfoFromDataFile() {
	freeList(nodeHead);
	return !loadListFromHexFile(nodeHead, DATA_FILE_PATH);
}

// 数据 保存到文件中
int saveInfoToDataFile() {
	return !saveListToHexFile(nodeHead, DATA_FILE_PATH);
}

// 主菜单
void mainMenu() {
	char itemText[8][50] = {"1.通信录录入"
	                        ,"2.通信录删除"
	                        ,"3.通信录显示"
	                        ,"4.通信录数据查询"
	                        ,"5.通信录数据保存"
	                        ,"6.通信录数据加载"
	                        ,"7.退出系统"
	                        ,"d-8.随机10条记录"
	                       };
	clearScreen();

	initMenu("<通 ·信 ·录>",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(33);
	showMenu();
	printf("\n\n[info]d-8为调试功能，实际无此功能");
}
