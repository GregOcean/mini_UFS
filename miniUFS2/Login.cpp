#include "Global.h"
#include "conio.h"
#include "ctype.h"

bool Login()
{
	fseek(fpDisk,16,0);
	fread(Username,1,10,fpDisk);
	fread(password,1,10,fpDisk);

	printf("�������û��������롣\n");

	bool flag=false;
	while(flag==false)
	{
		char userin[100];
		char passin[100];
		printf("�������û�����");
		scanf("%s",userin);
		printf("����������  ��");
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
			printf("\n���ڽ���ϵͳ��\n");
			getchar();
			return true;
		}
		printf("\n�û���������������������룺\n");

	}
	return false;
}