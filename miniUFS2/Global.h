#pragma once
#pragma warning (disable:4996)

//#define _1M_
#define _1G_

#include "stdio.h"
#include "string.h"

#include "Function.h"
#include "Structure.h"
#include "windows.h"
#include "conio.h"

#define b_Free 0//块未使用
#define b_Full 1//块已使用
#define b_Del  2//块已删除

#define t_File 0
#define t_Folder 1

#ifdef _1G_
	#define FDBNum 261352
	#define FCBRemainNum 100000

#endif

// #ifdef _1M_
// 	#define FDBNum 255
// 	#define FCBRemainNum 32
// #endif

#define BlockSize 4096

#define MaxDirDepth 200


/*需一次性载入内存的模块*/
extern char FDBBitmap[FDBNum];//块标记位图
extern FileNode *NowDirDirTree;//文件结构树
extern int NowDirFileNum;//文件数量
extern int FirstBlankFDB;//空闲数据块位置标记
extern int FirstBlankFCB;//空闲控制块位置标记
extern FILE *fpDisk;//1G空间磁盘位置指针

extern int IndexSpace;
extern int IndexSpaceInterval;

extern int* Deleted;//删除队列
extern int DeletedNum;
extern int DeletedSpace;
extern int DeletedSpaceInterval;

extern char Username[10];
extern char password[10];

extern int FreeFDBNum;

extern bool isEditing;

extern char *operateList[100];


extern int TotalFileNum;
extern int NowDirFid;
extern FileIndex* fileIndex;

extern char NowDirRoute[8*MaxDirDepth];


// extern int DirFidStack[MaxDirDepth];
//extern int DirFidStackTop;