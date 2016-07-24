#include "Global.h"

bool last[100]={1};

void Tree(int deep,int fid)
{
	FileNode *fn=fileIndex[fid].node;
	for (int i=0;i<fn->SonNum;i++)
	{
		for (int j=1;j<deep;j++)
		{
			if (last[j]==0)
			{
				printf("%c%c",-87,-90);
			}
			else
				printf("  ");
			printf("  ");
		}
		if (i==fn->SonNum-1)
		{
			printf("%c%c%c%c",-87,-72,-87,-92);
			last[deep]=1;
		}
		else{
			printf("%c%c%c%c",-87,-64,-87,-92);
			last[deep]=0;
		}

		FileNode *fnchild=fileIndex[fn->childnode[i]].node;
		if (fnchild->type==t_File)
		{
			printf("%s.%s\n",fnchild->filename,fnchild->extention);
		}
		else
		{
			printf("%s\n",fnchild->filename);
			Tree(deep+1,fn->childnode[i]);
		}


	}
}