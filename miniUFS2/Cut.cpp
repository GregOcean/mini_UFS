#include "Global.h"

bool cut(int mode,int fidsource,int fiddest)
{
	if(mode==1)
	{
		int fidsourcefdbblock;
		int filesize;
		//���ļ������ԭ�ļ��ĸ��׽ڵ�ɾ��ԭ�ļ���
		FileIndex* FI=&fileIndex[fidsource];
		FileNode* fn=FI->node;
		fidsourcefdbblock=fn->FDBBlock;
		filesize=fn->filesize;
		int fatherFID=fn->fatherFid;  //�ҵ����׽ڵ㡣
		FI=&fileIndex[fatherFID];
		fn=FI->node;
		int i;
		for (i=0;i<fn->SonNum;i++)
		{
			if (fn->childnode[i]==fidsource)
			{
				break;
			}
		}
		for(int j=i;j<fn->SonNum-1;j++)
		{
			fn->childnode[j]=fn->childnode[j+1];
		}
		fn->SonNum--;
		ChangeAttribute(2,fatherFID);  //�޸ĵĸ��׽ڵ�д������ڡ�
		//���ļ������µ������档
		 FI=&fileIndex[fiddest];
		 fn=FI->node;
		 
		 //��ԭ���ļ������ݿ鿼�뵽�����µ��ļ��ڡ�
		 fn->FDBBlock=fidsourcefdbblock;
		 fn->filesize=filesize;
		 ChangeAttribute(1,fiddest);
		 //fatherFID=fn->fatherFid;  //�ҵ����׽ڵ㡣
		 //FI=&fileIndex[fatherFID];
		 //fn=FI->node;
		//��ԭ�ļ����������
		//fn->childnode[fn->SonNum]=fidsource;
		//fn->SonNum++;
		//ChangeAttribute(2,fatherFID);
	}
	else
	{
		int fidsourcefdbblock;
		int filesize;
		//���ļ������ԭ�ļ��ĸ��׽ڵ�ɾ��ԭ�ļ���
		FileIndex* FI=&fileIndex[fidsource];
		FileNode* fn1=FI->node;
		fidsourcefdbblock=fn1->FDBBlock;
		filesize=fn1->filesize;
		int fatherFID=fn1->fatherFid;  //�ҵ����׽ڵ㡣
		FI=&fileIndex[fatherFID];
		FileNode* fn;
		fn=FI->node;
		int i;
		for (i=0;i<fn->SonNum;i++)
		{
			if (fn->childnode[i]==fidsource)
			{
				break;
			}
		}
		for(int j=i;j<fn->SonNum-1;j++)
		{
			fn->childnode[j]=fn->childnode[j+1];
		}
		fn->SonNum--;
		ChangeAttribute(2,fatherFID);  //�޸ĵĸ��׽ڵ�д������ڡ�
		//���ļ������µ������档
		FI=&fileIndex[fiddest];
		fn=FI->node;
		
		//��ԭ���ļ������ݿ鿼�뵽�����µ��ļ��ڡ�
		fn->FDBBlock=fidsourcefdbblock;
		//fn->filesize=filesize;
		fn->SonNum=fn1->SonNum;
		for(int i=0;i<fn->SonNum;i++)
		{
			fn->childnode[i]=fn1->childnode[i];
		}
		ChangeAttribute(2,fiddest);

		ChangeNowDir(NowDirRoute);
	}
	return true;
}