#include "Global.h"

void Format(int mode)
{
	int add;//通用_块地址标记
	char ZeroMark=b_Free;
	char Onemark=0x01;
	
	/*将内存与外存中的位图块置空*/
	memset(FDBBitmap,0,sizeof(FDBBitmap));
	FreeFDBNum=FDBNum;

	TotalFileNum=1;
	FirstBlankFDB=1;//空文件数据块标记初始化
	FirstBlankFCB=3;//空文件控制块标记初始化

	add=AddressOfBlock(1);//将系统块中所标文件数改为0
	fseek(fpDisk,add+4,0);
	//int zero=0;
	//fwrite(&zero,4,1,fpDisk);
	fwrite(&TotalFileNum,4,1,fpDisk);
	fwrite(&FirstBlankFDB,4,1,fpDisk);
	fwrite(&FirstBlankFCB,4,1,fpDisk);

	char Username[10];
	char Password[10];
	strcpy(Username,"Root");
	strcpy(Password,"123456");

	fwrite(Username,1,10,fpDisk);
	fwrite(Password,1,10,fpDisk);

	fseek(fpDisk,1024,0);

	char dirname[8]="root";

	fwrite(dirname,1,8,fpDisk);

	char ext[3];
	memset(ext,0,sizeof(ext));

	fwrite(ext,1,3,fpDisk);

	char nodetype=1;

	fwrite(&nodetype,1,1,fpDisk);

	char symbol=0x60;

	fwrite(&symbol,1,1,fpDisk);
	int time=0;
	fwrite(&time,4,1,fpDisk);

	int sonnum=0;

	fwrite(&sonnum,4,1,fpDisk);

	char FDB[3];
	IntToThree(FCBRemainNum+3,FDB);
	fwrite(FDB,1,3,fpDisk);

	BuildFileTree(2,1,1);

	ChangeNowDirFid(1);
	memset(NowDirRoute,0,sizeof(NowDirRoute));

	strcpy(NowDirRoute,"~");
	if (mode==2)
	{
		printf("低级格式化完成进度：");
		for (int i=0;i<100;i++)
		{
			printf("%d%%",i);
			for (int j=0;j<25000000;j++){}
			i>9?printf("\b\b\b"):printf("\b\b");
		}
		printf("100%%\n");
	}
	
}