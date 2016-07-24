#include "Global.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Close()
{
	//更改系统去三个数据
	fseek(fpDisk,4,0);
	fwrite(&TotalFileNum,4,1,fpDisk);
	fwrite(&FirstBlankFDB,4,1,fpDisk);
	fwrite(&FirstBlankFCB,4,1,fpDisk);

	fwrite(Username,1,10,fpDisk);
	fwrite(password,1,10,fpDisk);

	int i = 0;
	bool TF= true;
	int p=AddressOfBlock(FCBRemainNum+2);
	fseek(fpDisk,p,0);
	while (i<FDBNum)
	{
		int k=0;
		int sum=0;
		while(k<8)
		{
			if (FDBBitmap[i]==b_Full)
				sum=sum+pow(double(2),double(7-k));
			k++;
			i++;
			if (i>=FDBNum)
			{
					TF=false;	
					break;
			}
		}
		if (TF==0) break;
		char temp=sum;
		fwrite(&temp,1,1,fpDisk);
	}
	printf("系统退出成功！\n");
	exit(0);
}