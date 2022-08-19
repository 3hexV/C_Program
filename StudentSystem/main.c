#include <stdio.h>
#include <stdlib.h>
#include "gui_menu_tool.h"  // 菜单API 
#include "richtext.h"       // 富文本API 
#include "filehandler.h"	// 文件操作API 
#include "gen_def.h"		// 通用宏定义API 
#include "main.h"			
#include "nodelist.h"		// 链表操作API 
#include "passwd.h"			// 密码登陆API 

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
		
		printf("第一次使用，请设置密码：");
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
	
	// 验证密码 
	loadPWStr();
	if(checkPWStr()==-1){
		wait();
		return 0;
	}
	wait();
	
	// 菜单初始化 
	begin:
	mainMenu();
	
	// 输入检测模块 
	do{
		printf("\n请输入:");
		
		userInput = getchar();
		fflush(stdin);
		if(((userInput-'0')>=0)&&((userInput-'0')<=9)) {
			break;
		}
		else{
			mainMenu();
		}
	}while(1);
	
	
	// 功能选择模块
	switch(userInput){
		case '0': // 退出
			exitFlag = 0; 
			break;
		case '1': // 录入信息 
			funcInputInfo();
			exitFlag = 1; 
			break;
		case '2': // 查询成绩 
			funcSearchInfo();
			exitFlag = 2; 
			break;
		case '3': // 删除成绩 
			funcDelStdInfo();
			exitFlag = 3; 
			break;
		case '4': // 修改成绩 
			funcUpdateStdInfo();
			exitFlag = 4; 
			break;
		case '5': // 插入成绩 
			funcInsertStdInfo();
			exitFlag = 5;
			break;
		case '6': // 排序 
			funcSortList();
			exitFlag = 6;
			break;
		case '7': // 统计人数 
			funcCountStdNum();
			exitFlag = 7;
			break;
		case '8': // 打印前 20条信息 
			funcPrintListNew();
			exitFlag = 8;
			break;
		case '9': // 
			randTenInfo();
			exitFlag = 9;
			break;
		default:
			exitFlag = -1; // 输入异常 
			break;
	}
	
	// 异常退出处理模块
	if(exitFlag<0){ // 异常退出 
	pSError("[~]系统发生错误，退出系统");
		exit(exitFlag);
	}else if(exitFlag==0){
		//...
		pSSuccess("[~]系统正常退出");
		exit(exitFlag);
	}else{
		//...
		wait();
		goto begin;
	}
	
	return 0;
}

void randTenInfo(void){
	int i=0;
	DATA tmpData;
	
	for(i=0;i<10;i++){
		tmpData = randStdInfo(i);
		insertNodeByEnd(nodeHead, tmpData);
	}
	pSSuccess("[~]随机生成10条记录成功");
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]保存数据成功");
	}else{
		pSError("[~]保存数据失败"); 
	}
}

// 系统参数 初始化 
void systemInit(void){
	srand(time(NULL));
	
	// 初始化头节点 
	nodeHead = createNullList();
	
	// 载入 文件中的数据
	loadInfoFromDataFile();
//	if(loadInfoFromDataFile()){
//		pSSuccess("[~]载入成功");
//	}else{
//		pSError("[~]载入失败"); 
//	} 
	
} 

int checkFirstUser(void){
	FILE *fp = openFile(USER_FIRST_USE_PATH, "rb", 0);
	if(fp==NULL){ // 第一次使用系统 
		openFile(USER_FIRST_USE_PATH, "wb", 0); 
		return 1;
	}else{     // 不是第一次使用系统 
		return 0;
	}
} 

void funcSortList(void){
	listSortFunc(nodeHead);
	pSSuccess("[~]排序完成(按学号排序)");
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]保存数据成功");
	}else{
		pSError("[~]保存数据失败"); 
	}
}

void funcInsertStdInfo(void){
	int insertInfoCount=0, i=0, flag=0;
	int inputDataId=0;
	char tmpChar; 
	DATA tmpData;
	
	// 用户输入模块
	do{
		mainMenu();
		printf("\n请输入学号（插入）:\n");
		scanf("%d", &inputDataId);
		fflush(stdin); 
		
		flag = searchNodeByPosData(nodeHead, inputDataId);
		
		// 学号 
		printf("\n[~]请输入学号:");
		scanf("%d", &tmpData.num);
		fflush(stdin); 
		
		// 姓名 
		printf("\n[~]请输入姓名:");
		scanf("%s", tmpData.name);
		fflush(stdin); 
		
		// 年龄 
		printf("\n[~]请输入年龄:");
		scanf("%d", &tmpData.age);
		fflush(stdin); 
		
		// 性别 
		printf("\n[~]请输入性别:");
		scanf("%c", &tmpData.sex);
		fflush(stdin); 
		
		// 手机
		printf("\n[~]请输入手机:");
		scanf("%s", tmpData.mobile);
		fflush(stdin); 
		
		// qq号 
		printf("\n[~]请输入qq号:");
		fflush(stdin); 
		scanf("%s", tmpData.qq);
		
		// 专业 
		printf("\n[~]请输入专业:");
		scanf("%s", tmpData.direction);
		fflush(stdin); 
		
		if(flag==1){
			insertNodeByPosData(nodeHead, inputDataId, tmpData);
		} else{
			insertNodeByEnd(nodeHead, tmpData); 
		}
		
		insertInfoCount++;
		
		printf("该记录插入完成，是否继续插入? y/n：\n");
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // 非y/Y 跳出 
			pSInfo("[~]结束插入"); 
			printf("共插入了%3d条记录\n", insertInfoCount);
			break;
		}
	} while(1);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]保存数据成功");
	}else{
		pSError("[~]保存数据失败"); 
	}
}

void funcUpdateStdInfo(void){
	int updateInfoCount=0, i=0;
	int inputDataId=0;
	char tmpChar; 
	DATA tmpData;
	
	// 用户输入模块
	do{
		mainMenu();
		printf("\n请输入学号（更新）:\n");
		scanf("%d", &inputDataId);
		
		if(searchNodeByPosData(nodeHead, inputDataId)==1){
		// 学号 
		printf("\n[~]请输入学号:");
		scanf("%d", &tmpData.num);
		fflush(stdin); 
		
		// 姓名 
		printf("\n[~]请输入姓名:");
		scanf("%s", tmpData.name);
		fflush(stdin); 
		
		// 年龄 
		printf("\n[~]请输入年龄:");
		scanf("%d", &tmpData.age);
		fflush(stdin); 
		
		// 性别 
		printf("\n[~]请输入性别:");
		scanf("%c", &tmpData.sex);
		fflush(stdin); 
		
		// 手机
		printf("\n[~]请输入手机:");
		scanf("%s", tmpData.mobile);
		fflush(stdin); 
		
		// qq号 
		printf("\n[~]请输入qq号:");
		scanf("%s", tmpData.qq);
		fflush(stdin); 
		
		// 专业 
		printf("\n[~]请输入专业:");
		scanf("%s", tmpData.direction);
		fflush(stdin); 
			
			// 数据 插入到链表中 
			updateNodeByPosData(nodeHead, inputDataId, tmpData); 
			updateInfoCount++;	
		}
		
		printf("该记录修改完成，是否继续修改? y/n：\n");
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // 非y/Y 跳出 
			pSInfo("[~]结束修改"); 
			printf("共更新了%3d条记录\n", updateInfoCount);
			break;
		}
	} while(1);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]保存数据成功");
	}else{
		pSError("[~]保存数据失败"); 
	}
}

void funcPrintListNew(void){
	pSInfo("[~]最近20条记录：");
	printList(nodeHead, 0);
}

void funcDelStdInfo(void){
	int inputDataId=0;
	char tmpChar; 
	
	// 用户输入模块
	do{
		mainMenu();
		fflush(stdin);
		
		// 学号 
		printf("\n[~]请输入学号（删除）:");
		scanf("%d", &inputDataId);
		delNodeByPosDataRe(nodeHead, inputDataId); // 递归删除
		
		printf("\n是否继续删除? y/n：\n");
		
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // 非y/Y 跳出 
			pSInfo("[~]返回主菜单"); 
			break;
		}
	} while(1);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]保存数据成功");
	}else{
		pSError("[~]保存数据失败"); 
	}
}

void funcCountStdNum(void){
	printf("[~]该班级中共有 [%d] 人\n", listLength(nodeHead));
} 

void funcSearchInfo(void){
	int inputDataId=0;
	char tmpChar; 
	
	// 用户输入模块
	do{
		mainMenu();
		fflush(stdin);
		
		// 学号 
		printf("\n[~]请输入学号（查询）:");
		scanf("%d", &inputDataId);
		fflush(stdin); 
		
		searchNodeByPosData(nodeHead, inputDataId); 
		
		printf("\n是否继续查询? y/n：\n");
		
		fflush(stdin);
		tmpChar = getchar();
		
		if(!((tmpChar=='y')||(tmpChar=='Y'))) { // 非y/Y 跳出 
			pSInfo("[~]返回主菜单"); 
			break;
		}
	} while(1);
	
}

void funcInputInfo(void){
	int i=0, nowUserTimer=0, newNodeCount=0;
	char tmpChar;
	DATA tmpData;
	
	// 用户输入模块
	do{
		mainMenu();
		nowUserTimer++;
		printf("\n当前正在录入第%3d个学生信息\n", nowUserTimer);
		
		// 学号 
		printf("\n[~]请输入学号:");
		scanf("%d", &tmpData.num);
		fflush(stdin); 
		
		// 姓名 
		printf("\n[~]请输入姓名:");
		scanf("%s", tmpData.name);
		fflush(stdin); 
		
		// 年龄 
		printf("\n[~]请输入年龄:");
		scanf("%d", &tmpData.age);
		fflush(stdin); 
		
		// 性别 
		printf("\n[~]请输入性别:");
		scanf("%c", &tmpData.sex);
		fflush(stdin); 
		
		// 手机
		printf("\n[~]请输入手机:");
		scanf("%s", tmpData.mobile);
		fflush(stdin); 
		
		// qq号 
		printf("\n[~]请输入qq号:");
		scanf("%s", tmpData.qq);
		fflush(stdin); 
		
		// 专业 
		printf("\n[~]请输入专业:");
		scanf("%s", tmpData.direction);
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
	
//	printList(nodeHead);
	
	if(saveInfoToDataFile()){
		pSSuccess("[~]保存数据成功");
	}else{
		pSError("[~]保存数据失败"); 
	}
}

// 从文件中 载入数据 
int loadInfoFromDataFile(){
	return !loadListFromHexFile(nodeHead, DATA_FILE_PATH);
}

// 数据 保存到文件中 
int saveInfoToDataFile(){
	return !saveListToHexFile(nodeHead, DATA_FILE_PATH);
}

// 主菜单 
void mainMenu(){
	char itemText[10][50] = {"0.退出"
							,"1.录入成绩"
							,"2.查询成绩"
							,"3.删除成绩"
							,"4.修改成绩"
							,"5.插入成绩"
							,"6.排序"
							,"7.统计学生人数"
							,"d-8.近20条记录"
							,"d-9.随机10条记录"};
	clearScreen();
	
	initMenu("学生管理系统",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(17);
	showMenu(); 
	printf("\n\n[info]d-8,d-9为调试功能，实际无此功能");
}
