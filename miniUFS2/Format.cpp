#include "Global.h"

void Format(int mode)
{
	int add;//ͨ��_���ַ���
	char ZeroMark=b_Free;
	char Onemark=0x01;
	
	/*���ڴ�������е�λͼ���ÿ�*/
	memset(FDBBitmap,0,sizeof(FDBBitmap));
	FreeFDBNum=FDBNum;

	TotalFileNum=1;
	FirstBlankFDB=1;//���ļ����ݿ��ǳ�ʼ��
	FirstBlankFCB=3;//���ļ����ƿ��ǳ�ʼ��

	add=AddressOfBlock(1);//��ϵͳ���������ļ�����Ϊ0
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
		printf("�ͼ���ʽ����ɽ��ȣ�");
		for (int i=0;i<100;i++)
		{
			printf("%d%%",i);
			for (int j=0;j<25000000;j++){}
			i>9?printf("\b\b\b"):printf("\b\b");
		}
		printf("100%%\n");
	}
	
}