#include "Global.h"
#include"string.h"
#include"time.h"
#include"stdlib.h"
bool New(int mode,char *filename,char *extention)
{
	if (mode==1)
	{
		//判断文件是否已经建立过。
		int fid,temp;    //flag判断是否是新建文件。temp临时存放时间变量。
		struct tm *nowtime;
		time_t tmp;
		char input=0;

		if (strlen(filename)>8)
		{
			printf("文件名过长.\n");
			return false;
		}
		if (strlen(extention)>3)
		{
			printf("扩展名过长。\n");
			return false;
		}

		fid=GetFileID(filename,extention);
		
		if(fid!=-1)
		{
			printf("文件已存在，是否替换?\n",filename,extention);
			printf("yes(y),no(n)：  ");
			input=getchar();
			while(input=='\n')
			{
				input=getchar();
			}
			getchar();
		}
		if(fid==-1||input=='y')							//证明文件未重名。input等于"1"表示替换
		{
			if(input=='y'&&fid!=-1)  
			{
				
				Delete(1,filename,extention);
				ChangeNowDir(NowDirRoute);
			}
			//文件名，扩展名的创建。
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
			//系统时间的获取。
			time(&tmp);
			nowtime=localtime(&tmp);
			temp=nowtime->tm_year+1900;
			for(int i=0;i<4;i++)  //把年换算成char型
			{
				fn->createtime[3-i]=temp%10;
				temp=temp/10;
			}
			//月，日，时，分，秒计算。	
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
			//初始化lasttime与创建时间相同。
			for(int i=0;i<14;i++)
				fn->lastedittime[i]=fn->createtime[i];
			//初始化数据块位置为0。
			fn->FDBBlock=0;
			//初始化rightnode
			//NowDirDirTree[NowDirFileNum].rightnode=0;
			//初始创建文件可读可写
			fn->IfDelete=0;
			fn->IfCanRead=1;
			fn->IfCanWrite=1;
			//文件大小初始化为0；
			fn->filesize=0;
			//控制块的位置。
			fn->FCBBlock=FirstBlankFCB;
			FirstBlankFCB++;
			fn->type=t_File;
			fn->fatherFid=NowDirFid;
			fn->fid=fid;
			//写到控制块内
			ChangeAttribute(1,fid);

			FI=&fileIndex[NowDirFid];
			fn=FI->node;
			fn->SonNum++;
			fn->childnode[fn->SonNum-1]=fid;

			ChangeAttribute(2,NowDirFid);
			ChangeNowDirFid(NowDirFid);



			//判断数组是否够用。
			if(NowDirFileNum==IndexSpace)
			{
				//扩充数组大小。
				IndexSpace=IndexSpace+IndexSpaceInterval;
				NowDirDirTree=(FileNode *)realloc(NowDirDirTree,IndexSpace*sizeof(FileNode));
			}
			return true;
		}
	}
	else{
		//判断文件是否已经建立过。
		int fid,temp;    //flag判断是否是新建文件。temp临时存放时间变量。
		struct tm *nowtime;
		time_t tmp;
		char input=0;
		if (strlen(filename)>8)
		{
			printf("文件名过长.\n");
			return false;
		}
		fid=GetDirID(1,filename);

		if(fid!=-1)
		{
			printf("目录已存在，是否替换?\n",filename);
			printf("yes(y),no(n)：  ");
			input=getchar();
			while(input=='\n')
			{
				input=getchar();
			}
			getchar();
		}
		if(fid==-1||input=='y')							//证明文件未重名。input等于"1"表示替换
		{
			if(input=='y'&&fid!=-1)  
			{
				//
				
				Delete(2,NowDirDirTree[fid].filename,NowDirDirTree[fid].extention);
			}
			//文件名，扩展名的创建。
			TotalFileNum++;
			fid=TotalFileNum;
			strcpy(fileIndex[fid].filename,filename);
			FileIndex *FI=&fileIndex[fid];
			FI->type=t_Folder;
			FI->node=(FileNode*)malloc(sizeof(FileNode));
			FileNode *fn=FI->node;

			strcpy(fn->filename,filename);
			//系统时间的获取。
			time(&tmp);
			nowtime=localtime(&tmp);
			temp=nowtime->tm_year+1900;
			for(int i=0;i<4;i++)  //把年换算成char型
			{
				fn->createtime[3-i]=temp%10;
				temp=temp/10;
			}
			//月，日，时，分，秒计算。	
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
			//初始化数据块位置为0。
			fn->FDBBlock=FirstBlankFDB+FCBRemainNum+3;
			FDBBitmap[FirstBlankFDB]=b_Full;
			int nextFDB=GetNextBlankFDB();
			FirstBlankFDB=nextFDB;

			//初始创建文件可读可写
			fn->IfDelete=0;
			fn->IfCanRead=1;
			fn->IfCanWrite=1;

			fn->SonNum=0;
			fn->childnode=(int*)malloc(1000*4);
			//控制块的位置。
			fn->FCBBlock=FirstBlankFCB;
			FirstBlankFCB++;

			fn->type=t_Folder;
			fn->fatherFid=NowDirFid;
			fn->fid=fid;
			//写到控制块内
			ChangeAttribute(2,fid);

			FI=&fileIndex[NowDirFid];
			fn=FI->node;
			fn->SonNum++;
			fn->childnode[fn->SonNum-1]=fid;

			ChangeAttribute(2,NowDirFid);
			ChangeNowDirFid(NowDirFid);



			//判断数组是否够用。
			if(NowDirFileNum==IndexSpace)
			{
				//扩充数组大小。
				IndexSpace=IndexSpace+IndexSpaceInterval;
				NowDirDirTree=(FileNode *)realloc(NowDirDirTree,IndexSpace*sizeof(FileNode));
			}
			return true;
		}
	}
	return false;
} 