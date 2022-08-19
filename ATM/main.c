#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "gen_def.h"
#include "richtext.h"
#include "gui_menu_tool.h"
#include "filehandler.h"
#include "main.h"

/*
	用户：XM （小明） 
	密码：123456
	备注：密码输出错误超过3次，无法登陆。 在./data/infoload.txt中，将3修改为0即可重置登陆次数。 
		./--lib：自定义的库文件
		  --data：系统运行所需的文件缓存
		  --local：语言（CN：中文，EN：英文） 
*/

int main(){
	char str[100][LINE_TEXT_MAX];
	byte inputPara=0;
	
	// 0.检测磁卡有无插入
	checkCard();	
	
	// 1.验证用户 
	if(verifyUser()==0) {
		pSInfo("[~]Enter键继续");
		wait(); 
		return ;
	} 
	
	pSInfo("[~]Enter键继续");
	wait();
	
	// 2.语言选择界面
	initInterface();  
	
	// 3.主菜单界面
	mainInterface();  
	 
	while(1)
	{
		if(langFlag==1){
			pSCursor("\n[主菜单]");
		}else{
			pSCursor("\n[Main menu]");
		}

		userInputInfo();
		scanf("%d", &inputPara);
		
		// 4. 功能选择 
		switch(inputPara)
		{
			// 1.查询
			case 1:
				if(langFlag==1){
					pSCursor("\n[主菜单]-[查询]");
				}else{
					pSCursor("\n[Main menu]-[Query]");
				}
				itemFuncCheck();
				break;
			// 2.取款
			case 2:
				if(langFlag==1){
					pSCursor("\n[主菜单]-[取款]");
				}else{
					pSCursor("\n[Main menu]-[Withdraw money]");
				}
				
				itemFuncUpdate(1);
				break;
			// 3.存款
			case 3:
				if(langFlag==1){
					pSCursor("\n[主菜单]-[存款]");
				}else{
					pSCursor("\n[Main menu]-[Deposit]");
				}
				itemFuncUpdate(2);
				break;
			// 4.转账 
			case 4:
				if(langFlag==1){
					pSCursor("\n[主菜单]-[转账]");
				}else{
					pSCursor("\n[Main menu]-[Account details]");
				}
				itemFuncUpdate(3); 
				break;
			// 5.流水
			case 5:
				if(langFlag==1){
					pSCursor("\n[主菜单]-[流水]");
				}else{
					pSCursor("\n[Main menu]-[Transfer accounts]");
				}
				itemFuncDetails();
				break;
			// 6.退出
			case 6:
				exitFlag = 1;
				break;
			default:
				exitFlag = 2;
				break;
		}
		
		// 清屏幕  
		clearScreen();
		showMenu();
		
		// 退出处理 
		if(exitFlag==1)
		{
			clearScreen();
			if(langFlag==1)
			{
				pSSuccess("\n[~]正常退出成功");
			}else
			{
				pSSuccess("\n[~]Exit Successfully！");
			}
			wait();
			break; 
		}else if(exitFlag==2){
			clearScreen();
			if(langFlag==1)
			{
				pSError("\n[~]异常输入，退出！");
			}else
			{
				pSError("\n[~]Abnormal input, Exit!");
			}
			wait();
			break; 
		}
		
	}
	
	return 0;
}

// 验证用户 
int verifyUser(void){
	char userPasswd[STRING_MAX], tmpUserPasswd[STRING_MAX];
	char userLoadFailedCount[2][STRING_MAX];
	int errorCount = 0, j=0;
	
	fflush(stdin); 
	
	readStrFromFile(USER_LOAD_PATH, userLoadFailedCount); 
	errorCount = atoi(userLoadFailedCount[0]);
	
	if(errorCount>(USER_PASSWD_FAILED_MAX_COUNT-1))
	{
		pSError("[!]您输入密码错误次数达到三次，卡已被冻结，请到柜台解冻！");
		return 0;
	}
	
	again:
	printf("[~]请输入密码：");
	j = strlen(userInfoOnLine.userPasswd);
	strcpy(tmpUserPasswd, userInfoOnLine.userPasswd);
	tmpUserPasswd[j-1] = tmpUserPasswd[j]; 
	
	scanf("%s", userPasswd);
	
	if(strcmp(tmpUserPasswd, userPasswd)) // 密码错误 
	{
		errorCount++;
		if(errorCount>(USER_PASSWD_FAILED_MAX_COUNT-1))
		{
			pSError("[!]您输入密码错误次数达到三次，卡已被冻结，请到柜台解冻！");
			itoa(errorCount, userPasswd, 10);
			writeStrFromFile(USER_LOAD_PATH, userPasswd);
			return 0;
		}else{
			if(errorCount>(USER_PASSWD_FAILED_MAX_COUNT-1))
			{
				pSError("[!]您输入密码错误次数达到三次，卡已被冻结，请到柜台解冻！");
				itoa(errorCount, userPasswd, 10);
				writeStrFromFile(USER_LOAD_PATH, userPasswd);
				return 0;
			}else{
				pSError("[!]密码错误");
			}
			goto again;
		}
	}
	else{
		itoa(errorCount, userPasswd, 10);
		writeStrFromFile(USER_LOAD_PATH, userPasswd);
		return 1;
	} 
} 

// mode:1 取钱   mode:2 存钱  mode:3 转账 
void itemFuncUpdate(byte mode){
	int money=0, quitFlag=0;
	char tmpStr[STRING_MAX*3], tmpStrMoney[STRING_MAX], otherAccount[STRING_MAX];

	fflush(stdin);
	if(mode==3){
		if(langFlag==1)
		{
			printf("对方账号：");
		}else{
			printf("Account number of the opposite party:");
		}
		gets(otherAccount);
	} 

	if(langFlag==1)
	{
		printf("输入金额（只支持百元）[后退:-1]：");
	}else{
		printf("Input amount (only a few hundred)[back:-1]:");
	}
	
	do
	{
		fflush(stdin);
		scanf("%d", &money);
		
		// 退出 
		if(money==-1) {
			quitFlag = 1;
			break;
		}
		
		money = (money/100)*100;
		
		// 余额不足  取款模式 
		if(mode==1)
		{
			if((money>userInfoOnLine.deposit)) {
				if(langFlag==1){
					pSError("[!]余额不足");
				}else{
					pSError("[!]Your balance is not enough.");
				}
				goto cn_next;
			}
		}
		
		// 输入符合规范 
		if((money>0)&&(!(money>(mode==1?30000:50000)))) break;
		
		// 输入不符合规范 
		else{
			// 取款模式 
			if(mode==1)
			{
				if(langFlag==1)
				{
					pSError("[!]金额不规范，或大于3万");	
				}else{
					pSError("[!]The amount is not standardized, or more than 30000");
				}
			}
			// 存款模式 
			else{
				if(langFlag==1)
				{
					pSError("[!]金额不规范，或大于5万");
				}else{
					pSError("[!]The amount is not standardized, or more than 50000");
				}
			}
		}
		
		cn_next:
		if(langFlag==1)
		{
			printf("输入金额（只支持百元）：");
		}else{
			printf("Input amount (only a few hundred):");
		}
		
	}while(1);
	
	if(quitFlag==1){
		return;
	}
	
	// 取款 和 转账 
	if((mode==1)||(mode==3))
	{
		userInfoOnLine.deposit -= money;
	}
	// 存款 
	else if(mode==2){
		userInfoOnLine.deposit += money;
	}

	// 构建数据 
	strcat(tmpStr, userInfoOnLine.userName);
	strcat(tmpStr, userInfoOnLine.userPasswd);
	strcat(tmpStr, itoa(userInfoOnLine.deposit, tmpStrMoney, 10));
	
	// 写入成功	
	if(writeStrFromFile(USER_INFO_PATH, tmpStr)==1)
	{
		// 取款 
		if(mode==1)
		{
			if(langFlag==1)
			{
				pSSuccess("[~]取款成功");
				printf("[~]金额：-%d\n", money);
			}else{
				pSSuccess("[~]Withdrawal successful");
				printf("[~]Amount of money：-%d\n", money);
			}	
		}
		// 存款 
		else if(mode==2){
			if(langFlag==1)
			{
				pSSuccess("[~]存入成功");
				printf("[~]金额：+%d\n", money);
			}else{
				pSSuccess("[~]Deposit succeeded");
				printf("[~]Amount of money：+%d\n", money);
			}
		}
		// 转账 
		else if(mode==3){
			if(langFlag==1)
			{
				pSSuccess("[~]转出成功");
				printf("目标账户：%s\n", otherAccount);
				printf("[~]金额：-%d\n", money);
			}else{
				pSSuccess("[~]Transfer accounts succeeded");
				printf("[~]Amount of money：-%d\n", money);
			}
		}
		if(mode==3){
			accountDetails(mode, money, otherAccount);
		}else{
			accountDetails(mode, money, NULL);
		}
	}
	// 写入失败 
	else
	{
		// 取款 
		if(mode==1)
		{
			if(langFlag==1)
			{
				pSError("[~]取款失败");
			}else{
				pSSuccess("[~]Withdrawal Failed");
			}	
		}
		// 存款
		else if(mode==2){
			if(langFlag==1)
			{
				pSSuccess("[~]存款失败");
			}else{
				pSError("[~]Deposit Failed");
			}
		}
		// 转账 
		else if(mode==3){
			if(langFlag==1)
			{
				pSSuccess("[~]转账失败");
			}else{
				pSError("[~]Transfer accounts Failed");
			}
		}
	}
	
	if(langFlag==1){
		puts("\n[~]Enter键退出");
	}else{
		puts("\n[~]Enter to exit");
	}
	wait();
} 

// 记录近期流水 
void accountDetails(byte mode, int money, char *otherAccount){
	char tmpStr[STRING_MAX*2], tmpMoney[STRING_MAX];
	char nowTime[32] = {0};
    
    getNowTime(nowTime);

    strcpy(tmpStr, "[");
	strcat(tmpStr, nowTime);
	strcat(tmpStr, "  ");
	if(mode==1){		
		strcat(tmpStr, "取款]：￥");
	}else if(mode==2){
		strcat(tmpStr, "存款]：￥");
	}else if(mode==3){
		strcat(tmpStr, "转账]：");
		strcat(tmpStr, "对方账号：");
		strcat(tmpStr, otherAccount);
		strcat(tmpStr, "  ￥");
	}
	printf("%d\n", money);
	itoa(money, tmpMoney, 10);
	strcat(tmpStr, tmpMoney);
	strcat(tmpStr, "\n");
	
	addStrFromFile(SYS_LOG_PATH, tmpStr);	
}

// 查询近期流水 
void itemFuncDetails(void){
	char tmpLog[100][STRING_MAX];
	int i=0, n = readStrFromFile(SYS_LOG_PATH,tmpLog);
	if(langFlag==1)
	{
		pSInfo("[~]近期100条流水:");
	}else{
		pSInfo("[~]Recent 100 account information:");
	}
	for(i=0;i<n;i++)
	{
		puts(tmpLog[i]);
	}
	
	if(langFlag==1){
		puts("\n[~]Enter键退出");
	}else{
		puts("\n[~]Enter to exit");
	}
	wait();
}

// 获取当前时间 
int getNowTime(char *nowTime){
	char acYear[5] = {0};
	char acMonth[5] = {0};
	char acDay[5] = {0};
	char acHour[5] = {0};
	char acMin[5] = {0};
	char acSec[5] = {0};

	time_t now;
    struct tm* timenow;
    
    time(&now);
    timenow = localtime(&now);

    strftime(acYear,sizeof(acYear),"%Y",timenow);
    strftime(acMonth,sizeof(acMonth),"%m",timenow);
    strftime(acDay,sizeof(acDay),"%d",timenow);
    strftime(acHour,sizeof(acHour),"%H",timenow);
    strftime(acMin,sizeof(acMin),"%M",timenow);
    strftime(acSec,sizeof(acSec),"%S",timenow);

	strncat(nowTime, acYear, 4);
	strcat(nowTime, "-");
	strncat(nowTime, acMonth, 2);
	strcat(nowTime, "-");
	strncat(nowTime, acDay, 2);
	strcat(nowTime, " ");
	strncat(nowTime, acHour, 2);
	strcat(nowTime, ":");
	strncat(nowTime, acMin, 2);
	strcat(nowTime, ":");
	strncat(nowTime, acSec, 2);

	return 0;
}

// 查询余额 
void itemFuncCheck(void){
	if(langFlag==1)
	{
		printf("余额:%d", userInfoOnLine.deposit);
		puts("\n[~]Enter键退出");
	}else
	{
		printf("Balance:￥%d", userInfoOnLine.deposit);
		puts("\n[~]Enter to exit");
	}
	
	fflush(stdin);
	getchar();
}

// 等待 、过渡 
void wait(void){
	fflush(stdin);
	getchar();
}

// 载入用户信息 
void loadUserInfo(char *filepath){
	char tmpUserInfo[3][STRING_MAX];
	readStrFromFile(filepath, tmpUserInfo);
	strcpy(userInfoOnLine.userName, tmpUserInfo[0]);
	strcpy(userInfoOnLine.userPasswd, tmpUserInfo[1]);
	userInfoOnLine.deposit = atoi(tmpUserInfo[2]);
//	printf("%s %s %d\n", userInfoOnLine.userName, userInfoOnLine.userPasswd, userInfoOnLine.deposit); 
}

// 格式输入信息 
void userInputInfo(void){
	if(langFlag==1)
	{
		printf("\n[~]输入:");
	}else
	{
		printf("\n[~]input:");
	}
}

// 检查卡插入 
void checkCard(void){
	char c;
	pSInfo("[~]请插入磁卡！（按下P/p代表插入磁卡）");
	
	do{
		c = getchar();
		if((c=='P')||(c=='p'))
		{
			pSSuccess("[~]磁卡插入成功");
			
			// 载入用户信息（用户名和密码  |  用户存款信息） 
			loadUserInfo(USER_INFO_PATH);
			pSInfo("[~]欢迎用户：");
			printf("User: %s\n", userInfoOnLine.userName);
			
			break;
		}else
		{
			pSError("[!]磁卡未插入");
		}
		fflush(stdin);
	}while(1);	
}

// 载入菜单 
void loadMenuConfig(char *filepath){
	char tmpMainItemText[MAIN_TITLE_COUNT+1][STRING_MAX] = {"ATM菜单","查询","存款","取款","转账","退出"};
	int i=0, j=0;
	int r = readStrFromFile(filepath, tmpMainItemText);
	
	j=strlen(tmpMainItemText[0]);
	tmpMainItemText[0][j-1] = tmpMainItemText[0][j];
	strcpy(mainTitle, tmpMainItemText[0]);
	
	for(i=0;i<MAIN_TITLE_COUNT;i++)
	{
		j=strlen(tmpMainItemText[i+1]);
		tmpMainItemText[i+1][j-1] = tmpMainItemText[i+1][j];
	
		strcpy(mainItemText[i], tmpMainItemText[i+1]);
	}
} 

// 初始界面 
void initInterface(void){
	char itemText[2][50] = {"1.中文","2.English"};
	initMenu("请选择语言",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(12);
	showMenu();
	
	printf("\n[~]输入:");
	
	if(getchar() == '2'){ // en : 2
		loadMenuConfig(LOCAL_LANG_EN);
		langFlag = 2;
	}else{ // cn : 1 and other
		loadMenuConfig(LOCAL_LANG_CN);
		langFlag = 1;
	}
	
	clearScreen();
} 

// 主菜单 
void mainInterface(void){
	initMenu(mainTitle, mainItemText, sizeof(mainItemText)/sizeof(mainItemText[0]));
	createMenu(13);
	showMenu();
} 
