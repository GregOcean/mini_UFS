#include "Global.h"

int Copy(int mode,char *filenameSourc,char *fileextSourc,
	char* filenameDest,char *fileextDest)
{
	if (mode==1) //内往内
	{
		
		int p=GetFileID(filenameSourc,fileextSourc);
		if (p==-1)
		{
			printf("复制文件不存在！\n");
			return -1;
		}
		else if (fileIndex[p].node->filesize>FreeFDBNum*4093)
		{
			printf("目标文件大小超出剩余存储空间，操作已取消\n");
			return -1;
		}
		else
		{
			int q=GetFileID(filenameDest,fileextDest);
			if (q!=-1)
			{
				printf("文件已存在，是否替换?\n",filenameDest,fileextDest);
				printf("yes(y),no(n):  ");	
				char input;
				input=getchar();
				while(input=='\n')
					input=getchar();
				if (input=='n')
				{
					printf("File existe.Can not copy.\n");
					return -1;
				}
				else
				{
					Delete(1,filenameDest,fileextDest);
				}
			}
			//
			New(1,filenameDest,fileextDest);
			q=GetFileID(filenameDest,fileextDest);
			FileNode *fnq=fileIndex[q].node;//目的地
			FileNode *fnp=fileIndex[p].node;//源文件
			fnq->filesize=fnp->filesize;
			//FileNode fn=NowDirDirTree[p];
			int nowFDB=fnp->FDBBlock;//源
			int size=fnp->filesize;//源文件大小
			int BlockNum=(size+4092)/4093;//源文件数据块数
			char data[4096];
			char desnextadd[3];
			int add=0;
			int firstFDB=-1;
			for (int i=0;i<BlockNum-1;i++)
			{
				add=AddressOfBlock(nowFDB);
				fseek(fpDisk,add,0);
				fread(data,1,4096,fpDisk);

				char three[3];
				three[0]=data[4093];
				three[1]=data[4094];
				three[2]=data[4095];
				int nextBlock=ThreeToInt(three);
				nowFDB=nextBlock;
				//
				if (i==0) firstFDB=FirstBlankFDB;		

				add=AddressOfBlock(FirstBlankFDB+FCBRemainNum+3);
				fseek(fpDisk,add,0);
				
				FDBBitmap[FirstBlankFDB]=b_Full;
				FreeFDBNum--;

				FirstBlankFDB=GetNextBlankFDB();
				IntToThree(FirstBlankFDB+FCBRemainNum+3,desnextadd);
				data[4093]=desnextadd[0];
				data[4094]=desnextadd[1];
				data[4095]=desnextadd[2];

				fwrite(data,1,4096,fpDisk);
			}
			
			//不足一块的内容
			int remainSize=size;
			if (remainSize%4093==0&&remainSize>0) 
				remainSize=4093;
			else remainSize%=4093;
			//memset(data,0,sizeof(data));
			if (remainSize>0)
			{
				add=AddressOfBlock(nowFDB);
				//fseek(fpDisk,add,0);
				ReadBlock(nowFDB,data,remainSize);

				WriteToBlock(FirstBlankFDB+FCBRemainNum+3,data,remainSize);

				FDBBitmap[FirstBlankFDB]=b_Full;
				if(firstFDB==-1) 
					firstFDB=FirstBlankFDB;
				FirstBlankFDB=GetNextBlankFDB();
				FreeFDBNum--;
			}
			
			
			fnq->FDBBlock=firstFDB+FCBRemainNum+3;
			
			ChangeAttribute(1,q);

			return fnq->filesize;
		}
	}
	else if (mode==2)//内往外
		{
			int size;
			int fid=GetFileID(filenameSourc,fileextSourc);
			if (fid==-1)
			{
				printf("目录下找不到该文件。\n",filenameSourc,fileextSourc);
				return -1;
			}
			else
			{
				FileNode *fn=fileIndex[fid].node;
				int nowFDB=fn->FDBBlock;//源文件
				size=fn->filesize;
				int BlockNum=(size+4092)/4093;
				char data[4096];
				FILE* fp;
				fp=fopen(filenameDest,"wb");
				for (int i=0;i<BlockNum-1;i++)
				{	
					int add=AddressOfBlock(nowFDB);
					fseek(fpDisk,add,0);
					fread(data,1,4096,fpDisk);

					char three[3];
					three[0]=data[4093];
					three[1]=data[4094];
					three[2]=data[4095];
					int nextBlock=ThreeToInt(three);
					nowFDB=nextBlock;

					//fseek(fpDisk,add,0);
					fwrite(data,1,4093,fp);
				}
				int remainSize=size;
				if (remainSize%4093==0&&remainSize>0) remainSize=4093;
				else remainSize%=4093;
				ReadBlock(nowFDB,data,remainSize);
				for (int j=0;j<remainSize;j++)
				{
					fputc(data[j],fp);
				}
				int flen=ftell(fp);
				fclose(fp);
			}
			return size;
		}
		else//外往内		
		{
			FILE* fp;
			fp=fopen(filenameSourc,"rb");
			//
			if (fp==NULL)
			{
				printf("未找到目标文件，操作已终止\n");
				return -1;
			}
			fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
			int flen=ftell(fp); /* 得到文件大小 */
			if (flen>FreeFDBNum*4093)
			{
				printf("目标文件大小超出剩余存储空间，操作已取消\n");
				return -1;
			}
			fseek(fp,0L,SEEK_SET);
			//
			int q=GetFileID(filenameDest,fileextDest);
			
			if (q!=-1)
			{
				printf("文件已存在，是否替换?\n",filenameDest,fileextDest);
				printf("yes(y),no(n):  ");	
				char input;
				input=getchar();
				while(input=='\n')
					input=getchar();
				if (input=='n')
				{
					printf("File existe.Can not copy.\n");
					return -1;
				}
				else
				{
					Delete(1,filenameDest,fileextDest);
					ChangeNowDir(NowDirRoute);
				}
			}
			//
			New(1,filenameDest,fileextDest);
			int fid=GetFileID(filenameDest,fileextDest);
			FileNode *fn=fileIndex[fid].node;

			int filesize=flen; //文件大小
			int firstFDB=-1;
			char desnextadd[3];
			char data[4096];

			for (int i=0;i<(flen/4093);i++)
			{
				fread(data,1,4093,fp);
				int add=AddressOfBlock(FirstBlankFDB+FCBRemainNum+3);
				fseek(fpDisk,add,0);
				
				if (i==0) firstFDB=FirstBlankFDB;

				FDBBitmap[FirstBlankFDB]=b_Full;
				FreeFDBNum--;

				FirstBlankFDB=GetNextBlankFDB();
				IntToThree(FirstBlankFDB+FCBRemainNum+3,desnextadd);
				data[4093]=desnextadd[0];
				data[4094]=desnextadd[1];
				data[4095]=desnextadd[2];

				fwrite(data,1,4096,fpDisk);
				
			}
			
			if (flen%4093!=0&&flen>0)
			{
				int remainSize=flen;
				if (remainSize%4093==0&&remainSize>0) remainSize=4093;
				else remainSize%=4093;

				int add=AddressOfBlock(FirstBlankFDB+FCBRemainNum+3);
				fseek(fpDisk,add,0);
				fread(data,1,remainSize,fp);
				WriteToBlock(FirstBlankFDB+FCBRemainNum+3,data,remainSize);
				
				FDBBitmap[FirstBlankFDB]=b_Full;
				FreeFDBNum--;
				

				if(firstFDB==-1) 
					firstFDB=FirstBlankFDB;

				FirstBlankFDB=GetNextBlankFDB();

				fn->FDBBlock=firstFDB+FCBRemainNum+3;
			}

			fn->filesize=filesize;			
			ChangeAttribute(1,fid);		
			fclose(fp);
			return flen;
		}	
		
}