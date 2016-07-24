#include "Global.h"

void BlockOfFile(char *filename,char *extention)
{
	int fid=GetFileID(filename,extention);
	if (fid==-1)
	{
		printf("目录下找不到该文件。\n");
		return;
	}

	FileNode*fn=fileIndex[fid].node;
	int FileBlockNum=(fn->filesize+4095)/4096;
	int nowFDB=fn->FDBBlock;
	if (nowFDB==0)
	{
		return;
	}
	for (int i=0;i<FileBlockNum-1;i++)
	{
			printf("%-5d",nowFDB);
			int add=AddressOfBlock(nowFDB);
			fseek(fpDisk,add+4093,0);

			int nextBlock;
			char ThreeBytes[3];
			fread(ThreeBytes,1,3,fpDisk);

			nextBlock=ThreeToInt(ThreeBytes);

			nowFDB=nextBlock;
			if (i>0&&i%11==0)
			{
				printf("\n");
			}

		}
		printf("%-5d\n",nowFDB);

}