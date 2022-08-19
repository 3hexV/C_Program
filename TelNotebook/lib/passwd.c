#include "passwd.h"

char passwordStr[2][LINE_TEXT_MAX]={"\0", "\0"}; // 0: password 1: 输入的错误次数 

// 载入密码文件 
int loadPWStr(void){
	if(readStrFromFile(PW_FIILE_PATH, passwordStr) == 0){
		return 0;
	}else{
		return 1;
	}
	
}

// 验证密码 
int checkPWStr(void){
	char tmpPassword[LINE_TEXT_MAX] = {'\0'};
	int inputError = 0, len=0;
	
	if(passwordStr[1][0]-'3'>=0){ // 错误达到3次 
		pSError("[!]输入密码错误次数达到三次，无法继续验证，请联系管理员");
		return -1; 
	}
	
	len = strlen(passwordStr[0]);
	passwordStr[0][len-1] = passwordStr[0][len];
	inputError = passwordStr[1][0]-'0'; // 载入输入错误次数 
	
	PW_BEGIN_GOTO:
	
	fflush(stdin);
	printf("[~]请输入密码：");
	gets(tmpPassword);
	
	if(!strcmp(passwordStr[0], tmpPassword)){ // 密码正确 
		pSSuccess("[~]密码正确，验证通过");
		
		// 固化信息
		updatePWData(passwordStr[0], inputError);
		
		return 0;
	}else{ // 密码错误 
		inputError ++;
		if(inputError>=3){
			pSError("[!]输入密码错误次数达到三次，无法继续验证，请练习管理员");
			
			updatePWData(passwordStr[0], inputError);
			
			return -1; 
		}else{
			goto PW_BEGIN_GOTO;
		}
	}
}

// 更新密码信息
void updatePWData(char *passwd, int errorCount){
	char base[10] = {errorCount+'0', '\0'};
	
	strcat(passwd, "\n");
	strcat(passwd, base);
	writeStrToFile(PW_FIILE_PATH, passwd);
	
}



