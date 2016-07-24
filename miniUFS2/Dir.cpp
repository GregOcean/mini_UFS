#include "Global.h"
#include "stdlib.h"
#include "string.h"
#define PCRE_STATIC // ��̬�����ѡ��         
#include "pcre.h"      
#define OVECCOUNT 30 /* should be a multiple of 3 */      
#define EBUFLEN 128      
#define BUFLEN 1024      
#pragma  comment (lib,"pcre.lib")   

void DisplayCrtTime(FileNode* fn)
{

	int p;
	for ( p=0;p<4;p++)//��ʾ��
	{
		printf("%c",fn->createtime[p]+'0');
	}
	printf("/");
	for ( p=4;p<6;p++)//��ʾ��
	{
		printf("%c",fn->createtime[p]+'0');
	}
	printf("/");
	for ( p=6;p<8;p++)//��ʾ��
	{
		printf("%c",fn->createtime[p]+'0');
	}
	printf("  ");

	for ( p=8;p<10;p++)//��ʾʱ
	{
		printf("%c",fn->createtime[p]+'0');
	}
	printf(":");
	for ( p=10;p<12;p++)//��ʾ��
	{
		printf("%c",fn->createtime[p]+'0');
	}
	printf(":");
	for ( p=12;p<14;p++)//��ʾ��
	{
		printf("%c",fn->createtime[p]+'0');
	}
	printf("    ");
}
 void NumberWithComma(int OriNum)
 {
	 int tmp=OriNum;
	 char ctemp[15];
	 itoa(OriNum,ctemp,10);//intתchar
	 int NumLength=strlen(ctemp);//���ֳ���
	 int RealNumLen=0;//�Ӷ��ź����ֳ���
	 RealNumLen+=NumLength+(NumLength-1)/3;
	 int i=0,pout=0;
	 for (i=0;i<14;i++)
	 {
		 if (i<14-RealNumLen)
		 {
			 printf(" ");
		 }
		 else if ((i+2)%4!=0)
		 {
			 printf("%c",ctemp[pout]);
			 pout++;
		 }
		 else
		 {
			 printf(",");
		 }
	 }
	 printf(" ");
 }
int cmp(const void *a,const void *b)//���ļ�������һ������
{
	struct FileNode *c=(struct FileNode *)a;
	struct FileNode *d=(struct FileNode *)b;
	if (lstrcmpiA(c->filename,d->filename)>0)
	{
		return 1;
	}
	else return -1;
}

void Dir(char *filename,char *extention)
{
	if (filename==NULL)
	{
		FileNode fn;
		int TotalBytes=0;
		int ActualBytes=0;
		int j=0;
		int i=0;
		qsort(NowDirDirTree,NowDirFileNum,sizeof(NowDirDirTree[0]),cmp);

		if (NowDirFid!=1)
		{
			DisplayCrtTime(fileIndex[NowDirFid].node);
			printf("<DIR>          .\n");
			DisplayCrtTime(fileIndex[NowDirFid].node);
			printf("<DIR>          ..\n");
		}
		int NumOfFolder=0;
		for (i=0;i<NowDirFileNum;i++)
		{
			fn=NowDirDirTree[i];
			DisplayCrtTime(&fn);

			if (fn.type==t_Folder)//���ļ��еĻ���ʾ<DIR>
			{
				printf("<DIR>          ");//��10��
				printf("%8s",fn.filename);
				NumOfFolder++;
			}

			if (fn.type==t_File)//���ļ��Ļ�
			{
				NumberWithComma(fn.filesize);
				//FileNum++;
				//TotalBytes+=fn.filesize;
				printf("%8s",fn.filename);
				printf(".%s",fn.extention);
				ActualBytes+=fn.filesize;
				TotalBytes+=4096*((fn.filesize+4095)/4096);
			}

			printf("\n");

			//printf("%16 Directories",DirNum);
		}
		//printf("Directory contains %8d Files.\n",NowDirFileNum);
		//printf("Using space : %8d Bytes\n",TotalBytes);
		//printf("File Size : %d Bytes\n",ActualBytes);
		printf("%16d ���ļ�%16d �ֽ�%16d ռ���ֽ�\n",NowDirFileNum-NumOfFolder,ActualBytes,TotalBytes);
		printf("%16d ��Ŀ¼%16d �����ֽ�\n",NumOfFolder,FreeFDBNum*4096);
	}

	else
	{
		FileNode fn;
		pcre  *re1; 
		pcre  *re2;  
		const char *error;     
		int  erroffset;     
		int  ovector1[OVECCOUNT],ovector2[OVECCOUNT];     
		int  rc1, rc2;     
		char  srcfilename[1000];   
		char  srcextention[1000];  
		char  pattern1[1000];   
		char  pattern2[1000]; 
		qsort(NowDirDirTree,NowDirFileNum,sizeof(NowDirDirTree[0]),cmp);
		int i;
		for (i=0;i<NowDirFileNum;i++)
		{
			fn=NowDirDirTree[i];
			//DisplayCrtTime(&fn);

			if (fn.type==t_File)
			{
				memset(ovector1,0,sizeof(ovector1));
				memset(ovector2,0,sizeof(ovector2));

				strcpy(srcfilename,fn.filename);
				strcpy(pattern1,filename);
				strcpy(srcextention,fn.extention);
				strcpy(pattern2,extention);

				re1 = pcre_compile(pattern1,       
					0,         
					&error,       
					&erroffset,  
					NULL);      			    
				rc1 = pcre_exec(re1,              
					NULL,           
					srcfilename,           
					strlen(srcfilename),       
					0,              
					0,            
					ovector1,      
					OVECCOUNT);   

				re2 = pcre_compile(pattern2,       
					0,         
					&error,       
					&erroffset,  
					NULL);      
				rc2 = pcre_exec(re2,              
					NULL,           
					srcextention,           
					strlen(srcextention),       
					0,              
					0,            
					ovector2,      
					OVECCOUNT); 
				int substring_length1 = ovector1[2*0+1] - ovector1[2*0]; 
				int substring_length2 = ovector2[2*0+1] - ovector2[2*0]; 
				if (rc1 >= 0 && rc2>=0 &&strlen(fn.filename)==substring_length1 && strlen(fn.extention)==substring_length2) {                      
					DisplayCrtTime(&fn);
					NumberWithComma(fn.filesize);
					printf("%8s",fn.filename);
					printf(".%s",fn.extention);
					printf("\n");
				}     

			}

			
		}
	}

	
}