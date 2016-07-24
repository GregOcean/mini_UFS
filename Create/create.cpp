#include <stdio.h>
#include <iostream>
#include <string>

//#define _1M_
#define _1G_

#ifdef _1G_
#define FDBNum 261354
#define FCBRemainNum 100000
#endif

// #ifdef _1M_
// #define FDBNum 248
// #define FCBRemainNum 32
// #endif

using namespace std;

void IntToThree(int source,char *Dest)
{
	Dest[0]=(source>>16)&0xff;
	Dest[1]=(source>>8)&0xff;
	Dest[2]=(source)&0xff;
}

int main(int argc,char* argv[])
{

	FILE *fp;
	char c_zero=0;
	int  i_zero=0;
	int FileNum=1;
	int FirstBlankFDB=1;//空文件数据块标记初始化
	int FirstBlankFCB=3;//空文件控制块标记初始化
	if (argc>1)
	{
		fp = fopen(argv[1],"wb+");
	}
	else
	{
		fp=fopen("VirtualDisk.bleg","wb+");
	}
	

#ifdef _1G_

	fseek(fp,1024*1024*1024L,0);//1G

#endif

// #ifdef _1M_
// 
// 	fseek(fp,1024*1024L,0);//1M
// 
// #endif
	
	fwrite(&c_zero,1,1,fp);

	fseek(fp,0,0);

	char flag[5]="u-fs";
	fwrite(flag,1,4,fp);

	fwrite(&FileNum,4,1,fp);
	fwrite(&FirstBlankFDB,4,1,fp);
	fwrite(&FirstBlankFCB,4,1,fp);

	char Username[10];
	char Password[10];
	strcpy(Username,"Root");
	strcpy(Password,"123456");

	fwrite(Username,1,10,fp);
	fwrite(Password,1,10,fp);

	fseek(fp,1024,0);

	char dirname[8]="root";

	fwrite(dirname,1,8,fp);

	char ext[3];
	memset(ext,0,sizeof(ext));

	fwrite(ext,1,3,fp);

	char nodetype=1;

	fwrite(&nodetype,1,1,fp);

	char symbol=0x60;

	fwrite(&symbol,1,1,fp);
	int time=0;
	fwrite(&time,4,1,fp);

	int sonnum=0;

	fwrite(&sonnum,4,1,fp);

	char FDB[3];
	IntToThree(FCBRemainNum+3,FDB);
	fwrite(FDB,1,3,fp);

	char c_zreo3[3];
	memset(c_zreo3,0,3);
	fwrite(c_zreo3,1,3,fp);
	fwrite(c_zreo3,1,3,fp);

	fwrite(&c_zero,1,1,fp);
	fwrite(&c_zero,1,1,fp);

	fseek(fp,1024+32*FCBRemainNum,0); //定位位图块
	char tmp=0x80;
	fwrite(&tmp,1,1,fp);
	for (int i=1;i<(FDBNum+7)/8;i++)
	{
		fwrite(&c_zero,1,1,fp);
	}
	
	fclose(fp);
	printf("文件创建成功。\n");
	return 0;
}