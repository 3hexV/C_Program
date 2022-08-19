#include "nodelist.h"
#include "string.h"
#include <stdlib.h>

// 链表API

// 随机一条信息 
DATA randStdInfo(int flag)
{
	//学号//姓名//性别//年龄//手机//qq号//专业
	char tmpStr[100];
	DATA *tmpData = (DATA *)malloc(sizeof(DATA));

	tmpData->num = 1000 + flag;  // 学号 
	
	tmpStr[0] = flag+'A', tmpStr[1] = '\0';
	strcat(tmpStr, "Name");
	strcpy(tmpData->name, tmpStr); // 姓名 
	
	tmpStr[0] = (rand()%2?'M':'W');
	tmpData->sex = tmpStr[0]; // 性别
	
	tmpData->age = rand()%11+20; // 年龄 20-30
	
	strcpy(tmpData->mobile, "180 0000 000"); // 手机
	
	strcpy(tmpData->qq, "777 000"); // qq号
	
	strcpy(tmpData->direction, "ZY"); // 专业
	
	return *tmpData;
}

// 创建一个空的链表 
NODE *createNullList(){
	int i=0;
	NODE *nodeHead=NULL;
	nodeHead = (NODE *)malloc(sizeof(NODE));
	
	nodeHead->next = NULL;
	
	return nodeHead;
}

//  创建一个新的节点
NODE *createNewNode(DATA tmpData){
	int i=0;
	NODE *newNode = (NODE *)malloc(sizeof(NODE));
	
	newNode->next = NULL;
	
	newNode->data = tmpData;
	
	return newNode;
} 

// 插入节点 / 头插法 
void insertNodeByHead(NODE *nodeHead, DATA tmpData){
	NODE *fpNode = nodeHead->next;
	NODE *newNode = createNewNode(tmpData);
	
	// 第一次插入 节点 
	if(fpNode==NULL){
		nodeHead->next = newNode;
		return;
	}
	
	newNode->next = fpNode->next;
	fpNode->next = newNode;
	return;
}

// 插入节点 / 尾插法 
void insertNodeByEnd(NODE *nodeHead, DATA tmpData){
	NODE *forNode = nodeHead;
	NODE *newNode = createNewNode(tmpData);
	
	while(forNode->next != NULL){
		forNode = forNode->next;
	}
	
	forNode->next = newNode;
	return;
}

void insertNodeByPosData(NODE *nodeHead, int dataId, DATA tmpData){
	NODE *forNode = nodeHead;
	NODE *newNode = createNewNode(tmpData);
	
	while(!(forNode->data.num == dataId)){
		forNode = forNode->next;
	}
	
	newNode->next = forNode->next;
	forNode->next = newNode;
	return;
}

// 删除节点 / 通过下标  0 为第一个节点 
int delNodeByPosIndex(NODE *nodeHead, int posIndex){
	int indexCount=0;
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	if((posIndex-1)>listLength(nodeHead)) return -2;
	
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

// 删除节点 / 通过指定数据 ，只删除第一次查询到的 
int delNodeByPosData(NODE *nodeHead, int dataId){
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	tmpNode->next = forNode->next;
	free(forNode);
	
	return 0;
}

// 删除节点 / 通过指定数据 ，删除所有的查询到数据 
int delNodeByPosDataRe(NODE *nodeHead, int dataId){
	int count=0; 
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	NODE *checkNode = forNode;
	if(listIsNull(nodeHead)) return -1;
	
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

// 更新数据 / 通过指定的数据 
int updateNodeByPosData(NODE *nodeHead, int dataId, DATA tmpData){
	NODE *forNode = nodeHead->next, *tmpNode = nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		if(forNode->data.num == dataId) break;
		forNode = forNode->next;
		tmpNode = tmpNode->next;
	}
	
	// update
	forNode->data = tmpData;
	
	return 0;
}

// 更新数据 / 通过指定的下标 
int updataNodeByPosIndex(NODE *nodeHead, int posIndex, DATA tmpData){
	int indexCount=0;
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	if((posIndex-1)>listLength(nodeHead)) return -2;
	
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

// 查询打印节点 / 通过指定的数据 
int searchNodeByPosData(NODE *nodeHead, int dataId){
	NODE *forNode = nodeHead->next;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
//		printf("%p\n", forNode);
		if(forNode->data.num == dataId){
			// print data
			printf("%d|%s|%c|%d|%s|%s|%s",
					forNode->data.num,
					forNode->data.name,
					forNode->data.sex,
					forNode->data.age,
					forNode->data.mobile,
					forNode->data.qq,
					forNode->data.direction);
			return 1; 
		}
		forNode = forNode->next;
	}
	
	printf("[!]未查询到该条记录\n");
	return 0;
}

// 查询打印节点 / 通过指定的下标 
int searchNodeByPosIndex(NODE *nodeHead, int posIndex){
	int indexCount=0;
	NODE *forNode = nodeHead->next, *tmpNode=nodeHead;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		if(indexCount == posIndex) {
			// print data
			printf("%d|%s|%c|%d|%s|%s|%s",
					forNode->data.num,
					forNode->data.name,
					forNode->data.sex,
					forNode->data.age,
					forNode->data.mobile,
					forNode->data.qq,
					forNode->data.direction);
			break;
		}
		indexCount++;
	}
	
	return 0;
}

// 判断 链表为空 
int listIsNull(NODE *nodeHead){
	NODE *forNode = nodeHead->next;
	
	if(forNode == NULL) return 1;
	else return 0;
}

// 统计链表长度 
int listLength(NODE *nodeHead){
	int listLen=0; 
 	NODE *forNode = nodeHead->next;
	
	if(listIsNull(nodeHead)) return listLen;
	
	while(forNode != NULL){
		listLen++;
		forNode = forNode->next;
	}
	
	return listLen;
} 

// 打印节点的所有数据 
// mode:0 打印全部 mode:1 打印前20 
int printList(NODE *nodeHead, int mode){
	NODE *forNode = nodeHead->next;
	int count=0;
	
	if(listIsNull(nodeHead)) return -1;
	
	while(forNode != NULL){
		count++; 
		// print data
		printf("%d|%s|%c|%d|%s|%s|%s",
					forNode->data.num,
					forNode->data.name,
					forNode->data.sex,
					forNode->data.age,
					forNode->data.mobile,
					forNode->data.qq,
					forNode->data.direction);
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

// 固化 数据到hex文件 
int saveListToHexFile(NODE *nodeHead, char *filePath){
	NODE *forNode = nodeHead->next;
	FILE *fp = NULL;
	
	if(listIsNull(nodeHead)) return -1;
	
	fp = openFile(filePath, "wb", 1);
	if(fp==NULL) return -2;
	
	while(forNode != NULL){
		fwrite(&forNode->data, sizeof(DATA), 1, fp);
		fflush(fp); // 释放文件输入缓存   保证结构体的格式完整 正确 
		forNode = forNode->next;
	}
	
	return 0;
} 


// 从文件中载入 数据 构成链表 
int loadListFromHexFile(NODE *nodeHead, char *filePath){
	NODE *forNode = nodeHead->next, *tmpNode=NULL;
	FILE *fp = NULL;
	DATA tmpData;
	
	fp = openFile(filePath, "rb", 0);
	if(fp==NULL) return -2;
	
	do{
		fread(&tmpData, sizeof(DATA), 1, fp);
		insertNodeByEnd(nodeHead, tmpData);
		if(feof(fp)) break;
	}while(1);
	
	// 多读入一个节点 释放掉
	tmpNode = returnFrontEndNode(nodeHead);
	free(tmpNode->next); 
	tmpNode->next = NULL;
	
	return 0;
}

// 返回 最后一个节点 的前一个节点 
NODE *returnFrontEndNode(NODE *nodeHead){
	NODE *forNode = nodeHead; 
	
	if(listIsNull(nodeHead)) return NULL;
	
	while(forNode->next->next != NULL){
		forNode = forNode->next;
	}
	
	return forNode;
}

// 释放链表 
int freeList(NODE *nodeHead){
	NODE *forNode = NULL;
	
	if(listIsNull(nodeHead)) return -1;
	
	do{
		forNode = returnFrontEndNode(nodeHead);
		if(forNode == NULL) break;
		forNode->next = NULL;
		free(forNode);
	}while(1);
	
	return 0;
}

// 链表排序算法（简单选择） 
int listSortFunc(NODE *nodeHead){
	NODE *endP = returnFrontEndNode(nodeHead)->next;
	NODE *moveP = nodeHead->next, *baseP=nodeHead->next, *standP=nodeHead;
	DATA tmpData;
	
	if(listIsNull(nodeHead)) return -1; 
	
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




