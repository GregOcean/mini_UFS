#include "Global.h"

void cpdir(int fidsource,int fiddest)
{
	int fidsourcefdbblock;
	int filesize;
	//从文件树里的原文件的父亲节点删除原文件。
	FileIndex* FI=&fileIndex[fidsource];
	FileNode* fn1=FI->node;
	fidsourcefdbblock=fn1->FDBBlock;
	filesize=fn1->filesize;
	
	//将文件加入新的树里面。
	FI=&fileIndex[fiddest];
	FileNode *fn=FI->node;

	//将原来文件的数据块考入到现在新的文件内。
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