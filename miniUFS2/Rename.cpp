#include "Global.h"
#include "string.h"
bool rename(int mode,int fid,char *filename,char *extention)
{
	if (mode==1)
	{
		//�ж����������������
		char c;
		char d[3]={"_2"};
		FileNode *fn=fileIndex[fid].node;
		int fiddest=GetFileID(filename,extention);
		if(fiddest!=-1)   //��ʾ���������ļ��������ġ�
		{
			printf("���ļ����Ѵ���,�Ƿ����Ϊ%s_2.%s\n",filename,extention);
			printf("���������ѡ��yes(y),no(n)     ");
			c=getchar();
			if(c=='n')
			{
				printf("������ʧ��\n");
				getchar();    //���߻��С�
				return false;
			}
			else if(c=='y')
			{
				strcpy(fn->filename,filename);
				strcat(fn->filename,d);
				strcpy(fn->extention,extention);
				getchar();
				ChangeAttribute(1,fid);
			}
		}
		else  //û���������ļ���
		{
			strcpy(fn->filename,filename);
			strcpy(fn->extention,extention);
			ChangeAttribute(1,fid);
			return true;
		}
	}
	else
	{
		//�ж����������������
		char c;
		char d[3]={"_2"};
		FileNode *fn=fileIndex[fid].node;
		int fiddest=GetDirID(1,filename);
		if(fiddest!=-1)   //��ʾ���������ļ��������ġ�
		{
			printf("���ļ������Ѵ���,�Ƿ����Ϊ%s_2\n",filename);
			printf("���������ѡ��yes(y),no(n)     ");
			c=getchar();
			if(c=='n')
			{
				printf("������ʧ��\n");
				getchar();    //���߻��С�
				return false;
			}
			else if(c=='y')
			{
				strcpy(fn->filename,filename);
				strcat(fn->filename,d);
				getchar();
				ChangeAttribute(2,fid);
			}
		}
		else  //û���������ļ���
		{
			strcpy(fn->filename,filename);
			ChangeAttribute(2,fid);
			return true;
		}
	}
	return true;
}