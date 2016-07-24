#include "Global.h"
#include "conio.h"
#include "ctype.h"

bool Login()
{
	fseek(fpDisk,16,0);
	fread(Username,1,10,fpDisk);
	fread(password,1,10,fpDisk);

	printf("请输入用户名和密码。\n");

	bool flag=false;
	while(flag==false)
	{
		char userin[100];
		char passin[100];
		printf("请输入用户名：");
		scanf("%s",userin);
		printf("请输入密码  ：");
		memset(passin,0,100);
		int len=0;
		while(1)
		{
			char ch=getch();
			if (!isdigit(ch)&&!isalpha(ch)&&ch!=13)
			{
				continue;
			}
			if (ch==13)
			{
				break;
			}
			else
				passin[len++]=ch;
			printf("*");
		}
		if (!lstrcmpiA(userin,Username)&&!lstrcmpiA(passin,password))
		{
			flag=true;
			printf("\n正在进入系统。\n");
			getchar();
			return true;
		}
		printf("\n用户名或密码错误，请重新输入：\n");

	}
	return false;
}