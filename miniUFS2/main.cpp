#include "stdio.h"
#include "Global.h"

/*需一次性载入内存的模块*/
char FDBBitmap[FDBNum];//块标记位图

FileIndex *fileIndex;
int TotalFileNum;

int NowDirFid;
int NowDirFileNum;//当前目录文件数量
FileNode *NowDirDirTree;//文件结构树

char NowDirRoute[8*MaxDirDepth];

int DirFidStack[MaxDirDepth];
int DirFidStackTop;

int FirstBlankFDB;//空闲数据块位置标记
int FirstBlankFCB;//空闲控制块位置标记
FILE *fpDisk;//1G空间磁盘位置指针

int IndexSpace;
int IndexSpaceInterval=1000;

int* Deleted;//删除队列
int DeletedNum;
int DeletedSpace;
int DeletedSpaceInterval=100;

int FreeFDBNum;


char Username[10];
char password[10];


bool isEditing;


BOOL   CtrlHandler(DWORD   fdwCtrlType) ;

int main(int argc,char *argv[])
{
	if (argc>1)
	{
		fpDisk=fopen(argv[1],"rb+");
		if (fpDisk==NULL)
		{
			printf("指定文件不存在或无法打开。\n");
			return 0;
		}
	}
	else
	{
		printf("未指定虚拟磁盘文件，使用默认磁盘文件。\n");
		fpDisk=fopen("VirtualDisk.bleg","rb+");
		if (fpDisk==NULL)
		{
			printf("指定文件不存在。\n");
			return 0;
		}
	}

	BOOL   fSuccess;   

	fSuccess   =   SetConsoleCtrlHandler((PHANDLER_ROUTINE)  CtrlHandler,TRUE);
	if   (!fSuccess)  {
		printf("Could   not   set   control   handler.\n");
		exit(0);
	}

	fseek(fpDisk,0,0);
	char flag[5];
	memset(flag,0,5);
	fread(flag,1,4,fpDisk);
	if (lstrcmpiA(flag,"u-fs"))
	{
		printf("该文件不是mini-Ufs的有效文件。\n");
		exit(0);
	}

	Login();
	
	InitOnStart();

	char command[100];
	while(true)
	{
		printf("%s@miniUfs:%s> ",Username,NowDirRoute);
		gets(command);
		ParseCmd(command);
	}
}


BOOL   CtrlHandler(DWORD   fdwCtrlType)   
{   
	switch   (fdwCtrlType)   
	{
		case   CTRL_C_EVENT:   
			//Beep(1000,   1000);   
			return   TRUE;  
		case   CTRL_CLOSE_EVENT:   
			if (isEditing)
			{
				Beep(1000,600);
				printf("非正常关闭系统，正在编辑的数据可能会丢失。\n");
				printf("%s@miniUfs:%s> close",Username,NowDirRoute);
				Close();
				int i=800000000;
				while(i--)
				{
				}
			}
			else
			{
				printf("close\n");
				Close();
			}
			return   TRUE;    
		case   CTRL_BREAK_EVENT:   
		case   CTRL_LOGOFF_EVENT:   
		case   CTRL_SHUTDOWN_EVENT:   
		default:   
		return   FALSE;   
	}   
}   