//#define   WIN32_LEAN_AND_MEAN
#include "Global.h"
#include "string.h"
#include "time.h"

//#include <windows.h>

bool Edit(int mode,char *filename,char *extention/*,int mode*/)
{
	if (mode==1)
	{
			char c;
		//char tmp;
		char data[4096];//����ʱд��һ�ص����顣
		int count=-1;
		char dest[3];
		int fid=GetFileID(filename,extention);
		int NextBlankFDB;
		bool flag_changeline=0;
		struct tm *nowtime;
		time_t tmp;

		if (fid==-1)
		{
			printf("Ŀ¼���Ҳ������ļ���\n");
			return false;
		}

		FileNode *fn=fileIndex[fid].node;

		if (fid!=-1)
		{
			/*if (DirTree[temp].filesize!=0)
			{
				//��ʾ�ļ���
			}*/
			//system("stty raw");
			fn->filesize=0;
			printf("File Opened,Ctrl+Z to complete\n");
			fseek(fpDisk,fn->FDBBlock,0);
		
			while(FDBBitmap[FirstBlankFDB]!=b_Free)//ȷ����һ���������ݿ�
			{
				FirstBlankFDB=(FirstBlankFDB+1)%FDBNum;
			}
			fn->FDBBlock=FirstBlankFDB+FCBRemainNum+3;

		
			//IntToThree(FirstBlankFDB,dest);
		
			while ((c = getchar())!=EOF)
			{
				if (count==-1)
				{
					NextBlankFDB=FirstBlankFDB+1;
					while(FDBBitmap[NextBlankFDB]!=b_Free)//ȷ����һ���������ݿ���д�뵱ǰ���ݿ��βָ��
					{
						NextBlankFDB=(NextBlankFDB+1)%FDBNum;
					}
					IntToThree(NextBlankFDB+FCBRemainNum+3,dest);
					//Full_flag=0;
				}

			
				count++;
				fn->filesize++;
				if (flag_changeline==1)
				{
					data[count++]='\n';
					//continue;
				}
				if (c=='\n'&&count!=4092)
				{
					data[count]='\r';
					count++;
					data[count]='\n';
					fn->filesize++;
				}
			
				if (count==4092)
				{
					if (c!='\n')
					{
						data[count++]=c;
						//DirTree[fid].filesize++;
					}
					else
					{
						data[count++]='\r';
						flag_changeline=1;
						fn->filesize++;
					}
				
					data[count++]=dest[0];
					data[count++]=dest[1];
					data[count]=dest[2];
				

					WriteToBlock(FirstBlankFDB+FCBRemainNum+3,data,4096);
					FDBBitmap[FirstBlankFDB]=b_Full;
					FreeFDBNum--;
					FirstBlankFDB=NextBlankFDB;

					memset(data,0,sizeof(data));
					count=-1;
				}

				if (c!='\n'&&count<4092&&count>=0)
				{
					data[count]=c;
				}
			}
		
			if (count!=-1)//���д����һ���ݿ�
			{
				WriteToBlock(FirstBlankFDB+FCBRemainNum+3,data,count+1);
				FDBBitmap[FirstBlankFDB]=b_Full;
				FirstBlankFDB=NextBlankFDB;
				FreeFDBNum--;
			}
	//��ȡ��ǰʱ�䣨�޸�ʱ�䣩
			time(&tmp);
			nowtime=localtime(&tmp);
			int temp=nowtime->tm_year+1900;
			for(int i=0;i<4;i++)  //���껻���char��
			{
				fn->lastedittime[3-i]=temp%10;
				temp=temp/10;
			}
			//�£��գ�ʱ���֣�����㡣	
			nowtime->tm_mon=nowtime->tm_mon+1;
			fn->lastedittime[4]=(int)(nowtime->tm_mon/10);
			fn->lastedittime[5]=nowtime->tm_mon%10;
			fn->lastedittime[6]=(int)(nowtime->tm_mday/10);
			fn->lastedittime[7]=nowtime->tm_mday%10;
			fn->lastedittime[8]=(int)(nowtime->tm_hour/10);
			fn->lastedittime[9]=nowtime->tm_hour%10;
			fn->lastedittime[10]=(int)(nowtime->tm_min/10);
			fn->lastedittime[11]=nowtime->tm_min%10;
			fn->lastedittime[12]=(int)(nowtime->tm_sec/10);
			fn->lastedittime[13]=nowtime->tm_sec%10;
	//
			ChangeAttribute(1,fid);
	//		printf("�ļ��ѱ���\n");
			//system("stty cooked");
			return true;
		}
		else
		{
			printf("Ŀ¼���Ҳ������ļ���\n");
			return false;
		}
	}
	else if (mode==2)
	{
		//��λ����д��λ�á�
		char c;
		//char tmp;
		char data[4096];//����ʱд��һ�ص����顣
		int count=-1;   
		int BlockNum;
		int nowFDB;
		char dest[3];
		int fid=GetFileID(filename,extention);
		if (fid==-1)
		{
			printf("Ŀ¼���Ҳ������ļ���\n");
			return false;
		}
		int NextBlankFDB;
		bool flag_changeline=0;
		struct tm *nowtime;
		time_t tmp;
		FileNode *fn=fileIndex[fid].node;

		if (fn->filesize==0)
		{
			return Edit(1,filename,extention);

		}

		//�ж��ļ��Ƿ����
		if(fid==-1)
		{
			printf("�����ڴ��ļ�\n");
			return false;
		}
		else
		{
			printf("File Opened,Ctrl+Z to complete\n");
			FreeFDBNum++;
			//��λҪд�Ŀ�λ�á�
			nowFDB=fn->FDBBlock;
			BlockNum=(fn->filesize+4092)/4093;
			for(int i=0;i<BlockNum-1;i++)
			{
				ReadBlock(nowFDB,data,4096);
				int nextBlock=ThreeToInt(&data[4093]);
				for (int j=0;j<4093;j++)
				{
					if (data[j]!='\r')
					{
						putchar(data[j]);
					}
				}
				nowFDB=nextBlock;
			}
			//ȷ��count��ֵ��
			count=fn->filesize%4093;

			if(fn->filesize!=0)
				ReadBlock(nowFDB,data,4096);
			if(count==0&&fn->filesize!=0)
				count=4093;
			for(int i=0;i<count;i++)
			{
				if (data[i]!='\r')
				{
					putchar(data[i]);
				}
			}
				
			//��ʼ��ֵ��count��λ�ÿ�ʼд��
			
			int add=AddressOfBlock(nowFDB);
			fseek(fpDisk,add+count,0);
			while(FDBBitmap[FirstBlankFDB]!=b_Free)//ȷ����һ���������ݿ�
			{
				FirstBlankFDB=(FirstBlankFDB+1)%FDBNum;
			}
			if(count==4093)
				count=-1;
			else
				count--;
			NextBlankFDB=FirstBlankFDB;
			FirstBlankFDB=nowFDB-FCBRemainNum-3;
			while ((c = getchar())!=EOF)
			{
				if (count==-1)
				{
					NextBlankFDB=FirstBlankFDB+1;
					while(FDBBitmap[NextBlankFDB]!=b_Free)//ȷ����һ���������ݿ���д�뵱ǰ���ݿ��βָ��
					{
						NextBlankFDB=(NextBlankFDB+1)%FDBNum;
					}
					IntToThree(NextBlankFDB+FCBRemainNum+3,dest);
					//Full_flag=0;
				}
				count++;
				fn->filesize++;
				if (flag_changeline==1)
				{
					data[count++]='\n';
					//continue;
				}
				if (c=='\n'&&count!=4092)
				{
					data[count]='\r';
					count++;
					data[count]='\n';
					fn->filesize++;
				}

				if (count==4092)
				{
					if (c!='\n')
					{
						data[count++]=c;
						//DirTree[fid].filesize++;
					}
					else
					{
						data[count++]='\r';
						flag_changeline=1;
						fn->filesize++;
					}

					data[count++]=dest[0];
					data[count++]=dest[1];
					data[count]=dest[2];


					WriteToBlock(FirstBlankFDB+FCBRemainNum+3,data,4096);
					FDBBitmap[FirstBlankFDB]=b_Full;
					FreeFDBNum--;
					FirstBlankFDB=NextBlankFDB;

					memset(data,0,sizeof(data));
					count=-1;
				}

				if (c!='\n'&&count<4092&&count>=0)
				{
					data[count]=c;
				}
			}

			if (count!=-1)//���д����һ���ݿ�
			{
				WriteToBlock(FirstBlankFDB+FCBRemainNum+3,data,count+1);
				FDBBitmap[FirstBlankFDB]=b_Full;
				FreeFDBNum--;
			}
			//��ȡ��ǰʱ�䣨�޸�ʱ�䣩
			time(&tmp);
			nowtime=localtime(&tmp);
			int temp=nowtime->tm_year+1900;
			for(int i=0;i<4;i++)  //���껻���char��
			{
				fn->lastedittime[3-i]=temp%10;
				temp=temp/10;
			}
			//�£��գ�ʱ���֣�����㡣	
			nowtime->tm_mon=nowtime->tm_mon+1;
			fn->lastedittime[4]=(int)(nowtime->tm_mon/10);
			fn->lastedittime[5]=nowtime->tm_mon%10;
			fn->lastedittime[6]=(int)(nowtime->tm_mday/10);
			fn->lastedittime[7]=nowtime->tm_mday%10;
			fn->lastedittime[8]=(int)(nowtime->tm_hour/10);
			fn->lastedittime[9]=nowtime->tm_hour%10;
			fn->lastedittime[10]=(int)(nowtime->tm_min/10);
			fn->lastedittime[11]=nowtime->tm_min%10;
			fn->lastedittime[12]=(int)(nowtime->tm_sec/10);
			fn->lastedittime[13]=nowtime->tm_sec%10;
			//
			ChangeAttribute(1,fid);
			//		printf("�ļ��ѱ���\n");
			//system("stty cooked");
		}
		return true;
		}
		return true;
}