#ifndef _GEN_DEF_H_
#define _GEN_DEF_H_

/* 
	filename : gen_def.h (通用头文件)
 	version  : v1.0
 	content  : 定义常用的宏定义、带参宏等 常用定义 
 	author   : 3hex
 	date     : 2020-10-27 
*/ 

// 0.默认参数

// 1.常用类型定义
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef uchar byte;
typedef long double ldouble;

// 2.布尔类型
// ...

// 3.常用强转
#define DOU(x) ((double)(x))
#define FLOAT(x) ((float)(x))
#define INT(x) ((int)(x))
#define UINT(x) ((uint)(x))
#define LONG(x) ((long)(x))
#define ULONG(x) ((ulong)(x))
#define UCHAR(x) ((uchar)(x))
#define BYTE(x) ((byte)(x))

// 4.常用有参宏定义
// func:交换x,y的值 
#define SWAP(x,y) ((x)^=(y),(y)^=(x),(x)^=(y)) 
// func:任何正、负数 转为正数 (支持double) 
#define NUM_TO_POS(x)  (DOU(x)<0.0? DOU(-(x)):DOU((x)))
// func:返回两个数中最大值 (支持double) 
#define NUM_MAX_2(x,y)  (DOU(x)>DOU(y)? DOU((x)):DOU((y)))
// func:返回两个数中最大值 (支持double) 
#define NUM_MIN_2(x,y)  (DOU(x)<DOU(y)? DOU((x)):DOU((y)))
// func:判断两个数是不是相等 (支持double)
#define NUM_EQUAL(x,y) ((NUM_TO_POS((x)-(y))<1E-7)? 1.0:0.0) 

#endif
