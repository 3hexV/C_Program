#ifndef _MAIN_H_
#define _MAIN_H_

#define MAIN_TITLE_COUNT (6) 

#define USER_PASSWD_FAILED_MAX_COUNT (3)
#define LOCAL_LANG_EN "./local/en.txt"
#define LOCAL_LANG_CN "./local/cn.txt"
#define USER_INFO_PATH "./data/userinfo.txt"
#define USER_LOAD_PATH "./data/userload.txt"
#define SYS_LOG_PATH "./data/syslog.txt"

typedef struct _userInfo{
	char userName[STRING_MAX];
	char userPasswd[STRING_MAX];
	unsigned int deposit; 
}USERINFO;

USERINFO userInfoOnLine;

void checkCard(void);
void initInterface(void);
void loadMenuConfig(char *filepath);
void mainInterface(void);
void userInputInfo(void);
void loadUserInfo(char *filepath);
void wait(void);

void itemFuncCheck(void);
void itemFuncUpdate(byte mode); 
void itemFuncTransfer(void);
void itemFuncDetails(void);

int verifyUser(void);

void accountDetails(byte mode, int money, char *otherAccount);
int getNowTime(char *nowTime);

char mainItemText[MAIN_TITLE_COUNT][STRING_MAX] = {"查询","存款","取款","转账","退出"};
char mainTitle[STRING_MAX] ="ATM菜单";
byte exitFlag = 0;
byte langFlag = 1;//1 or other:cn  2:en



#endif 
