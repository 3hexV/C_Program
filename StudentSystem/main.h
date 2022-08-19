#ifndef _MAIN_H_
#define _MAIN_H_

#define DATA_FILE_PATH "./data/std_info.bin"
#define USER_FIRST_USE_PATH "./data/flag.bin"

void mainMenu();
void systemInit(void);

void funcInputInfo(void);
void funcSearchInfo(void);
void funcCountStdNum(void);
void funcDelStdInfo(void);
void funcUpdateStdInfo(void);
void funcInsertStdInfo(void);
void funcSortList(void);
void funcPrintListNew(void);


int loadInfoFromDataFile();
int saveInfoToDataFile();

int checkFirstUser(void);

void randTenInfo(void);

#endif 
