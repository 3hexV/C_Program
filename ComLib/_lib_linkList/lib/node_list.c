#include "node_list.h"
#include "string.h"
#include <stdlib.h>

// 链表API

/*
	func	: 创建一个空的链表 
	para	: void
	return	: NODE *headNode,返回一个头节点地址 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
NODE *createNullList(void){
	int i=0;
	NODE *headNode=NULL;
	headNode = (NODE *)malloc(sizeof(NODE));
	
	headNode->next = NULL;
	
	return headNode;
}

/*
	func	: 返回一个新的节点 
	para	: DATA tmpData, 值传递 
	return	: NODE *newNode，返回一个新节点地址 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
NODE *createNewNode(DATA tmpData){
	int i=0;
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	
	newNode->next = NULL;
	
	newNode->data = tmpData;
	
	return newNode;
} 

/*
	func	: 插入节点 / 头插法  
	para	: Node* headNode,DATA tmpData  头节点，DATA结构体 
	return	: void
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
void insertNodeByHead(NODE *headNode, DATA tmpData){
	NODE *fpNode = headNode->next;
	NODE *newNode = createNewNode(tmpData);
	
	// 第一次插入 节点 
	if(fpNode==NULL){
		headNode->next = newNode;
		return;
	}
	
	newNode->next = fpNode->next;
	fpNode->next = newNode;
	return;
}

/*
	func	: 插入节点 / 尾插法 
	para	: Node* headNode,DATA tmpData  头节点，DATA结构体 
	return	: void
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
void insertNodeByEnd(NODE *headNode, DATA tmpData){
	NODE *forNode = headNode;
	NODE *newNode = createNewNode(tmpData);
	
	while(forNode->next != NULL){
		forNode = forNode->next;
	}
	
	forNode->next = newNode;
	return;
}

/*
	func	: 插入节点 在指定节点后 (int类型数据) 
	para	: Node* headNode,int dataId, DATA tmpData  头节点，int的数据ID，DATA结构体 
	return	: void
	more	:是否依赖DATA结构体内部数据类型 ：√ 
*/
void insertNodeByPosDataInt(NODE *headNode, int dataId, DATA tmpData){
	NODE *forNode = headNode;
	NODE *newNode = createNewNode(tmpData);
	
	while(!(forNode->data.num == dataId)){
		forNode = forNode->next;
	}
	
	newNode->next = forNode->next;
	forNode->next = newNode;
	return;
}

/*
	func	: 删除节点 / 通过下标  0为第一个节点 
	para	: Node* headNode,int posIndex  头节点，下标 
	return	: int -1:表空 -2：下标溢出 0：成功 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
int delNodeByPosIndex(NODE *headNode, int posIndex){
	int indexCount=0;
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	if((posIndex-1)>listLength(headNode)) return -2;
	
	while(forNode != NULL){
		if(indexCount == posIndex) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
		indexCount++;
	}
	
	tmpNode->next = forNode->next;
	free(forNode);
	
	return 0;
} 

/*
	func	: 删除节点 / 通过指定数据(int类型数据)  ，只删除第一次查询到的  
	para	: Node* headNode,int dataId  头节点，int的数据ID 
	return	: int -1:表空 0：成功 
	more	:是否依赖DATA结构体内部数据类型 ：√ 
*/
int delNodeByPosDataInt(NODE *headNode, int dataId){
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	tmpNode->next = forNode->next;
	free(forNode);
	
	return 0;
}

/*
	func	: 删除节点 / 通过指定数据 ，删除所有的查询到数据  
	para	: Node* headNode,int dataId  头节点，int的数据ID 
	return	: int -1:表空 0：成功 
	more	:是否依赖DATA结构体内部数据类型 ：√ 
*/
int delNodeByPosDataIntRe(NODE *headNode, int dataId){
	int count=0; 
	NODE *forNode = headNode->next, *tmpNode=headNode;
	NODE *checkNode = forNode;
	if(listIsNull(headNode)) return -1;
	
	while(1){
//		printf("%s|%s\n", dataId, forNode->data.studentInfo.id);
		if(forNode->data.num == dataId)
		{
			tmpNode->next = forNode->next;
			free(forNode);
			count++;
			forNode = tmpNode->next;
			checkNode = forNode;
		}else{
			forNode = forNode->next;
			checkNode = checkNode->next;
			tmpNode = tmpNode->next;
		}
		
		if(checkNode == NULL) break;	
	}
	if(count==0){
		printf("[~]没有该记录\n");
	}else{
		printf("[~]成功删除[%d]条记录\n", count);
	}
	return count;
}

/*
	func	: 更新数据 / 通过指定的数据   
	para	: Node* headNode,int dataId,DATA tmpData  头节点，int的数据ID , DATA
	return	: int -1:表空 0：成功 
	more	:是否依赖DATA结构体内部数据类型 ：√ 
*/
int updateNodeByPosDataInt(NODE *headNode, int dataId, DATA tmpData){
	NODE *forNode = headNode->next, *tmpNode = headNode;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	// update
	forNode->data = tmpData;
	
	return 0;
}

/*
	func	: 更新数据 / 通过指定的下标  
	para	: Node* headNode,int posIndex,DATA tmpData  头节点，下标 , DATA
	return	: int -1:表空 -2：下标溢出 0：成功 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
int updataNodeByPosIndex(NODE *headNode, int posIndex, DATA tmpData){
	int indexCount=0;
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	if((posIndex-1)>listLength(headNode)) return -2;
	
	while(forNode != NULL){
		if(indexCount == posIndex) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
		indexCount++;
	}
	
	// update
	forNode->data = tmpData;
	
	return 0;
}

/*
	func	: 查询打印节点 / 通过指定的数据(int类型数据)   
	para	: Node* headNode,int dataId  头节点，int的数据ID 
	return	: int 1:成功  0：失败 
	more	:是否依赖DATA结构体内部数据类型 ：√ 
*/
int searchNodeByPosDataInt(NODE *headNode, int dataId){
	NODE *forNode = headNode->next;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId){
			// print data
			printFormatInfo(forNode);
			return 1; 
		}
		forNode = forNode->next;
	}
	
	printf("[!]未查询到该条记录\n");
	return 0;
}

/*
	func	: 查询打印节点 / 通过指定的下标 
	para	: Node* headNode,int posIndex  头节点，下标
	return	: int 1:成功  0：失败 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
int searchNodeByPosIndex(NODE *headNode, int posIndex){
	int indexCount=0;
	NODE *forNode = headNode->next, *tmpNode=headNode;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		if(indexCount == posIndex) {
			// print data
			printFormatInfo(forNode);
			return 1;
		}
		indexCount++;
	}
	
	return 0;
}

/*
	func	: 判断链表为空 
	para	: Node* headNode  头节点
	return	: int 1:空  0：不为空 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
int listIsNull(NODE *headNode){
	NODE *forNode = headNode->next;
	
	if(forNode == NULL) return 1;
	else return 0;
}


/*
	func	: 统计链表长度
	para	: Node* headNode  头节点
	return	: int 长度 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
int listLength(NODE *headNode){
	int listLen=0; 
 	NODE *forNode = headNode->next;
	
	if(listIsNull(headNode)) return listLen;
	
	while(forNode != NULL){
		listLen++;
		forNode = forNode->next;
	}
	
	return listLen;
} 

/*
	func	: 打印节点的所有数据
	para	: Node* headNode, int mode   头节点，mode:0 打印全部 mode:1 打印前20 
	return	: int -1:表空  0：成功  
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
int printList(NODE *headNode, int mode){
	NODE *forNode = headNode->next;
	int count=0;
	
	if(listIsNull(headNode)) return -1;
	
	while(forNode != NULL){
		count++; 
		// print data
		printFormatInfo(forNode);
		
		puts("");
		if(mode==1){
			if(count>20){
				break;
			}
		}
		forNode = forNode->next; 
	}
	
	return 0;
}
 
/*
	func	: 固化 数据到hex文件(bin) 
	para	: NODE *headNode, char *filePath   头节点，文件路径 
	return	: int -1:表空  0：成功 -2:文件打开失败 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/
int saveListToHexFile(NODE *headNode, char *filePath){
	NODE *forNode = headNode->next;
	FILE *fp = NULL;
	
	if(listIsNull(headNode)) return -1;
	
	fp = openFile(filePath, "wb", 1);
	if(fp==NULL) return -2;
	
	while(forNode != NULL){
		fwrite(&forNode->data, sizeof(DATA), 1, fp);
		fflush(fp); // 释放文件输入缓存   保证结构体的格式完整 正确 
		forNode = forNode->next;
	}
	
	return 0;
} 

/*
	func	: 从文件（bin)中载入 数据 构成链表
	para	: NODE *headNode, char *filePath   头节点，文件路径 
	return	: int -1:表空  0：成功 -2:文件打开失败 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/ 
int loadListFromHexFile(NODE *headNode, char *filePath){
	NODE *forNode = headNode->next, *tmpNode=NULL;
	FILE *fp = NULL;
	DATA tmpData;
	
	fp = openFile(filePath, "rb", 0);
	if(fp==NULL) return -2;
	
	do{
		fread(&tmpData, sizeof(DATA), 1, fp);
		insertNodeByEnd(headNode, tmpData);
		if(feof(fp)) break;
	}while(1);
	
	// 多读入一个节点 释放掉
	tmpNode = returnFrontEndNode(headNode);
	free(tmpNode->next); 
	tmpNode->next = NULL;
	
	return 0;
}
 
/*
	func	: 返回 最后一个节点 的前一个节点
	para	: NODE *headNode   头节点
	return	: NODE *forNode , 最后一个节点的前一个节点 
	more	:是否依赖DATA结构体内部数据类型 ：×
			 通过forNode->next即可得到尾节点  
*/ 
NODE *returnFrontEndNode(NODE *headNode){
	NODE *forNode = headNode; 
	
	if(listIsNull(headNode)) return NULL;
	
	while(forNode->next->next != NULL){
		forNode = forNode->next;
	}
	
	return forNode;
}

/*
	func	: 释放链表 
	para	: NODE *headNode   头节点
	return	: int -1:表空  0：成功 
	more	:是否依赖DATA结构体内部数据类型 ：× 
*/ 
int freeList(NODE *headNode){
	NODE *forNode = NULL;
	
	if(listIsNull(headNode)) return -1;
	
	do{
		forNode = returnFrontEndNode(headNode);
		if(forNode == NULL) break;
		forNode->next = NULL;
		free(forNode);
	}while(1);
	
	return 0;
}

/*
	func	: 链表排序算法（简单选择）
	para	: NODE *headNode   头节点
	return	: int -1:表空  0：成功 
	more	:是否依赖DATA结构体内部数据类型 ：√ 
*/ 
int listSortFunc(NODE *headNode){
	NODE *endP = returnFrontEndNode(headNode)->next;
	NODE *moveP = headNode->next, *baseP=headNode->next, *standP=headNode;
	DATA tmpData;
	
	if(listIsNull(headNode)) return -1; 
	
	while(baseP!=endP){
	
		moveP = baseP;
		
		standP = moveP;
		moveP = moveP->next;
		
		while(1){
			
			if(standP->data.num>moveP->data.num){
				tmpData = standP->data;
				standP->data = moveP->data;
				moveP->data = tmpData;
			}
			
			moveP = moveP->next;
			if(moveP==NULL) break;
		}
		
		baseP = baseP->next; 
	}
	return 0;
}


/*
	func	: 打印格式化数据 
	para	: NODE *headNode   头节点
	return	: void 
	more	:是否依赖DATA结构体内部数据类型 ：√√√
*/ 
void printFormatInfo(NODE *forNode){
	printf(PF_DATA, DATA_FROMATE);
} 



