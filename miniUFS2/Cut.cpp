#include "Global.h"

bool cut(int mode,int fidsource,int fiddest)
{
	if(mode==1)
	{
		int fidsourcefdbblock;
		int filesize;
		//从文件树里的原文件的父亲节点删除原文件。
		FileIndex* FI=&fileIndex[fidsource];
		FileNode* fn=FI->node;
		fidsourcefdbblock=fn->FDBBlock;
		filesize=fn->filesize;
		int fatherFID=fn->fatherFid;  //找到父亲节点。
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
		ChangeAttribute(2,fatherFID);  //修改的父亲节点写道外存内。
		//将文件加入新的树里面。
		 FI=&fileIndex[fiddest];
		 fn=FI->node;
		 
		 //将原来文件的数据块考入到现在新的文件内。
		 fn->FDBBlock=fidsourcefdbblock;
		 fn->filesize=filesize;
		 ChangeAttribute(1,fiddest);
		 //fatherFID=fn->fatherFid;  //找到父亲节点。
		 //FI=&fileIndex[fatherFID];
		 //fn=FI->node;
		//将原文件加入此树下
		//fn->childnode[fn->SonNum]=fidsource;
		//fn->SonNum++;
		//ChangeAttribute(2,fatherFID);
	}
	else
	{
		int fidsourcefdbblock;
		int filesize;
		//从文件树里的原文件的父亲节点删除原文件。
		FileIndex* FI=&fileIndex[fidsource];
		FileNode* fn1=FI->node;
		fidsourcefdbblock=fn1->FDBBlock;
		filesize=fn1->filesize;
		int fatherFID=fn1->fatherFid;  //找到父亲节点。
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
		ChangeAttribute(2,fatherFID);  //修改的父亲节点写道外存内。
		//将文件加入新的树里面。
		FI=&fileIndex[fiddest];
		fn=FI->node;
		
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
	return true;
}