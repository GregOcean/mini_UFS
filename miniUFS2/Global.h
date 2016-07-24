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

#define b_Free 0//��δʹ��
#define b_Full 1//����ʹ��
#define b_Del  2//����ɾ��

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


/*��һ���������ڴ��ģ��*/
extern char FDBBitmap[FDBNum];//����λͼ
extern FileNode *NowDirDirTree;//�ļ��ṹ��
extern int NowDirFileNum;//�ļ�����
extern int FirstBlankFDB;//�������ݿ�λ�ñ��
extern int FirstBlankFCB;//���п��ƿ�λ�ñ��
extern FILE *fpDisk;//1G�ռ����λ��ָ��

extern int IndexSpace;
extern int IndexSpaceInterval;

extern int* Deleted;//ɾ������
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