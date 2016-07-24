#include "Global.h"
#include "string.h"
bool rename(int mode,int fid,char *filename,char *extention)
{
	if (mode==1)
	{
		//判断有无重命名情况。
		char c;
		char d[3]={"_2"};
		FileNode *fn=fileIndex[fid].node;
		int fiddest=GetFileID(filename,extention);
		if(fiddest!=-1)   //表示新命名的文件有重名的。
		{
			printf("此文件名已存在,是否改名为%s_2.%s\n",filename,extention);
			printf("请输入你的选择yes(y),no(n)     ");
			c=getchar();
			if(c=='n')
			{
				printf("重命名失败\n");
				getchar();    //读走换行。
				return false;
			}
			else if(c=='y')
			{
				strcpy(fn->filename,filename);
				strcat(fn->filename,d);
				strcpy(fn->extention,extention);
				getchar();
				ChangeAttribute(1,fid);
			}
		}
		else  //没有重命的文件。
		{
			strcpy(fn->filename,filename);
			strcpy(fn->extention,extention);
			ChangeAttribute(1,fid);
			return true;
		}
	}
	else
	{
		//判断有无重命名情况。
		char c;
		char d[3]={"_2"};
		FileNode *fn=fileIndex[fid].node;
		int fiddest=GetDirID(1,filename);
		if(fiddest!=-1)   //表示新命名的文件有重名的。
		{
			printf("此文件夹名已存在,是否改名为%s_2\n",filename);
			printf("请输入你的选择yes(y),no(n)     ");
			c=getchar();
			if(c=='n')
			{
				printf("重命名失败\n");
				getchar();    //读走换行。
				return false;
			}
			else if(c=='y')
			{
				strcpy(fn->filename,filename);
				strcat(fn->filename,d);
				getchar();
				ChangeAttribute(2,fid);
			}
		}
		else  //没有重命的文件。
		{
			strcpy(fn->filename,filename);
			ChangeAttribute(2,fid);
			return true;
		}
	}
	return true;
}