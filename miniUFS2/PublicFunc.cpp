#include "Global.h"
#include "stdlib.h"
#include "math.h"
//#include "regex.h"

int AddressOfBlock(int BlockID)
{
	//系统块
	if (BlockID==1)
	{
		return 0;
	}
	//控制块
	else if (BlockID>=2&&BlockID<=FCBRemainNum+1)
	{
		return 1024+(BlockID-2)*32;
	}
	//位图块
	else if (BlockID==FCBRemainNum+2)
	{
		return 1024+32*FCBRemainNum;
	}
	//数据块
	else
#ifdef _1G_
		return 1024+32*FCBRemainNum+32*1024+(BlockID-FCBRemainNum-3)*BlockSize;
#endif
		
// #ifdef _1M_
// 		return 1024+32*FCBRemainNum+32+(BlockID-FCBRemainNum-3)*BlockSize;
// #endif
		

}


bool WriteToBlock(int BlockID,char *indata,int length)
{

	int add=AddressOfBlock(BlockID);
	fseek(fpDisk,add,0);
	fwrite(indata,1,length,fpDisk);
	return true;
}


int ReadBlock(int BlockID,char *outdata,int length)
{
	int add=AddressOfBlock(BlockID);
	fseek(fpDisk,add,0);
	fread(outdata,1,length,fpDisk);
	return 0;
}

bool ChangeAttribute(int mode,int fid)
{
	FileIndex FI=fileIndex[fid];
	FileNode fn=*FI.node;
	int BlockID=fn.FCBBlock;
	int add=AddressOfBlock(BlockID);
	if (mode==1)
	{
		fseek(fpDisk,add,0);
		fwrite(fn.filename,1,8,fpDisk);
		fwrite(fn.extention,1,3,fpDisk);
		fwrite(&fn.type,1,1,fpDisk);


		char tmp=0;
		if (fn.IfDelete)
		{
			tmp|=0x80;
		}
		if (fn.IfCanRead)
		{
			tmp|=0x40;
		}
		if (fn.IfCanWrite)
		{
			tmp|=0x20;
		}
		//fprintf(fpDisk,"%c",tmp);
		fwrite(&tmp,1,1,fpDisk);

		//fprintf(fpDisk,"%d",fn.filesize);
		fwrite(&fn.filesize,4,1,fpDisk);


		int year=fn.createtime[0]*1000+fn.createtime[1]*100+fn.createtime[2]*10+fn.createtime[3];
		int month=fn.createtime[4]*10+fn.createtime[5];
		int day=fn.createtime[6]*10+fn.createtime[7];
		int hour=fn.createtime[8]*10+fn.createtime[9];
		int minute=fn.createtime[10]*10+fn.createtime[11];
		int second=fn.createtime[12]*10+fn.createtime[13];

		int time=((((year-2000)<<9)+(month<<5)+day)<<16)+((hour<<11)+(minute<<5)+(second>>1));
		//fprintf(fpDisk,"%d",time);
		fwrite(&time,4,1,fpDisk);

		int year2=fn.lastedittime[0]*1000+fn.lastedittime[1]*100+fn.lastedittime[2]*10+fn.lastedittime[3];
		int month2=fn.lastedittime[4]*10+fn.lastedittime[5];
		int day2=fn.lastedittime[6]*10+fn.lastedittime[7];
		int hour2=fn.lastedittime[8]*10+fn.lastedittime[9];
		int minute2=fn.lastedittime[10]*10+fn.lastedittime[11];
		int second2=fn.lastedittime[12]*10+fn.lastedittime[13];

		int time2=((((year2-2000)<<9)+(month2<<5)+day2)<<16)+((hour2<<11)+(minute2<<5)+(second2>>1));
		//fprintf(fpDisk,"%d",time2);
		fwrite(&time2,4,1,fpDisk);

		char ThreeBytes[3];
		IntToThree(fn.FDBBlock,ThreeBytes);

		fwrite(&ThreeBytes[0],1,1,fpDisk);
		fwrite(&ThreeBytes[1],1,1,fpDisk);
		fwrite(&ThreeBytes[2],1,1,fpDisk);

		int trash=0;
		fwrite(&trash,4,1,fpDisk);
	}

	else
	{
		fseek(fpDisk,add,0);
		fwrite(fn.filename,1,8,fpDisk);
		fwrite(fn.extention,1,3,fpDisk);
		fwrite(&fn.type,1,1,fpDisk);


		char tmp=0;
		if (fn.IfDelete)
		{
			tmp|=0x80;
		}
		if (fn.IfCanRead)
		{
			tmp|=0x40;
		}
		if (fn.IfCanWrite)
		{
			tmp|=0x20;
		}
		//fprintf(fpDisk,"%c",tmp);
		fwrite(&tmp,1,1,fpDisk);

		//fprintf(fpDisk,"%d",fn.filesize);
		//fwrite(&fn.filesize,4,1,fpDisk);


		int year=fn.createtime[0]*1000+fn.createtime[1]*100+fn.createtime[2]*10+fn.createtime[3];
		int month=fn.createtime[4]*10+fn.createtime[5];
		int day=fn.createtime[6]*10+fn.createtime[7];
		int hour=fn.createtime[8]*10+fn.createtime[9];
		int minute=fn.createtime[10]*10+fn.createtime[11];
		int second=fn.createtime[12]*10+fn.createtime[13];

		int time=((((year-2000)<<9)+(month<<5)+day)<<16)+((hour<<11)+(minute<<5)+(second>>1));
		//fprintf(fpDisk,"%d",time);
		fwrite(&time,4,1,fpDisk);

		fwrite(&fn.SonNum,4,1,fpDisk);

		char ThreeBytes[3];
		IntToThree(fn.FDBBlock,ThreeBytes);

		fwrite(&ThreeBytes[0],1,1,fpDisk);
		fwrite(&ThreeBytes[1],1,1,fpDisk);
		fwrite(&ThreeBytes[2],1,1,fpDisk);

		int trash=0;
		fwrite(&trash,4,1,fpDisk);
		fwrite(&trash,4,1,fpDisk);

		int FDB=fn.FDBBlock;
		int addOfFDB=AddressOfBlock(FDB);
		fseek(fpDisk,addOfFDB,0);
		for (int i=0;i<fn.SonNum;i++)
		{
			fwrite(&fileIndex[fn.childnode[i]].node->FCBBlock,4,1,fpDisk);
		}

	}

	return true;
}


int GetFileID(char*filename,char *extention)
{
	for(int i=0;i<NowDirFileNum;i++)
	{
		if (!lstrcmpiA(NowDirDirTree[i].filename,filename)&&!lstrcmpiA(NowDirDirTree[i].extention,extention))
		{
			return NowDirDirTree[i].fid;
		}
	}
	return -1;
}


int GetOperateID(char *op)
{
	int oid;
	for (oid=0;oid<29;oid++)
	{
		if (!lstrcmpiA(op,operateList[oid]))
		{
			return oid;
		}
	}
	return -1;
}



int ThreeToInt(char *source)
{
	int tmp2=0;
	//char tmp[3];
	int tmp11=source[0];
	int tmp22=source[1];
	int tmp33=source[2];
	//tmp2=tmp11*pow(2,16)+tmp22*pow(2,8)+tmp33;

	tmp11&=0xff;
	tmp22&=0xff;
	tmp33&=0xff;
	
 	tmp2|=(tmp11<<16);
 	tmp2|=(tmp22<<8);
 	tmp2|=(tmp33);
	return tmp2;
}


void IntToThree(int source,char *Dest)
{
	Dest[0]=(source>>16)&0xff;
	Dest[1]=(source>>8)&0xff;
	Dest[2]=(source)&0xff;
}


bool ChangeNowDir(char *dirOri)
{

	if (dirOri[0]==0)
	{
		return ChangeNowDir(NowDirRoute);
	}

	int fid;
	char dir[10000];
	strcpy(dir,dirOri);
	if (dir[0]=='.'&&dir[1]=='.')
	{
		if (NowDirFid!=1)
		{
			fid=fileIndex[NowDirFid].node->fatherFid;
			ChangeNowDirFid(fid);
			char *p=NowDirRoute+strlen(NowDirRoute);
			while(p!=NowDirRoute)
			{
				if (*p=='\\')
				{
					break;
				}
				p--;
			}
			*p=0;
		}
		if (dir[2]!=0)
		{
			strcpy(dir,dir+3);
			ChangeNowDir(dir);
		}
		
	}
	else if (dir[0]=='.')
	{
		if (strlen(dir)>1)
		{
			strcpy(dir,dir+2);
			if (strchr(dir,'\\'))
			{
				ChangeNowDir(dir);
			}
		}
		
		
	}
	else if (dir[0]=='~')
	{
		ChangeNowDirFid(1);
		memset(NowDirRoute,0,sizeof(NowDirRoute));
		strcpy(NowDirRoute,"~");
		if (strlen(dir)>1)
		{
			strcpy(dir,&dir[2]);
			ChangeNowDir(dir);
		}
		
	}
	else
	{
		fid=GetDirID(1,dir);
		if (fid==-1)
		{
			printf("找不到该目录。\n");
			return false;
		}
		ChangeNowDirFid(fid);
		ChangeNowDirName(1,dir);
	}
	return true;
}

void ChangeNowDirFid(int fid)
{
	if (fileIndex[fid].type==t_File)
	{
		printf("目标不是文件目录\n");
	}
	NowDirFid=fid;
	FileIndex FI=fileIndex[fid];
	FileNode fn=*FI.node;
	if (NowDirDirTree!=NULL)
	{
		free(NowDirDirTree);
	}
	NowDirFileNum=fn.SonNum;
	NowDirDirTree=(FileNode*)malloc(fn.SonNum*sizeof(FileNode));
	for (int i=0;i<fn.SonNum;i++)
	{
		NowDirDirTree[i]=*fileIndex[fn.childnode[i]].node;
	}
}

void ChangeNowDirName(int mode,char *Dir)
{
	if (mode==1)
	{
		strcat(NowDirRoute,"\\");
		strcat(NowDirRoute,Dir);
		int len=strlen(NowDirRoute);
		if (NowDirRoute[len-1]=='\\')
		{
			NowDirRoute[len-1]=0;
		}

	}
	else
	{

	}
}

int GetDirID(int mode,char *Dir)
{
	char *dir;
	dir=(char*)malloc(8*MaxDirDepth);
	strcpy(dir,Dir);
	int tmpfid=NowDirFid;
	if (mode==1)
	{
		while(strlen(dir))
		{
			char *p=strchr(dir,'\\');
			if (p)
			{
				char q[100];
				memset(q,0,100);
				for(int i=0;i<p-dir;i++)
				{
					q[i]=dir[i];
				}
				if (strlen(q)>8)
				{
					printf("文件夹名太长。\n");
					return -1;
				}
				int fid=-1;
				FileNode fn=*fileIndex[tmpfid].node;
				for(int i=0;i<fn.SonNum;i++)
				{
					if (fileIndex[fn.childnode[i]].type==t_Folder&&!lstrcmpiA(q,fileIndex[fn.childnode[i]].filename))
					{
						fid=fn.childnode[i];
						break;
					}
				}
				if (fid==-1)
				{
					return -1;
				}
				tmpfid=fid;
				dir=p+1;
			}
			else
			{
				char q[100];
				memset(q,0,100);
				strcpy(q,dir);
				if (strlen(q)>8)
				{
					printf("文件夹名过长。\n");
					return -1;

				}
				int fid=-1;
				FileNode fn=*fileIndex[tmpfid].node;
				for(int i=0;i<fn.SonNum;i++)
				{
					if (fileIndex[fn.childnode[i]].type==t_Folder&&!lstrcmpiA(q,fileIndex[fn.childnode[i]].filename))
					{
						fid=fn.childnode[i];
						break;
					}
				}
				if (fid==-1)
				{
					return -1;
				}
				tmpfid=fid;
				int len=strlen(dir);
				dir=dir+len;
			}
		}
		return tmpfid;
	}
	else
	{
		return -1;
	}
}

int GetNextBlankFDB()
{
	for(int i=FirstBlankFDB+1;;i=(i+1)%FDBNum)
	{
		if (FDBBitmap[i]==b_Free)
		{
			return i;
		}
	}
	return -1;
}

int ReplaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr)
{
	int  StringLen;
	char caNewString[1000];

	char *FindPos = strstr(sSrc, sMatchStr);
	if( (!FindPos) || (!sMatchStr) )
		return -1;

	while( FindPos )
	{
		memset(caNewString, 0, sizeof(caNewString));
		StringLen = FindPos - sSrc;
		strncpy(caNewString, sSrc, StringLen);
		strcat(caNewString, sReplaceStr);
		strcat(caNewString, FindPos + strlen(sMatchStr));
		strcpy(sSrc, caNewString);

		FindPos = strstr(sSrc, sMatchStr);
	}

	return 0;
}


void str2Reg(char *str)
{
	char tmp[1000]="(";
	strcat(tmp,str);
	strcat(tmp,")");
	strcpy(str,tmp);
	
}

