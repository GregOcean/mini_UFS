#include "stdio.h"
#include "Global.h"

/*��һ���������ڴ��ģ��*/
char FDBBitmap[FDBNum];//����λͼ

FileIndex *fileIndex;
int TotalFileNum;

int NowDirFid;
int NowDirFileNum;//��ǰĿ¼�ļ�����
FileNode *NowDirDirTree;//�ļ��ṹ��

char NowDirRoute[8*MaxDirDepth];

int DirFidStack[MaxDirDepth];
int DirFidStackTop;

int FirstBlankFDB;//�������ݿ�λ�ñ��
int FirstBlankFCB;//���п��ƿ�λ�ñ��
FILE *fpDisk;//1G�ռ����λ��ָ��

int IndexSpace;
int IndexSpaceInterval=1000;

int* Deleted;//ɾ������
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
			printf("ָ���ļ������ڻ��޷��򿪡�\n");
			return 0;
		}
	}
	else
	{
		printf("δָ����������ļ���ʹ��Ĭ�ϴ����ļ���\n");
		fpDisk=fopen("VirtualDisk.bleg","rb+");
		if (fpDisk==NULL)
		{
			printf("ָ���ļ������ڡ�\n");
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
		printf("���ļ�����mini-Ufs����Ч�ļ���\n");
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
				printf("�������ر�ϵͳ�����ڱ༭�����ݿ��ܻᶪʧ��\n");
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