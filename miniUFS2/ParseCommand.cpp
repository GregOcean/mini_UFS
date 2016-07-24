#include "Global.h"
#include "string.h"
#include "time.h"
#include "math.h"

char *operateList[100]={
	"cd",			//0
	"newdir",		//1
	"deldir",		//2
	"rmdir",		//3
	"cutdir",		//4
	"dr",				//5
	"cpdir",		//6
	"attdir",		//7
	"renamedir",//8
	
	"search",		//9
	"new",         //10
	"cp",				//11
	"cut",			//12
	"rm",			//13
	"del",			//14
	"type",			//15
	"more",		//16
	"edit",			//17
	"att",			//18
	"rc",				//19
	"block",		//20
	"rename",    //21
	


	"tree",			//22
	"fmt",			//23
	"space",		//24
	"deleted",	//25
	"user",			//26
	"close",		//27
	"help"			//28
};


void ParseCmd(char *cmd)
{
	char file1dir[1000],file2dir[1000];
	char option[100];
	char file1nametmp[1000];
	char file2nametmp[1000];
	char filename1[100],extention1[100];
	char filename2[100],extention2[100];
	char OriDir[1000];
	char operate[100];
	

	memset(file1dir,0,sizeof(file1dir));
	memset(file2dir,0,sizeof(file2dir));
	memset(option,0,sizeof(option));
	memset(file1nametmp,0,sizeof(file1nametmp));
	memset(file2nametmp,0,sizeof(file2nametmp));
	memset(filename1,0,sizeof(filename1));
	memset(extention1,0,sizeof(extention1));
	memset(filename2,0,sizeof(filename2));
	memset(extention2,0,sizeof(extention2));
	memset(OriDir,0,sizeof(OriDir));
	memset(operate,0,sizeof(operate));

	if (cmd[0]==0||cmd[0]=='\n')
	{
		return;
	}

	sscanf(cmd,"%s",operate);

	int oid=GetOperateID(operate);
	if (oid==-1)
	{
		printf("命令错误，请重新输入。输入HELP来查看帮助。\n\n");
		return;
	}

	cmd=cmd+strlen(operate);
	while(*cmd&&*cmd==' ')
		cmd++;

	if (*cmd=='-')
	{
		sscanf(cmd,"-%s",option);
		cmd=cmd+strlen(option)+1;
		while(*cmd&&*cmd==' ')
			cmd++;
	}

	if (*cmd)
	{
		if (*cmd=='-')
		{
			printf("错误：一个命令只能带有命令选项，请重新输入。\n");
			return;
		}
		sscanf(cmd,"%s",file1dir);
		cmd=cmd+strlen(file1dir);
		while(*cmd&&*cmd==' ')
			cmd++;
		if (*cmd)
		{
			if (*cmd=='-')
			{
				printf("错误：指令选项位置错误，请重新输入。\n");
				return;
			}
			sscanf(cmd,"%s",file2dir);
		}

	}

	strcpy(OriDir,NowDirRoute);

	if (oid<9) //文件夹相关命令
	{
		if (oid!=1&&oid!=5&&file1dir[0]==0)
		{
			printf("错误：命令需要参数，请重新输入.\n");
			return;
		}
		char *p=file1dir+strlen(file1dir);
		if (oid!=5) 
		{
			if (*(p-1)=='\\')
			{
				p--;
				*p=0;
			}
		}
		else
		{
			if (strchr(file1dir,'\\'))
			{
				printf("Dir 命令只针对当前目录。\n");
				return;
			}
		}


		if (oid==1||oid==8||oid==4||oid==6)
		{
			while(p!=file1dir)
			{
				if (*p=='\\')
				{
					break;
				}
				p--;
			}
			if (p!=file1dir)
			{
				p++;
				sscanf(p,"%s",filename1);
				p--; 
			}
			else{
				sscanf(p,"%s",filename1);
			}
			*p=0;
		}

		if (oid==8||oid==4||oid==6)
		{
			p=file2dir+strlen(file2dir);
			while(p!=file2dir)
			{
				if (*p=='\\')
				{
					break;
				}
				p--;
			}
			if (p!=file2dir)
			{
				p++;
				sscanf(p,"%s",filename2);
				p--; 
			}
			else{
				sscanf(p,"%s",filename2);
			}
			*p=0;
		}


		if (oid==5&&file1dir[0])
		{
			char *p=strchr(file1dir,'.');
			if (p!=NULL)
			{
				strcpy(extention1,p+1);
				*p=0;
				strcpy(filename1,file1dir);

				ReplaceStr(filename1,"*","._");
				ReplaceStr(filename1,"._",".*");
				ReplaceStr(filename1,"?",".");

				ReplaceStr(extention1,"*","._");
				ReplaceStr(extention1,"._",".*");
				ReplaceStr(extention1,"?",".");

				str2Reg(filename1);
				str2Reg(extention1);

			}
			else
			{
				char tmp[1000]="(.*";
				strcat(tmp,file1dir);
				strcat(tmp,")?.*");

				str2Reg(tmp);
				strcpy(filename1,tmp);
				strcpy(extention1,tmp);

			}

		}
		
		
	}

	else if (oid<=21) //文件相关命令
	{
		if (oid!=10&&oid!=19&&!file1dir[0])
		{
			printf("错误：命令需要参数，请重新输入.\n");
			return;
		}


		if (oid!=11)
		{
			char *p;

			if (file1dir[0])
			{
				p=file1dir+strlen(file1dir);
				while(p!=file1dir)
				{
					if (*p=='\\')
					{
						break;
					}
					p--;
				}

				if (p==file1dir+strlen(file1dir))
				{
					printf("错误：文件名不能为空.\n");
					return;
				}

				if (p!=file1dir)
				{
					p++;
					sscanf(p,"%s",file1nametmp);
					p--;
				}
				else{
					sscanf(p,"%s",file1nametmp);
				}
				*p=0;

				if (file1nametmp[0]=='.')
				{
					printf("错误：文件名不能为空.\n");
					return;
				}

				p=file1nametmp+strlen(file1nametmp);
				while(p!=file1nametmp)
				{
					if (*p=='.')
					{
						break;
					}
					p--;
				}

				if (p==file1nametmp||p==file1nametmp+strlen(file1nametmp)-1)
				{
					printf("错误：文件扩展名不能为空。\n");
					return;
				}

				sscanf(file1nametmp,"%[^.]%*c%s",filename1,extention1);
				if (strlen(filename1)>8)
				{
					printf("错误：文件名长度超过限制。\n");
					return;
				}
				if (strlen(extention1)>3)
				{
					printf("错误：扩展名长度超过限制。\n");
					return;
				}
		}

			if (file2dir[0])
			{
				p=file2dir+strlen(file2dir);
				while(p!=file2dir)
				{
					if (*p=='\\')
					{
						break;
					}
					p--;
				}

				if (p==file2dir+strlen(file2dir))
				{
					printf("错误：文件名不能为空.\n");
					return;
				}

				if (p!=file2dir)
				{
					p++;
					sscanf(p,"%s",file2nametmp);
					p--;
				}
				else{
					sscanf(p,"%s",file2nametmp);
				}
				*p=0;


				if (file2nametmp[0]=='.')
				{
					printf("错误：文件名不能为空.\n");
					return;
				}

				p=file2nametmp+strlen(file2nametmp);
				while(p!=file2nametmp)
				{
					if (*p=='.')
					{
						break;
					}
					p--;
				}

				if (p==file2nametmp||p==file2nametmp+strlen(file2nametmp)-1)
				{
					printf("错误：文件扩展名不能为空。\n");
					return;
				}

				sscanf(file2nametmp,"%[^.]%*c%s",filename2,extention2);
				if (strlen(filename2)>8)
				{
					printf("错误：文件名长度超过限制。\n");
					return;
				}
				if (strlen(extention2)>3)
				{
					printf("错误：扩展名长度超过限制。\n");
					return;
				}

			}

		}

		

	}

	else	if(oid<28)			//无参命令
	{
		if (file1dir[0])
		{
			printf("警告：命令不接收参数，参数将被忽略.\n");
		}
	}
	else
	{

	}

	char tmp[100],ccmd[100];
	switch (oid)
	{
	case 0:
		ChangeNowDir(file1dir);
		if (file2dir[0])
		{
			printf("警告：命令不接收两个参数，第二个参数将被忽略.\n");
		}
		break;

	case 1:
		ChangeNowDir(file1dir);
		if (filename1[0]==0)
		{
			char tmp1[20];
			strcpy(tmp1,"新建");
			for (int i=1;i<1000;i++)
			{
				sprintf(filename1,"%s%d",tmp1,i);
				int fid;
				fid=GetDirID(1,filename1);
				if(fid==-1)
					break;
			}
		}
		if(New(2,filename1,0))
			printf("文件夹 %s 创建成功。\n",filename1);
		ChangeNowDir(OriDir);
		break;

	case 2:case 3:
		if (Delete(2,file1dir,0))
		{
			printf("文件夹删除成功.\n");
		}
		break;

	case 4:
		if (filename2[0]==0)
		{
			printf("错误：请输入目标文件夹路径.\n");
			return;
		}
		ChangeNowDir(file1dir);
		int fidsource;
		fidsource=GetDirID(1,filename1);

		if (fidsource==-1)
		{
			printf("找不到该文件夹。\n");
			return;
		}

		if (file2dir[0]==0)
		{
			ChangeNowDir(OriDir);
		}
		else
		{
			ChangeNowDir(file2dir);
		}

		int fidDest;
		fidDest=GetDirID(1,filename2);

		if (fidDest!=-1)
		{
			printf("目标文件夹已存在，是否替换？yes(y) no(n) :");
			char c;
			c=getchar();
			while(c=='\n')
			{
				c=getchar();
			}
			getchar();
			if (c=='y')
			{
				Delete(2,filename2,0);
			}
			else
			{
				printf("文件夹剪切失败。\n");
			}
		}
		New(2,filename2,0);
		fidDest=GetDirID(1,filename2);

		cut(2,fidsource,fidDest);
		ChangeNowDir(OriDir);

		break;
		break;


	case 5:
		
		if (filename1[0])
		{
			Dir(filename1,extention1);
		}
		else
		{
			ChangeNowDir(NowDirRoute);
			printf("%s\\ 的目录 \n\n",NowDirRoute);
			Dir(0,0);
		}
		break;

	case 6:
		if (filename2[0]==0)
		{
			printf("错误：请输入目标文件夹路径.\n");
			return;
		}
		ChangeNowDir(file1dir);
		fidsource=GetDirID(1,filename1);

		if (fidsource==-1)
		{
			printf("找不到该文件夹。\n");
			return;
		}

		if (file2dir[0]==0)
		{
			ChangeNowDir(OriDir);
		}
		else
		{
			ChangeNowDir(file2dir);
		}

		fidDest=GetDirID(1,filename2);

		if (fidDest!=-1)
		{
			printf("目标文件夹已存在，是否替换？yes(y) no(n) :");
			char c;
			c=getchar();
			while(c=='\n')
			{
				c=getchar();
			}
			getchar();
			if (c=='y')
			{
				Delete(2,filename2,0);
			}
			else
			{
				printf("文件夹剪切失败。\n");
			}
		}
		New(2,filename2,0);
		fidDest=GetDirID(1,filename2);

		cpdir(fidsource,fidDest);
		ChangeNowDir(OriDir);

		break;
		break;

	case 7:
		//ChangeNowDir(file1dir);
		DisplayAttribute(2,file1dir,0);
		//ChangeNowDir(OriDir);
		break;

	case 8:  
		
		if (filename2[0]==0)
		{
			printf("错误：请输入目标文件夹名。\n");
			return;
		}
		if (strchr(filename2,'\\'))
		{
			printf("错误：目标文件夹名非法。\n");
			return;
		}
		ChangeNowDir(file1dir);
		int fid;
		fid=GetDirID(1,filename1);
		if (fid==-1)
		{
			printf("错误：找不到该文件夹。\n");
		}
		if(rename(2,fid,filename2,0))
			printf("文件夹重命名成功。\n");
		ChangeNowDir(OriDir);

		break;

	case 9:
		if (file1dir[0])
		{
			printf("警告：文件名不需要指定目录。目录将被忽略。\n");
		}
		printf("找到的文件有：\n\n");
			ChangeNowDir(NowDirRoute);
			ReplaceStr(filename1,"*","._");
			ReplaceStr(filename1,"._",".*");
			ReplaceStr(filename1,"?",".");

			ReplaceStr(extention1,"*","._");
			ReplaceStr(extention1,"._",".*");
			ReplaceStr(extention1,"?",".");

			str2Reg(filename1);
			str2Reg(extention1);
			Search(filename1,extention1);
			printf("\n");
		break;

	case 10:
		ChangeNowDir(file1dir);
		if (filename1[0]==0)
		{
			int fid;
			char tmpname[14];
			strcpy(tmpname,"新建");
			char tmp2[14];
			strcpy(extention1,"txt");

			for (int i=1;i<1000;i++)
			{
				sprintf(tmp2,"%s%d",tmpname,i);
				fid=GetFileID(tmp2,extention1);
				if (fid==-1)
				{
					strcpy(filename1,tmp2);
					break;
				}
			}
		}
		if (New(1,filename1,extention1))
		{
			printf("文件 %s.%s 创建成功。\n",filename1,extention1);
		}
		ChangeNowDir(OriDir);
		break;

	case 11:
		int copysize;
		if (!file1dir[1])
		{
			printf("错误：命令需要两个参数。\n");
			return;
		}
		isEditing=true;
		
		printf("复制中，请稍候.\n");
		clock_t clocks,clocke;

		char filename11[100],extention11[100];
		char filename22[100],extention22[100];
		if (strchr(file1dir,':'))
		{
			char *p=strlen(file2dir)+file2dir;
			while(p!=file2dir)
			{
				if (*p=='\\')
				{
					break;
				}
				p--;
			}
			if (p!=file2dir)
			{
				p++;
				sscanf(p,"%[^.]%*c%s",filename11,extention11);
				p--;
				*p=0;
				if (strlen(filename11)>8)
				{
					printf("错误：目标文件名长度超出限制。\n");
					isEditing=false;
					return;
				}
				if (strlen(extention11)>3)
				{
					printf("错误：目标文件扩展名长度超限。\n");
					isEditing=false;
					return;
				}
				ChangeNowDir(file2dir);
			}
			else
			{
				sscanf(p,"%[^.]%*c%s",filename11,extention11);
				if (strlen(filename11)>8)
				{
					printf("错误：目标文件名长度超出限制。\n");
					isEditing=false;
					return;
				}
				if (strlen(extention11)>3)
				{
					printf("错误：目标文件扩展名长度超限。\n");
					isEditing=false;
					return;
				}
			}
			clocks=clock();
			copysize=Copy(3,file1dir,0,filename11,extention11);
			clocke=clock();
		}
		else if (strchr(file2dir,':'))
		{
			char *p=strlen(file1dir)+file1dir;
			while(p!=file1dir)
			{
				if (*p=='\\')
				{
					break;
				}
				p--;
			}
			if (p!=file1dir)
			{
				p++;
				sscanf(p,"%[^.]%*c%s",filename11,extention11);
				p--;
				*p=0;
				ChangeNowDir(file1dir);
			}
			else
			{
				sscanf(p,"%[^.]%*c%s",filename11,extention11);
			}
			clocks=clock();
			copysize=Copy(2,filename11,extention11,file2dir,0);
			clocke=clock();
		}
		else
		{
			if (!strchr(file1dir,'\\')&&!strchr(file2dir,'\\'))
			{
				sscanf(file1dir,"%[^.]%*c%s",filename11,extention11);
				sscanf(file2dir,"%[^.]%*c%s",filename22,extention22);
				if (strlen(filename22)>8)
				{
					printf("错误：目标文件名长度超出限制。\n");
					isEditing=false;
					return;
				}
				if (strlen(extention22)>3)
				{
					printf("错误：目标文件扩展名长度超限。\n");
					isEditing=false;
					return;
				}
				clocks=clock();
				copysize=Copy(1,filename11,extention11,filename22,extention22);
				clocke=clock();
			}

			else
			{
				char *p=strlen(file1dir)+file1dir;
				while(p!=file1dir)
				{
					if (*p=='\\')
					{
						break;
					}
					p--;
				}
				if (p!=file1dir)
				{
					p++;
					sscanf(p,"%[^.]%*c%s",filename11,extention11);
					p--;
					*p=0;
					ChangeNowDir(file1dir);
				}
				else
				{
					sscanf(p,"%[^.]%*c%s",filename11,extention11);
				}
				char ctmp[100]="c:\\temp\\";
				strcat(ctmp,filename11);
				strcat(ctmp,"_blegtmp.");
				strcat(ctmp,extention11);
				clocks=clock();
				copysize=Copy(2,filename11,extention11,ctmp,0);
				clocke=clock();

				ChangeNowDir(OriDir);

				char *q=strlen(file2dir)+file2dir;
				while(q!=file2dir)
				{
					if (*q=='\\')
					{
						break;
					}
					q--;
				}
				if (q!=file2dir)
				{
					q++;
					sscanf(q,"%[^.]%*c%s",filename11,extention11);
					q--;
					*q=0;
					if (strlen(filename11)>8)
					{
						printf("错误：目标文件名长度超出限制。\n");
						isEditing=false;
						return;
					}
					if (strlen(extention11)>3)
					{
						printf("错误：目标文件扩展名长度超限。\n");
						isEditing=false;
						return;
					}
					ChangeNowDir(file2dir);
				}
				else
				{
					sscanf(q,"%[^.]%*c%s",filename11,extention11);
					if (strlen(filename11)>8)
					{
						printf("错误：目标文件名长度超出限制。\n");
						isEditing=false;
						return;
					}
					if (strlen(extention11)>3)
					{
						printf("错误：目标文件扩展名长度超限。\n");
						isEditing=false;
						return;
					}
				}
				Copy(3,ctmp,0,filename11,extention11);
				char ccmd2[1000];
				strcpy(ccmd2,"del ");
				strcat(ccmd2,ctmp);
				system(ccmd2);
			}
			}

			ChangeNowDir(OriDir);
			if(copysize!=-1)
			{
				printf("文件复制完成。\n");
				double second=((double)clocke-(double)clocks)/CLOCKS_PER_SEC;
				if (fabs(second)<0.001)
				{
					second=0.001;
				}
				printf("文件复制使用时间 %.2f 秒。平均速度为 %.2f M/s\n",second,(copysize/1024/1024)/second);
			}
			isEditing=false;
		break;

		case 12:
			if (filename2[0]==0)
			{
				printf("错误：请输入目标文件路径.\n");
				return;
			}
			ChangeNowDir(file1dir);
			fidsource=GetFileID(filename1,extention1);

			if (fidsource==-1)
			{
				printf("找不到该文件。\n");
				return;
			}

			if (file2dir[0]==0)
			{
				ChangeNowDir(OriDir);
			}
			else
			{
				ChangeNowDir(file2dir);
			}
			
			fidDest=GetFileID(filename2,extention2);

			if (fidDest!=-1)
			{
				printf("目标文件已存在，是否替换？yes(y) no(n) :");
				char c;
				c=getchar();
				while(c=='\n')
				{
					c=getchar();
				}
				getchar();
				if (c=='y')
				{
					Delete(1,filename2,extention2);
				}
				else
				{
					printf("文件剪切失败。\n");
				}
			}
			New(1,filename2,extention2);
			fidDest=GetFileID(filename2,extention2);

			cut(1,fidsource,fidDest);
			ChangeNowDir(OriDir);

			break;

		case 13:case 14:
			
			if (!strchr(filename1,'*')&&!strchr(filename1,'?')
				&&!strchr(extention1,'*')&&!strchr(extention1,'?'))
			{
				ChangeNowDir(file1dir);
				if(Delete(1,filename1,extention1))
					printf("文件删除成功。\n");
				ChangeNowDir(OriDir);
			}
			else
			{
				ReplaceStr(filename1,"*","._");
				ReplaceStr(filename1,"._",".*");
				ReplaceStr(filename1,"?",".");

				ReplaceStr(extention1,"*","._");
				ReplaceStr(extention1,"._",".*");
				ReplaceStr(extention1,"?",".");

				str2Reg(filename1);
				str2Reg(extention1);
				Delete(4,filename1,extention1);
			}
			
			
			break;
		case 15:
			ChangeNowDir(file1dir);
			fid=GetFileID(filename1,extention1);
			Display(1,fid);
			ChangeNowDir(OriDir);
			break;
		case 16:
			ChangeNowDir(file1dir);
			fid=GetFileID(filename1,extention1);
			if (fid==-1)
			{
				printf("目录下找不到该文件。\n");
				return;
			}
			tmp[100];
			memset(tmp,0,100);
			strcat(tmp,"c:\\temp\\");
			strcat(tmp,filename1);
			strcat(tmp,".");
			strcat(tmp,extention1);

			Copy(2,filename1,extention1,tmp,0);
			isEditing=false;
			strcpy(ccmd,"more ");
			strcat(ccmd,tmp);
			system(ccmd);
			char ccmd2[1000];
			strcpy(ccmd2,"del ");
			strcat(ccmd2,tmp);
			system(ccmd2);
			ChangeNowDir(OriDir);
			
			break;
		case 17:
			isEditing=true;
			bool succ;
			succ=false;
			ChangeNowDir(file1dir);
			if (option[0]==0)
			{
				strcpy(option,"a");
			}
			if (!lstrcmpiA("w",option))
			{
				printf("文件将以覆写形式打开。\n");
				succ=Edit(1,filename1,extention1);
			}
			else if (!lstrcmpiA("a",option))
			{
				printf("文件将以追加形式打开。\n");
				succ=Edit(2,filename1,extention1);
			}
			else if (!lstrcmpiA("vim",option))
			{
				printf("文件将使用Vim进行编辑。\n");
				fid=GetFileID(filename1,extention1);
				if (fid==-1)
				{
					printf("目录下找不到该文件。\n");
					return;
				}
				tmp[100];
				memset(tmp,0,100);
				strcat(tmp,"c:\\temp\\");
				strcat(tmp,filename1);
				strcat(tmp,".");
				strcat(tmp,extention1);

				Copy(2,filename1,extention1,tmp,0);
				isEditing=false;
				strcpy(ccmd,"vim ");
				strcat(ccmd,tmp);
				system(ccmd);
				Delete(1,filename1,extention1);
				if (file1dir[0]==0)
				{
					ChangeNowDir(OriDir);
				}
				else
				{
					ChangeNowDir(file1dir);
				}
				
				Copy(3,tmp,0,filename1,extention1);
 				char ccmd2[1000];
 				strcpy(ccmd2,"del ");
 				strcat(ccmd2,tmp);
 				system(ccmd2);
				ChangeNowDir(OriDir);
			}
			else
			{
				printf("警告：选项被忽略。\n");
			}
			if (succ)
			{
				printf("文件已保存。\n");
			}
			
			isEditing=false;
			ChangeNowDir(OriDir);
			break;
		case 18:
			ChangeNowDir(file1dir);
			DisplayAttribute(1,filename1,extention1);
			ChangeNowDir(OriDir);
			break;
		case 19:
			ChangeNowDir(file1dir);
			if (filename1[0]==0)
			{
				while(DeletedNum!=0)
				{
					if (fileIndex[Deleted[DeletedNum-1]].type==t_File)
					{
						break;
					}
					DeletedNum--;
				}
				if (DeletedNum==0)
				{
					printf("回收站中没有文件可恢复。\n");
					return;
				}
				strcpy(filename1,fileIndex[Deleted[DeletedNum-1]].node->filename);
				strcpy(extention1,fileIndex[Deleted[DeletedNum-1]].node->extention);

			}
			recovery(filename1,extention1);
			ChangeNowDir(OriDir);
			break;
		case  20:
			ChangeNowDir(file1dir);
			BlockOfFile(filename1,extention1);
			break;
		case 21:
			if (filename2[0]==0)
			{
				printf("错误：请输入目标文件名。\n");
				return;
			}
			ChangeNowDir(file1dir);
			fid=GetFileID(filename1,extention1);
			if (fid==-1)
			{
				printf("目录下找不到该文件。\n");
				return;
			}
			else
				if(rename(1,fid,filename2,extention2))
					printf("重命名成功。\n");
			//printf("")
			ChangeNowDir(OriDir);
			break;
		case 22:
			if (option[0]==0)
			{
				printf("%s 的文件结构树：\n",NowDirRoute);
				printf(".\n");
				Tree(1,NowDirFid);
			}
			else if (!lstrcmpiA(option,"r"))
			{
				ChangeNowDir("~");
				printf("%s 的文件结构树：\n",NowDirRoute);
				printf("~\n");
				Tree(1,NowDirFid);
				ChangeNowDir(OriDir);
			}
			else
			{
				printf("警告：选项被忽略。\n");
			}
			break;
		case 23:
			if (option[0]==0)
			{
				printf("正在格式化。\n");
				Format(1);
				printf("格式化完成。\n");
			}
			else if (!lstrcmpiA(option,"d"))
			{
				Format(2);

			}
			
			break;
		case 24:
			// #ifdef _1M_
			// 		printf("总空间:  1048576 Bytes.可用空间: %d Bytes.剩余空间: %d Bytes.\n",FDBNum*4096,FreeFDBNum*4096);
			// #endif
#ifdef _1G_
			printf("总空间:  1073741824 Bytes.可用空间: %d Bytes.剩余空间: %d Bytes.\n",FDBNum*4096,FreeFDBNum*4096);
#endif
			break;
		case 25:
			printf("回收站。\n");
			Delete(3,0,0);
			break;
		case 26:
			printf("请输入新用户名：");
			while(1)
			{
				char tmp[100];
				scanf("%s",tmp);
				if (strlen(tmp)<10)
				{
					strcpy(Username,tmp);
					break;
				}
				printf("用户名不能超过 10 个字符，请重新输入新用户名：");
			}


			bool correct;
			correct=false;
			int len;
			len=0;
			char tmp[20];
			char tmp2[20];
			memset(tmp2,0,20);
			memset(tmp,0,20);
			while(!correct)
			{
				printf("请输入新密码：");
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
							printf("\n密码必须小于 10 个字符，请重新输入新密码：");
							len=0;
							memset(tmp,0,20);
							continue;
						}
						else
						{
							printf("\n请再次输入新密码：");
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
						if (!lstrcmpiA(tmp,tmp2))
						{
							printf("\n新密码已确认。\n");
							strcpy(password,tmp);
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
			break;
		case 27:
			Close();
			break;
		case 28:
			if (file1dir[0]==0)
			{
				Help(1,0);
			}
			else
			{
				Help(2,file1dir);
			}
			break;
		default:
			printf("命令错误，请重新输入。输入HELP来查看帮助。\n");
			break;
	}


}