#include "Global.h"

void Display(int mode,int fid)
{
	if (fid==-1)
	
	{
		printf("目录下没有该文件。\n");
		return;
	}
	FileNode fn=*fileIndex[fid].node;
	int nowFDB=fn.FDBBlock;

	int size=fn.filesize;

	if (nowFDB==0||size==0)
	{
		return;
	}

	
	int BlockNum=(size+4092)/4093;
	char data[4096];
	if (mode==1)  //直接显示
	{
		for (int i=0;i<BlockNum-1;i++)
		{
			ReadBlock(nowFDB,data,4096);
			int nextBlock=ThreeToInt(&data[4093]);
			for (int j=0;j<4093;j++)
			{
				if (data[j]!='\r')
				{
					putchar(data[j]);
				}
			}
			nowFDB=nextBlock;
		}
		int remainSize=size%4093;
		if (remainSize==0)
		{
			remainSize=4093;
		}
		ReadBlock(nowFDB,data,4096);
		for (int i=0;i<remainSize;i++)
		{
			if (data[i]!='\r')
			{
				putchar(data[i]);
			}
		}
	}
	else
	{

	}
	printf("\n");
	
}