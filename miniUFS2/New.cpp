#include "Global.h"
#include"string.h"
#include"time.h"
#include"stdlib.h"
bool New(int mode,char *filename,char *extention)
{
	if (mode==1)
	{
		//�ж��ļ��Ƿ��Ѿ���������
		int fid,temp;    //flag�ж��Ƿ����½��ļ���temp��ʱ���ʱ�������
		struct tm *nowtime;
		time_t tmp;
		char input=0;

		if (strlen(filename)>8)
		{
			printf("�ļ�������.\n");
			return false;
		}
		if (strlen(extention)>3)
		{
			printf("��չ��������\n");
			return false;
		}

		fid=GetFileID(filename,extention);
		
		if(fid!=-1)
		{
			printf("�ļ��Ѵ��ڣ��Ƿ��滻?\n",filename,extention);
			printf("yes(y),no(n)��  ");
			input=getchar();
			while(input=='\n')
			{
				input=getchar();
			}
			getchar();
		}
		if(fid==-1||input=='y')							//֤���ļ�δ������input����"1"��ʾ�滻
		{
			if(input=='y'&&fid!=-1)  
			{
				
				Delete(1,filename,extention);
				ChangeNowDir(NowDirRoute);
			}
			//�ļ�������չ���Ĵ�����
			TotalFileNum++;
			fid=TotalFileNum;
			strcpy(fileIndex[fid].filename,filename);
			strcpy(fileIndex[fid].extention,extention);
			FileIndex *FI=&fileIndex[fid];
			FI->type=t_File;
			FI->node=(FileNode*)malloc(sizeof(FileNode));
			FileNode *fn=FI->node;

			strcpy(fn->filename,filename);
			strcpy(fn->extention,extention);
			//ϵͳʱ��Ļ�ȡ��
			time(&tmp);
			nowtime=localtime(&tmp);
			temp=nowtime->tm_year+1900;
			for(int i=0;i<4;i++)  //���껻���char��
			{
				fn->createtime[3-i]=temp%10;
				temp=temp/10;
			}
			//�£��գ�ʱ���֣�����㡣	
			nowtime->tm_mon=nowtime->tm_mon+1;
			fn->createtime[4]=(int)(nowtime->tm_mon/10);
			fn->createtime[5]=nowtime->tm_mon%10;
			fn->createtime[6]=(int)(nowtime->tm_mday/10);
			fn->createtime[7]=nowtime->tm_mday%10;
			fn->createtime[8]=(int)(nowtime->tm_hour/10);
			fn->createtime[9]=nowtime->tm_hour%10;
			fn->createtime[10]=(int)(nowtime->tm_min/10);
			fn->createtime[11]=nowtime->tm_min%10;
			fn->createtime[12]=(int)(nowtime->tm_sec/10);
			fn->createtime[13]=nowtime->tm_sec%10;
			//��ʼ��lasttime�봴��ʱ����ͬ��
			for(int i=0;i<14;i++)
				fn->lastedittime[i]=fn->createtime[i];
			//��ʼ�����ݿ�λ��Ϊ0��
			fn->FDBBlock=0;
			//��ʼ��rightnode
			//NowDirDirTree[NowDirFileNum].rightnode=0;
			//��ʼ�����ļ��ɶ���д
			fn->IfDelete=0;
			fn->IfCanRead=1;
			fn->IfCanWrite=1;
			//�ļ���С��ʼ��Ϊ0��
			fn->filesize=0;
			//���ƿ��λ�á�
			fn->FCBBlock=FirstBlankFCB;
			FirstBlankFCB++;
			fn->type=t_File;
			fn->fatherFid=NowDirFid;
			fn->fid=fid;
			//д�����ƿ���
			ChangeAttribute(1,fid);

			FI=&fileIndex[NowDirFid];
			fn=FI->node;
			fn->SonNum++;
			fn->childnode[fn->SonNum-1]=fid;

			ChangeAttribute(2,NowDirFid);
			ChangeNowDirFid(NowDirFid);



			//�ж������Ƿ��á�
			if(NowDirFileNum==IndexSpace)
			{
				//���������С��
				IndexSpace=IndexSpace+IndexSpaceInterval;
				NowDirDirTree=(FileNode *)realloc(NowDirDirTree,IndexSpace*sizeof(FileNode));
			}
			return true;
		}
	}
	else{
		//�ж��ļ��Ƿ��Ѿ���������
		int fid,temp;    //flag�ж��Ƿ����½��ļ���temp��ʱ���ʱ�������
		struct tm *nowtime;
		time_t tmp;
		char input=0;
		if (strlen(filename)>8)
		{
			printf("�ļ�������.\n");
			return false;
		}
		fid=GetDirID(1,filename);

		if(fid!=-1)
		{
			printf("Ŀ¼�Ѵ��ڣ��Ƿ��滻?\n",filename);
			printf("yes(y),no(n)��  ");
			input=getchar();
			while(input=='\n')
			{
				input=getchar();
			}
			getchar();
		}
		if(fid==-1||input=='y')							//֤���ļ�δ������input����"1"��ʾ�滻
		{
			if(input=='y'&&fid!=-1)  
			{
				//
				
				Delete(2,NowDirDirTree[fid].filename,NowDirDirTree[fid].extention);
			}
			//�ļ�������չ���Ĵ�����
			TotalFileNum++;
			fid=TotalFileNum;
			strcpy(fileIndex[fid].filename,filename);
			FileIndex *FI=&fileIndex[fid];
			FI->type=t_Folder;
			FI->node=(FileNode*)malloc(sizeof(FileNode));
			FileNode *fn=FI->node;

			strcpy(fn->filename,filename);
			//ϵͳʱ��Ļ�ȡ��
			time(&tmp);
			nowtime=localtime(&tmp);
			temp=nowtime->tm_year+1900;
			for(int i=0;i<4;i++)  //���껻���char��
			{
				fn->createtime[3-i]=temp%10;
				temp=temp/10;
			}
			//�£��գ�ʱ���֣�����㡣	
			nowtime->tm_mon=nowtime->tm_mon+1;
			fn->createtime[4]=(int)(nowtime->tm_mon/10);
			fn->createtime[5]=nowtime->tm_mon%10;
			fn->createtime[6]=(int)(nowtime->tm_mday/10);
			fn->createtime[7]=nowtime->tm_mday%10;
			fn->createtime[8]=(int)(nowtime->tm_hour/10);
			fn->createtime[9]=nowtime->tm_hour%10;
			fn->createtime[10]=(int)(nowtime->tm_min/10);
			fn->createtime[11]=nowtime->tm_min%10;
			fn->createtime[12]=(int)(nowtime->tm_sec/10);
			fn->createtime[13]=nowtime->tm_sec%10;
			//��ʼ�����ݿ�λ��Ϊ0��
			fn->FDBBlock=FirstBlankFDB+FCBRemainNum+3;
			FDBBitmap[FirstBlankFDB]=b_Full;
			int nextFDB=GetNextBlankFDB();
			FirstBlankFDB=nextFDB;

			//��ʼ�����ļ��ɶ���д
			fn->IfDelete=0;
			fn->IfCanRead=1;
			fn->IfCanWrite=1;

			fn->SonNum=0;
			fn->childnode=(int*)malloc(1000*4);
			//���ƿ��λ�á�
			fn->FCBBlock=FirstBlankFCB;
			FirstBlankFCB++;

			fn->type=t_Folder;
			fn->fatherFid=NowDirFid;
			fn->fid=fid;
			//д�����ƿ���
			ChangeAttribute(2,fid);

			FI=&fileIndex[NowDirFid];
			fn=FI->node;
			fn->SonNum++;
			fn->childnode[fn->SonNum-1]=fid;

			ChangeAttribute(2,NowDirFid);
			ChangeNowDirFid(NowDirFid);



			//�ж������Ƿ��á�
			if(NowDirFileNum==IndexSpace)
			{
				//���������С��
				IndexSpace=IndexSpace+IndexSpaceInterval;
				NowDirDirTree=(FileNode *)realloc(NowDirDirTree,IndexSpace*sizeof(FileNode));
			}
			return true;
		}
	}
	return false;
} 