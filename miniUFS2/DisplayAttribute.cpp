#include "Global.h"
#include "stdio.h"
void NumberWithComma(int OriNum);

void DirSizeRCS(FileNode *Fn,int *TotalSize,int *fnum,int *Fnum)
{
	FileNode *tmp;
	int fileid;
	
	for(int i=0;i<Fn->SonNum;i++)
	{
		fileid=Fn->childnode[i];
		tmp=fileIndex[fileid].node;
		if (tmp->type==t_File)
		{
			(*TotalSize)+=tmp->filesize;
			(*fnum)++;
		}
		else if (tmp->type==t_Folder)
		{
			(*Fnum)++;
			DirSizeRCS(tmp,TotalSize,fnum,Fnum);
		}
	}
}
void DisplayAttribute(int mode,char *filename,char *extention)
{
	if(mode==1)
	{
		int fid=GetFileID(filename,extention);
		FileNode*fn=fileIndex[fid].node;

		if (fid!=-1&&fn->IfDelete==0)
		{
			printf("\n����ʱ��  		      �ļ���С	   �ļ�����		   Ȩ��\n");
			DisplayCrtTime(fn);
			NumberWithComma(fn->filesize);
			printf("%8s",fn->filename);
			printf(".%s        ",fn->extention);
			if (fn->IfCanRead==1 &&fn->IfCanWrite==1)
			{
				printf("    �ɶ���д\n");				
			}
			else if (fn->IfCanRead==1 && fn->IfCanWrite==0)
			{
				printf  ("      ֻ�ɶ�\n");
			}
			else if (fn->IfCanRead==0 &&fn->IfCanWrite==1)
			{
				printf("      ֻ��д\n");
			}
			else
			{
				printf("���ɶ�����д\n");
			}
		}
		else
			printf("�ļ������ڻ�ɾ��\n");
	}
	else if (mode==2)
	{
		
		int Fid=GetDirID(1,filename);
		FileNode *Fn=fileIndex[Fid].node;
		int FolderTotalSize=0;
		int fnum=0,Fnum=0;
		if (Fid!=-1&&Fn->IfDelete==0)
		{	
			printf("\n����ʱ��                    �ļ��д�С     �����ļ�     �����ļ���         ����\n");
			
			DisplayCrtTime(Fn);
			DirSizeRCS(Fn,&FolderTotalSize,&fnum,&Fnum);
			NumberWithComma(FolderTotalSize);
			printf("           %d              %d",fnum,Fnum);

			if (Fn->IfCanRead==1 &&Fn->IfCanWrite==1)
			{
				printf("     �ɶ���д\n");
			}
			else if (Fn->IfCanRead==1 && Fn->IfCanWrite==0)
			{
				printf("       ֻ�ɶ�\n");
			}
			else if (Fn->IfCanRead==0 &&Fn->IfCanWrite==1)
			{
				printf("       ֻ��д\n");
			}
			else
			{
				printf(" ���ɶ�����д\n");
			}
		}
		else
			printf("�ļ������ڻ�ɾ��\n");
	}
	else
		printf("Command Error\n");
}