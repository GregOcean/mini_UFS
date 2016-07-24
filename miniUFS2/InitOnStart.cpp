#include "Global.h"
#include "stdlib.h"
#include "stdio.h"

void InitOnStart()
{
	isEditing=false;
	//读取系统块三个数据
	fseek(fpDisk,0,0);
	char flag[5];
	memset(flag,0,5);
	fread(flag,1,4,fpDisk);
	if (lstrcmpiA(flag,"u-fs"))
	{
		printf("该文件不是mini-Ufs的有效文件。\n");
		exit(0);
	}
	fread(&TotalFileNum,4,1,fpDisk);
	fread(&FirstBlankFDB,4,1,fpDisk);
	fread(&FirstBlankFCB,4,1,fpDisk);

	//读取控制块
	fseek(fpDisk,1024,0);

	IndexSpace=TotalFileNum*3>1000?TotalFileNum:1000;
	IndexSpace=IndexSpace<FCBRemainNum?IndexSpace:FCBRemainNum;

	fileIndex=(FileIndex*)malloc(IndexSpace*sizeof(FileNode));
	memset(fileIndex,0,sizeof(fileIndex));

	BuildFileTree(2,1,1);

	DeletedNum=0;
	DeletedSpace=100;

	Deleted=(int*)malloc(DeletedSpace*sizeof(int));

	int add=AddressOfBlock(2+FCBRemainNum);
	fseek(fpDisk,add,0);
	memset(FDBBitmap,0,sizeof(FDBBitmap));
	FreeFDBNum=0;
	for(int i=0;i<FDBNum/8;i++)
	{
		char tmp;
		tmp=0;
		fread(&tmp,1,1,fpDisk);
		for (int j=0;j<8;j++)
		{
			bool ifFree=(tmp&(0x01<<(7-j)))>0;
			FDBBitmap[8*i+j]=ifFree;
			if (!ifFree)
			{
				FreeFDBNum++;
			}
		}

	}
	//NowDirFid=1;
	//NowDirDirTree
	ChangeNowDirFid(1);
	memset(NowDirRoute,0,sizeof(NowDirRoute));

	strcpy(NowDirRoute,"~");
	

}


int BuildFileTree(int rootFCB,int fid,int fatherFid)
{
	int add=AddressOfBlock(rootFCB);
	char filename[9],extention[4];
	memset(filename,0,9);
	memset(extention,0,4);
	fseek(fpDisk,add,0);
	fread(filename,1,8,fpDisk);
	fread(extention,1,3,fpDisk);
	
	char type;
	fread(&type,1,1,fpDisk);

	char symbol;
	fread(&symbol,1,1,fpDisk);
	char IfDeleted=(symbol&0x80)!=0;
	char IfCanRead=(symbol&0x40)!=0;
	char IfCanWrite=(symbol&0x20)!=0;

	if (IfDeleted!=0)
	{
		return fid;
	}

	if (type==t_File)
	{
		FileIndex FI;
		memset(&FI,0,sizeof(FI));
		strcpy(FI.filename,filename);
		strcpy(FI.extention,extention);
		FI.type=type;
		FI.node=(FileNode*)malloc(sizeof(FileNode));

		FileNode *fn=FI.node;
		fn->fid=fid;
		strcpy(fn->filename,filename);
		strcpy(fn->extention,extention);
		fn->FCBBlock=rootFCB;
		fn->IfDelete=0;
		fn->IfCanRead=IfCanRead;
		fn->IfCanWrite=IfCanWrite;

		fread(&fn->filesize,4,1,fpDisk);

		//创建时间
		int time;
		fread(&time,4,1,fpDisk);
		int second=time&0x1F;//00011111
		int minute=(time>>5)&0x3f;//00111111
		int hour=(time>>11)&0x1f;//00011111

		time=time>>16;

		int day=time&0x1f;
		int month=(time>>5)&0x0f;
		int year=((time>>9)&0x7f)+2000;

		fn->createtime[12]=second/10;
		fn->createtime[13]=second%10;
		fn->createtime[10]=minute/10;
		fn->createtime[11]=minute%10;
		fn->createtime[ 8]=hour/10;
		fn->createtime[ 9]=hour%10;
		fn->createtime[ 6]=day/10;
		fn->createtime[ 7]=day%10;
		fn->createtime[ 4]=month/10;
		fn->createtime[ 5]=month%10;
		fn->createtime[ 0]=year/1000;
		fn->createtime[ 1]=year%1000/100;
		fn->createtime[ 2]=year%100/10;
		fn->createtime[ 3]=year%10;



		//修改时间
		int time2;
		fread(&time2,4,1,fpDisk);
		int second2=time2&0x1f;
		int minute2=(time2>>5)&0x3f;
		int hour2=(time2>>11)&0x1f;

		time2=time2>>16;

		int day2=time2&0x1f;
		int month2=(time2>>5)&0x0f;
		int year2=((time2>>9)&0x7f)+2000;

		fn->lastedittime[12]=second2/10;
		fn->lastedittime[13]=second2%10;
		fn->lastedittime[10]=minute2/10;
		fn->lastedittime[11]=minute2%10;
		fn->lastedittime[ 8]=hour2/10;
		fn->lastedittime[ 9]=hour2%10;
		fn->lastedittime[ 6]=day2/10;
		fn->lastedittime[ 7]=day2%10;
		fn->lastedittime[ 4]=month2/10;
		fn->lastedittime[ 5]=month2%10;
		fn->lastedittime[ 0]=year2/1000;
		fn->lastedittime[ 1]=year2%1000/100;
		fn->lastedittime[ 2]=year2%100/10;
		fn->lastedittime[ 3]=year2%10;

		//首簇号
		char ThreeBytes[3];
		fread(ThreeBytes,1,3,fpDisk);

		fn->FDBBlock=ThreeToInt(ThreeBytes);

		fn->type=type;
		fn->fatherFid=fatherFid;

		fileIndex[fid]=FI;
		fid++;
		return fid;
	}

	else
	{
		FileIndex FI;
		memset(&FI,0,sizeof(FI));
		strcpy(FI.filename,filename);
		FI.type=type;
		FI.node=(FileNode*)malloc(sizeof(FileNode));

		FileNode *fn=FI.node;
		fn->fid=fid;
		strcpy(fn->filename,filename);
		fn->FCBBlock=rootFCB;
		fn->IfDelete=0;
		fn->IfCanRead=IfCanRead;
		fn->IfCanWrite=IfCanWrite;

		//创建时间
		int time;
		fread(&time,4,1,fpDisk);
		int second=time&0x1F;//00011111
		int minute=(time>>5)&0x3f;//00111111
		int hour=(time>>11)&0x1f;//00011111

		time=time>>16;

		int day=time&0x1f;
		int month=(time>>5)&0x0f;
		int year=((time>>9)&0x7f)+2000;

		fn->createtime[12]=second/10;
		fn->createtime[13]=second%10;
		fn->createtime[10]=minute/10;
		fn->createtime[11]=minute%10;
		fn->createtime[ 8]=hour/10;
		fn->createtime[ 9]=hour%10;
		fn->createtime[ 6]=day/10;
		fn->createtime[ 7]=day%10;
		fn->createtime[ 4]=month/10;
		fn->createtime[ 5]=month%10;
		fn->createtime[ 0]=year/1000;
		fn->createtime[ 1]=year%1000/100;
		fn->createtime[ 2]=year%100/10;
		fn->createtime[ 3]=year%10;

		int SonNum;
		fread(&SonNum,4,1,fpDisk);

		fn->SonNum=SonNum;

		//首簇号
		char ThreeBytes[3];
		fread(ThreeBytes,1,3,fpDisk);
		fn->FDBBlock=ThreeToInt(ThreeBytes);

		fn->type=type;

		int *SonFCB=(int *)malloc(SonNum*sizeof(int));
		GetSonFCB(SonNum,fn->FDBBlock,SonFCB);
		fn->childnode=(int*)malloc(1000*sizeof(int));

		fn->fatherFid=fatherFid;

		fileIndex[fid]=FI;
		fid++;

		for (int i=0;i<SonNum;i++)
		{
			fn->childnode[i]=fid;
			fid=BuildFileTree(SonFCB[i],fid,fn->fid);
		}
		free(SonFCB);
		return fid;
	}
}

void GetSonFCB(int SonNum,int FDB,int *outData)
{
	int FDBUsed=(SonNum+1022)/1023;
	int nowFDB=FDB;
	for (int i=0;i<FDBUsed-1;i++)
	{
		int add=AddressOfBlock(nowFDB);
		fseek(fpDisk,add,0);
		for (int j=0;j<1023;j++)
		{
			int tmp;
			fread(&tmp,4,1,fpDisk);
			outData[1023*i+j]=tmp;
		}
		char trash;
		fread(&trash,1,1,fpDisk);
		char ThreeBytes[3];
		fread(ThreeBytes,1,3,fpDisk);
		int nextFDB=ThreeToInt(ThreeBytes);
		nowFDB=nextFDB;
	}

	int FcbInLastFdb=SonNum%1023;
	int add=AddressOfBlock(nowFDB);
	fseek(fpDisk,add,0);
	for (int i=0;i<FcbInLastFdb;i++)
	{
		int tmp;
		fread(&tmp,4,1,fpDisk);
		outData[1023*(FDBUsed-1)+i]=tmp;
	}
	
	return;
}