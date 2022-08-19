#ifndef _NODE_LIST_H_
#define _NODE_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include "filehandler.h"
 
// 数据结构体 
typedef struct _data{
	// 用户自定义 
	int num;                   	//学号
    char name[10];             	//姓名
    char sex;               	//性别
    int age;           			//年龄
    char mobile[13];           	//手机
    char qq[11];               	//qq号
    char direction[31];         //专业
}DATA;

// 链表节点 
typedef struct _node{
	DATA data;
	struct _node *next;
}NODE; 


NODE *createNullList();
NODE *createNewNode(DATA tmpData);
void insertNodeByHead(NODE *nodeHead, DATA tmpData);
void insertNodeByEnd(NODE *nodeHead, DATA tmpData);
void insertNodeByPosData(NODE *nodeHead, int dataId, DATA tmpData);
int delNodeByPosIndex(NODE *nodeHead, int posIndex);
int delNodeByPosData(NODE *nodeHead, int dataId);
int delNodeByPosDataRe(NODE *nodeHead, int dataId);
int updateNodeByPosData(NODE *nodeHead, int dataId, DATA tmpData);
int updataNodeByPosIndex(NODE *nodeHead, int posIndex, DATA tmpData);
int searchNodeByPosData(NODE *nodeHead, int dataId);
int searchNodeByPosIndex(NODE *nodeHead, int posIndex);
int printList(NODE *nodeHead, int mode);

NODE *returnFrontEndNode(NODE *nodeHead);
int freeList(NODE *nodeHead);

int listIsNull(NODE *nodeHead);
int listLength(NODE *nodeHead);

int saveListToHexFile(NODE *nodeHead, char *filePath);
int loadListFromHexFile(NODE *nodeHead, char *filePath);

//sort
int listSortFunc(NODE *nodeHead);

// debug func
DATA randStdInfo(int flag);


#endif 
