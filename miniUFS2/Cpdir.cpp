#include "Global.h"

void cpdir(int fidsource,int fiddest)
{
	int fidsourcefdbblock;
	int filesize;
	//���ļ������ԭ�ļ��ĸ��׽ڵ�ɾ��ԭ�ļ���
	FileIndex* FI=&fileIndex[fidsource];
	FileNode* fn1=FI->node;
	fidsourcefdbblock=fn1->FDBBlock;
	filesize=fn1->filesize;
	
	//���ļ������µ������档
	FI=&fileIndex[fiddest];
	FileNode *fn=FI->node;

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