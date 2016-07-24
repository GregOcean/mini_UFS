#include "Global.h"
#include "stdlib.h"
#define PCRE_STATIC // 静态库编译选项         
#include "pcre.h"      
#define OVECCOUNT 30 /* should be a multiple of 3 */      
#define EBUFLEN 128      
#define BUFLEN 1024      
#pragma  comment (lib,"pcre.lib")   
void ReleaseFDB(int mode,int fid);
bool Delete(int mode,char *filename,char*extention)
{
	if (mode==1)
	{
		int fid;
		fid=GetFileID(filename,extention);      //定位
		//判断文件是否能删除。
		if(fid==-1){
			printf("目录下找不到该文件.\n",filename,extention);
			return false;
		}
		else
		{
			//TotalFileNum--;

			FileIndex* FI=&fileIndex[fid];
			FileNode* fn=FI->node;
			fn->IfDelete=1;
			//将删除的控制块加入删除队列中。
			Deleted[DeletedNum]=fid;
			DeletedNum=DeletedNum+1;
			//判断删除是否够用。不够用扩充数组。
			if(DeletedNum==DeletedSpace)
			{
				DeletedSpace=DeletedSpace+IndexSpaceInterval;
				Deleted=(int *)realloc(Deleted,DeletedSpace*sizeof(int));
			}
			//写道外存里。
			ChangeAttribute(1,fid);
			//将该文件从文件树中删除。

			ReleaseFDB(1,fid);

			int fatherFID=fn->fatherFid;
			FI=&fileIndex[fatherFID];
			fn=FI->node;
			int i;
			for (i=0;i<fn->SonNum;i++)
			{
				if (fn->childnode[i]==fid)
				{
					break;
				}
			}
			for(int j=i;j<fn->SonNum-1;j++)
			{
				fn->childnode[j]=fn->childnode[j+1];
			}
			fn->SonNum--;
			ChangeAttribute(2,fatherFID);
		}
	}
	else if(mode==2)
	{
		int fid;
		fid=GetDirID(1,filename);      //定位
		//判断文件是否能删除。
		if(fid==-1){
			printf("找不到该目录。\n",filename);
			return false;
		}
		else
		{
			//TotalFileNum--;

			FileIndex* FI=&fileIndex[fid];
			FileNode* fn=FI->node;
			fn->IfDelete=1;
			//将删除的控制块加入删除队列中。
			Deleted[DeletedNum]=fid;
			DeletedNum=DeletedNum+1;
			//判断删除是否够用。不够用扩充数组。
			if(DeletedNum==DeletedSpace)
			{
				DeletedSpace=DeletedSpace+IndexSpaceInterval;
				Deleted=(int *)realloc(Deleted,DeletedSpace*sizeof(int));
			}

			ChangeAttribute(2,fid);

			ReleaseFDB(2,fid);

			int fatherFID=fn->fatherFid;
			FI=&fileIndex[fatherFID];
			fn=FI->node;
			int i;
			for (i=0;i<fn->SonNum;i++)
			{
				if (fn->childnode[i]==fid)
				{
					break;
				}
			}
			for(int j=i;j<fn->SonNum-1;j++)
			{
				fn->childnode[j]=fn->childnode[j+1];
			}
			fn->SonNum--;
			ChangeAttribute(2,fatherFID);
		}
	}
		else if(mode==3)
		{
			if (NowDirDirTree!=NULL)
			{
				free(NowDirDirTree);
			}
			NowDirFileNum=DeletedNum;
			NowDirDirTree=(FileNode*)malloc(DeletedNum*sizeof(FileNode));
			for (int i=0;i<DeletedNum;i++)
			{
				NowDirDirTree[i]=*fileIndex[Deleted[i]].node;
			}
			Dir(0,0);
			ChangeNowDirFid(NowDirFid);
		}
		else
		{
			FileNode fn1;
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
			int i;
			for (i=0;i<NowDirFileNum;i++)
			{
				fn1=NowDirDirTree[i];
				//DisplayCrtTime(&fn);

				if (fn1.type==t_File)
				{
					memset(ovector1,0,sizeof(ovector1));
					memset(ovector2,0,sizeof(ovector2));

					strcpy(srcfilename,fn1.filename);
					strcpy(pattern1,filename);
					strcpy(srcextention,fn1.extention);
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
					if (rc1 >= 0 && rc2>=0 &&strlen(fn1.filename)==substring_length1 && strlen(fn1.extention)==substring_length2) {  
						int fid=fn1.fid;
						printf("已删除文件 ");
						printf("%s",fn1.filename);
						printf(".%s",fn1.extention);
						printf("\n");
						FileIndex* FI=&fileIndex[fid];
						FileNode* fn=FI->node;
						fn->IfDelete=1;
						//将删除的控制块加入删除队列中。
						Deleted[DeletedNum]=fid;
						DeletedNum=DeletedNum+1;
						//判断删除是否够用。不够用扩充数组。
						if(DeletedNum==DeletedSpace)
						{
							DeletedSpace=DeletedSpace+IndexSpaceInterval;
							Deleted=(int *)realloc(Deleted,DeletedSpace*sizeof(int));
						}
						//写道外存里。
						ChangeAttribute(1,fid);
						//将该文件从文件树中删除。

						ReleaseFDB(1,fid);

						int fatherFID=fn->fatherFid;
						FI=&fileIndex[fatherFID];
						fn=FI->node;
						int i;
						for (i=0;i<fn->SonNum;i++)
						{
							if (fn->childnode[i]==fid)
							{
								break;
							}
						}
						for(int j=i;j<fn->SonNum-1;j++)
						{
							fn->childnode[j]=fn->childnode[j+1];
						}
						fn->SonNum--;
						ChangeAttribute(2,fatherFID);

					}     

				}
			}
		}
	return true;
}


void ReleaseFDB(int mode,int fid)
{
	FileNode*fn=fileIndex[fid].node;
	if (mode==1)
	{
		
		int FileBlockNum=(fn->filesize+4095)/4096;
		int nowFDB=fn->FDBBlock;
		for (int i=0;i<FileBlockNum-1;i++)
		{
			FDBBitmap[nowFDB-FCBRemainNum-3]=b_Del;
			FreeFDBNum++;
			int add=AddressOfBlock(nowFDB);
			fseek(fpDisk,add+4093,0);

			int nextBlock;
			char ThreeBytes[3];
			fread(ThreeBytes,1,3,fpDisk);

			nextBlock=ThreeToInt(ThreeBytes);

			nowFDB=nextBlock;

		}
		if (fn->filesize!=0)
		{
			FDBBitmap[nowFDB-FCBRemainNum-3]=b_Del;
			FreeFDBNum++;
		}
	}
	else
	{
		int FDB=fn->FDBBlock-FCBRemainNum-3;
		FDBBitmap[FDB]=b_Del;
		FreeFDBNum++;
	}
}