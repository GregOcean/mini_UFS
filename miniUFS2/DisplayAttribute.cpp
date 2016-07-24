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
			printf("\n创建时间  		      文件大小	   文件名称		   权限\n");
			DisplayCrtTime(fn);
			NumberWithComma(fn->filesize);
			printf("%8s",fn->filename);
			printf(".%s        ",fn->extention);
			if (fn->IfCanRead==1 &&fn->IfCanWrite==1)
			{
				printf("    可读可写\n");				
			}
			else if (fn->IfCanRead==1 && fn->IfCanWrite==0)
			{
				printf  ("      只可读\n");
			}
			else if (fn->IfCanRead==0 &&fn->IfCanWrite==1)
			{
				printf("      只可写\n");
			}
			else
			{
				printf("不可读不可写\n");
			}
		}
		else
			printf("文件不存在或删除\n");
	}
	else if (mode==2)
	{
		
		int Fid=GetDirID(1,filename);
		FileNode *Fn=fileIndex[Fid].node;
		int FolderTotalSize=0;
		int fnum=0,Fnum=0;
		if (Fid!=-1&&Fn->IfDelete==0)
		{	
			printf("\n创建时间                    文件夹大小     包含文件     包含文件夹         属性\n");
			
			DisplayCrtTime(Fn);
			DirSizeRCS(Fn,&FolderTotalSize,&fnum,&Fnum);
			NumberWithComma(FolderTotalSize);
			printf("           %d              %d",fnum,Fnum);

			if (Fn->IfCanRead==1 &&Fn->IfCanWrite==1)
			{
				printf("     可读可写\n");
			}
			else if (Fn->IfCanRead==1 && Fn->IfCanWrite==0)
			{
				printf("       只可读\n");
			}
			else if (Fn->IfCanRead==0 &&Fn->IfCanWrite==1)
			{
				printf("       只可写\n");
			}
			else
			{
				printf(" 不可读不可写\n");
			}
		}
		else
			printf("文件不存在或删除\n");
	}
	else
		printf("Command Error\n");
}