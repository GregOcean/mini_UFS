#include "Global.h"
#include"string.h"
#include"stdlib.h"
void recovery(char *filename,char *extention)
{
	
	FileNode *recoverfile;
	int fid=-1;
	//��ɾ�������ж�λҪ�ָ����ļ�,�Ӻ�����ǰ�ǻָ����µ��ļ���
	int i;
	for(i=DeletedNum-1;i>=0;i--)
		if(lstrcmpiA(fileIndex[Deleted[i]].filename,filename)==0&&lstrcmpiA(fileIndex[Deleted[i]].extention,extention)==0)
			{  
				fid=Deleted[i];
				
				break;
			}
	//�ƶ�ɾ�����С�
		if (fid==-1)
		{
			printf("�Ҳ������ļ���\n");
			return;
		}
		for(int j=i;j<DeletedNum-1;j++)
			Deleted[j]=Deleted[j+1];

		recoverfile=fileIndex[fid].node;
		recoverfile->IfDelete=0;
		DeletedNum=DeletedNum-1;

	//���ָ��ļ�������д����档
		ChangeAttribute(1,fid);


		


		FileIndex *FI=&fileIndex[recoverfile->fatherFid];
		FileNode *fn=FI->node;
		int *tmp=(int*)malloc(fn->SonNum*4);
		memcpy(tmp,fn->childnode,fn->SonNum*4);
		fn->SonNum++;
		fn->childnode=(int*)realloc(fn->childnode,fn->SonNum);
		memcpy(fn->childnode,tmp,(fn->SonNum-1)*4);
		free(tmp);
		fn->childnode[fn->SonNum-1]=fid;

		ChangeAttribute(2,recoverfile->fatherFid);



	//�޸�λͼ�顣
		int  FileBlockNum=(recoverfile->filesize+4095)/4096;
		if (FileBlockNum==0)
		{
			printf("�ļ� %s.%s �ָ��ɹ���\n",filename,extention);
			return;
		}
		int  nowFDB=recoverfile->FDBBlock;
		for(int i=0;i<FileBlockNum-1;i++)
		{
			FDBBitmap[nowFDB-FCBRemainNum-3]=b_Full;
			FreeFDBNum--;
			int add=AddressOfBlock(nowFDB);
			fseek(fpDisk,add+4093,0);

			int nextBlock;
			char ThreeBytes[3];
			fread(ThreeBytes,1,3,fpDisk);

			nextBlock=ThreeToInt(ThreeBytes);

			nowFDB=nextBlock;
		}
		FDBBitmap[nowFDB-FCBRemainNum-3]=b_Full;
		FreeFDBNum--;
		printf("�ļ� %s.%s �ָ��ɹ���\n",filename,extention);
		
}