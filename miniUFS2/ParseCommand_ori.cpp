#include "Global.h"
#include <string.h>
#include "conio.h"
#include "ctype.h"

bool ParseCmd(char *cmd)
{
	char operate[100];
	sscanf(cmd,"%s",operate);




	if (!strcmp(operate,"fmt"))
	{
		printf("Disk Formating. Please Wait.\n");
		Format();
		printf("Disk Format Compleated.\n");
	}
	else if (!strcmp(operate,"dr"))
	{
		printf("%s\\ ��Ŀ¼ \n\n",NowDirRoute);

		Dir();
	}
	else if (!strcmp(operate,"cp"))
	{
		isEditing=true;
		printf("�����У����Ժ�.\n");
		char file1[1000],file2[1000];

		sscanf(cmd,"%*s %s %s",file1,file2);

		//char dir[1000];
		//char filename[10],extention[4];
		//sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);


		char filename[10],extention[4];
		char filename2[10],extention2[4];
		if (strchr(file1,':'))
		{
			char *p=strlen(file2)+file2;
			while(p!=file2)
			{
				if (*p=='\\')
				{
					break;
				}
				p--;
			}
			if (p!=file2)
			{
				p++;
				sscanf(p,"%[^.]%*c%s",filename,extention);
				p--;
				*p=0;
				ChangeNowDir(file2);
			}
			else
			{
				sscanf(p,"%[^.]%*c%s",filename,extention);
			}
			//sscanf(file2,"%[^.]%*c%s",filename,extention);
			Copy(3,file1,0,filename,extention);
		}
		else if (strchr(file2,':'))
		{
			char *p=strlen(file1)+file1;
			while(p!=file1)
			{
				if (*p=='\\')
				{
					break;
				}
				p--;
			}
			if (p!=file1)
			{
				p++;
				sscanf(p,"%[^.]%*c%s",filename,extention);
				p--;
				*p=0;
				ChangeNowDir(file1);
			}
			else
			{
				sscanf(p,"%[^.]%*c%s",filename,extention);
			}
			//sscanf(file2,"%[^.]%*c%s",filename,extention);
			Copy(2,filename,extention,file2,0);
		}
		else
		{
			if (!strchr(file1,'\\')&&!strchr(file2,'\\'))
			{
				sscanf(file1,"%[^.]%*c%s",filename,extention);
				sscanf(file2,"%[^.]%*c%s",filename2,extention2);
				Copy(1,filename,extention,filename2,extention2);
			}

			else
			{
				char *p=strlen(file1)+file1;
				while(p!=file1)
				{
					if (*p=='\\')
					{
						break;
					}
					p--;
				}
				if (p!=file1)
				{
					p++;
					sscanf(p,"%[^.]%*c%s",filename,extention);
					p--;
					*p=0;
					ChangeNowDir(file1);
				}
				else
				{
					sscanf(p,"%[^.]%*c%s",filename,extention);
				}
				char ctmp[100]="c:\\";
				strcat(ctmp,filename);
				strcat(ctmp,"_blegtmp.");
				strcat(ctmp,extention);
				Copy(2,filename,extention,ctmp,0);

				ChangeNowDir(OriDir);

				char *q=strlen(file2)+file2;
				while(q!=file2)
				{
					if (*q=='\\')
					{
						break;
					}
					q--;
				}
				if (q!=file2)
				{
					q++;
					sscanf(q,"%[^.]%*c%s",filename,extention);
					q--;
					*q=0;
					ChangeNowDir(file2);
				}
				else
				{
					sscanf(q,"%[^.]%*c%s",filename,extention);
				}

				Copy(3,ctmp,0,filename,extention);
				//ChangeNowDir(OriDir);

			}
			
		}
		ChangeNowDir(OriDir);
		printf("�ļ�������ɡ�\n");
		isEditing=false;
	}
	else if (!strcmp(operate,"user"))
	{
		printf("���������û�����");
		while(1)
		{
			char tmp[100];
			scanf("%s",tmp);
			if (strlen(tmp)<10)
			{
				strcpy(Username,tmp);
				break;
			}
			printf("�û������ܳ��� 10 ���ַ����������������û�����");
		}
		
		
		bool correct=false;
		int len=0;
		char tmp[20];
		char tmp2[20];
		memset(tmp2,0,20);
		memset(tmp,0,20);
		while(!correct)
		{
			printf("�����������룺");
			while(1)
			{			
				char ch=getch();
				if (!isdigit(ch)&&!isalpha(ch)&&ch!=13)
				{
					continue;
				}
				if (ch==13)
				{
					if (len>=10)
					{
						printf("\n�������С�� 10 ���ַ������������������룺");
						len=0;
						memset(tmp,0,20);
						continue;
					}
					else
					{
						printf("\n���ٴ����������룺");
						len=0;
						break;
					}
				}
				else
				{
					tmp[len++]=ch;
					printf("*");
				}
				
			}

			while(1)
			{			
				char ch=getch();
				if (!isdigit(ch)&&!isalpha(ch)&&ch!=13)
				{
					continue;
				}
				if (ch==13)
				{
					if (!strcmp(tmp,tmp2))
					{
						printf("\n��������ȷ�ϡ�\n");
						getchar();
						correct=true;
						break;
					}
					else
					{
						   break;
					}
				}
				tmp2[len++]=ch;
				printf("*");
			}
		}

	}
	else if(!strcmp(operate,"rm"))
	{
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}

		bool succ=Delete(1,filename,extention);
		if(succ)
			printf("һ���ļ��ѱ�ɾ��.\n");
		ChangeNowDir(OriDir);
	}

	else if (!strcmp(operate,"block"))
	{
		printf("�ļ���ʹ�õ����ݿ��У�\n");
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}

		BlockOfFile(filename,extention);
		ChangeNowDir(OriDir);
	}

	else if (!strcmp(operate,"rmdir"))
	{
		char dir[1000];
		sscanf(cmd,"%*s %s",dir);
		bool succ=Delete(2,dir,0);
		if (succ)
		{
			printf("һ���ļ����ѱ�ɾ��.\n");
		}
	}
	else if (!strcmp(operate,"deleted"))
	{
		printf("����վ��\n");
		Delete(3,0,0);
	}
	else if (!strcmp(operate,"type"))
	{
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}
		int fid=GetFileID(filename,extention);
		Display(1,fid);

		ChangeNowDir(OriDir);
	}
	else if (!strcmp(operate,"more"))
	{
		/*
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}
		
		int fid=GetFileID(filename,extention);
		Display(2,fid);

		ChangeNowDir(OriDir);
		*/
		//system("dir");
		char filename[10],extention[4];
		sscanf(cmd,"%*s %[^.]%*c%s",filename,extention);
		char tmp[100];
		memset(tmp,0,100);
		strcat(tmp,"c:\\");
		strcat(tmp,filename);
		strcat(tmp,".");
		strcat(tmp,extention);
		Copy(2,filename,extention,tmp,0);
		char ccmd[100]="more ";
		strcat(ccmd,tmp);
		system(ccmd);
		
	}
	else if(!strcmp(operate,"att"))
	{
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}

		DisplayAttribute(filename,extention);

		ChangeNowDir(OriDir);
	}
	else if (!strcmp(operate,"help"))
	{

	}
	else if (!strcmp(operate,"cd"))
	{
		char Dir[1000];
		sscanf(cmd,"%*s %s",Dir);
		ChangeNowDir(Dir);
	}
	else if (!strcmp(operate,"close"))
	{
		Close();
	}
	else if (!strcmp(operate,"new"))
	{
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}

		bool succ=New(1,filename,extention);
		if (succ)
		{
			printf("�ļ������ɹ���\n");
		}

		ChangeNowDir(OriDir);
		
	}
	else if (!strcmp(operate,"aaa"))
	{
		printf("%d\n",TotalFileNum);
		printf("%s\n",NowDirRoute);
	}
	else if (!strcmp(operate,"newdir"))
	{
		char filename[10];
		sscanf(cmd,"%*s %s",filename);
		bool succ=New(2,filename,0);
		if (succ)
		{
			printf("Ŀ¼�����ɹ���\n");
		}
	}
	else if (!strcmp(operate,"editw"))
	{
		isEditing=true;
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}
		
		Edit(1,filename,extention);
		printf("1      Files Saved.\n");

		ChangeNowDir(OriDir);
		isEditing=false;
	}


	else if (!strcmp(operate,"edita"))
	{
		isEditing=true;
		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}

		Edit(2,filename,extention);
		printf("1      Files Saved.\n");

		ChangeNowDir(OriDir);
		isEditing=false;
	}

	else if (!strcmp(operate,"rc"))
	{

		char dir[1000];
		char filename[10],extention[4];
		sscanf(cmd,"%*s %s",dir);

		char OriDir[1000];
		strcpy(OriDir,NowDirRoute);
		char *p=strlen(dir)+dir;
		while(p!=dir)
		{
			if (*p=='\\')
			{
				break;
			}
			p--;
		}
		if (p!=dir)
		{
			p++;
			sscanf(p,"%[^.]%*c%s",filename,extention);
			p--;
			*p=0;
			ChangeNowDir(dir);
		}
		else
		{
			sscanf(p,"%[^.]%*c%s",filename,extention);
		}

		recovery(filename,extention);
		printf("�ļ��ѻָ���\n");
		ChangeNowDir(OriDir);
	}
	else if (!strcmp(operate,"space"))
	{
// #ifdef _1M_
// 		printf("�ܿռ�:  1048576 Bytes.���ÿռ�: %d Bytes.ʣ��ռ�: %d Bytes.\n",FDBNum*4096,FreeFDBNum*4096);
// #endif
#ifdef _1G_
		printf("�ܿռ�:  1073741824 Bytes.���ÿռ�: %d Bytes.ʣ��ռ�: %d Bytes.\n",FDBNum*4096,FreeFDBNum*4096);
#endif
		
	}
	else if (!strcmp(operate,"tree"))
	{
		printf("%s ���ļ��ṹ����\n",NowDirRoute);
		printf(".\n");
		Tree(1,NowDirFid);
	}
	else
	{
		printf("illegal instruction\n");
	}
	return true;
}