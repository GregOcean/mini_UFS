#include "Global.h"

void Help(int mode,char *command)
{
	if (mode==1)
	{
		printf("�й�ĳ���������ϸ��Ϣ������� help ������\n\n");
		printf("cd		�����ָ��Ŀ¼��\n");
		printf("new		����һ���µ��ļ�\n");
		printf("newdir		����һ���µ��ļ���\n");
		printf("cp		��һ���ļ����Ƶ���һ��λ��\n");
		printf("cpdir		��һ���ļ��и��Ƶ���һ��λ��\n");
		printf("cut		��һ���ļ����е���һ��λ��\n");
		printf("cutdir		��һ���ļ��м��е���һ��λ��\n");
		printf("rename		������һ���ļ�\n");
		printf("renamedir	������һ���ļ���\n");
		printf("rm		ɾ������һ���ļ�\n");
		printf("rmdir		ɾ������һ���ļ���\n");
		printf("del		ɾ������һ���ļ�\n");
		printf("deldir		ɾ������һ���ļ���\n");
		printf("dr		��ʾ��ǰĿ¼�е��ļ����ļ���\n");
		printf("tree		�����νṹչʾ�ļ�ϵͳ\n");
		printf("type		����ͨ�ı���ʽ��ʾһ���ļ�������\n");
		printf("more		�Է�ҳ�ı���ʽ��ʾһ���ļ�������\n");
		printf("search		�����ļ�ϵͳ�е��ļ���\n");
		printf("fmt		��ʽ������\n");
		printf("space		��ʾ��ǰ���̵Ŀռ�ʹ�����\n");
		printf("att		��ʾһ���ļ��ľ�������\n");
		printf("attdir		��ʾһ���ļ��еľ�������\n");
		printf("rc		�ָ�һ����ɾ���ļ�\n");
		printf("deleted		��ʾ����վ�е������ļ����ļ���\n");
		printf("user		�����û���������\n");
		printf("block		�����ݿ���ʽ��ʾһ���ļ�\n");
		printf("edit		�༭�ļ�����\n");
		printf("rename		������һ���ļ�\n");
		printf("close		�ر�miniUFSϵͳ\n");
		printf("\n");
	}else
	{
		int num1=GetOperateID(command);
		switch (num1)
		{
			case 0:
				printf("�����ָ��Ŀ¼��\n");
				printf("\n");
				printf("CD  [path]\n");
				printf("CD  ~\\[path]\n");
				printf("CD  ..\n\n");
				printf("ʹ��..ָ���ĳɸ�Ŀ¼��\n");
				printf("ʹ��~ָ��Ŀ¼�ľ���·����\n");
				printf("path Ŀ¼�����·��\n\n");
				printf("���� ���� cd ~\\temp ��������temp�ļ�����  \n");
				printf("��ǰ��Ŀ¼�ַ����ᱻת����ʹ�ô������ϵĴ�Сд�����ԣ�\n");
				printf("��������ϵĴ�Сд��ˣ�CD ~\\TEMP �Ὣ��ǰĿ¼��Ϊ~\\Temp��\n\n");
				printf("CD ����ո���Ϊ�ָ���������Ŀ¼���벻Ҫ�����ո�\n");
				printf("\n");
				printf("\n");break;
			case 1:
				printf("����һ���µ��ļ���\n");
				printf("\n");
				printf("newdir [path] [dirname]\n\n");
				printf("path		����·�������·������,����ָ����Ҫɾ���ļ��еľ���λ��\n");
				printf("dirname		�������ļ�������\n");
				printf("�����������ϵͳ��ʹ��Ĭ���ļ����������ļ��С�\n\n");
				printf("�ڵ�ǰĿ¼�´���һ���µ��ļ���\n");
				printf("NEWDIR ����ո���Ϊ�ָ���������Ŀ¼���벻Ҫ�����ո�\n");
				printf("\n");

				printf("\n");break;
			case 2:case 3:
				printf("ɾ������һ���ļ���\n");
				printf("\n");
				printf("deldir [path] dirname\n\n");
				printf("path		����·�������·������,����ָ����Ҫɾ���ļ��еľ���λ��\n");
				printf("dirname		��Ҫɾ�����ļ������ƣ�֧��ʹ��ͨ�����\n\n");
				printf("������ļ����Լ���������ļ��к��ļ�һ��ɾ��\n");
				printf("DELDIR ����ո���Ϊ�ָ���������Ŀ¼���벻Ҫ�����ո�\n");
				printf("\n");
				printf("\n");break;
			case 4:
				printf("��һ���ļ��м��е���һ��λ��\n");
				printf("\n");
				printf("cutdir [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2		����·�������·������,����ָ���ļ��еľ���λ�� \n\n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
				printf("ִ�гɹ����ļ���1�ᱻɾ��\n");
				printf("CUTDIR ����ո���Ϊ�ָ���������Ŀ¼���벻Ҫ�����ո�\n\n");
				printf("\n");
				printf("\n");break;
			case 5:
				printf("��ʾ��ǰĿ¼�е��ļ����ļ���\n");
				printf("\n");
				printf("dr [filename]\n\n");
				printf("filename ָ��Ҫ�г����ļ�����֧��������ʽ��\n\n");
				printf("������ִ�гɹ�������Ļ���г���ǰĿ¼�µ������ļ����ļ���\n\n");			
				printf("�ļ����ļ��н����ļ�����ĸ˳������\n");		
				printf("\n");
				printf("\n");break;
			case 6:
				printf("��һ���ļ��и��Ƶ���һ��λ��\n");
				printf("\n");
				printf("cpdir [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2		����·�������·������,����ָ���ļ��еľ���λ�� \n\n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
				printf("\nCPDIR ����ո���Ϊ�ָ���������Ŀ¼���벻Ҫ�����ո�\n\n");
				printf("\n");
				printf("\n");break;
			case 7:
				printf("��ʾһ���ļ��еľ�������\n");
				printf("\n");
				printf("attdir [path]dirname\n\n");
				printf("path  ����·�������·������,����ָ���ļ��еľ���λ�� \n\n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
				printf("ִ�гɹ��󽫻���ʾ�ļ��е����ԣ���ɶ���д��\n");
				printf("\n");
				printf("\n");break;
			case 8:
				printf("�������ļ��С�\n\n");
				printf("renamedir [path]dirname\n\n");
				printf("path  ����·�������·������,����ָ���ļ��еľ���λ�� \n\n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
				printf("\n");break;
			case 9:
				printf("���ļ�ϵͳ�������ļ���\n");
				printf("search [path]filename\n\n");
				printf("path  ����·�������·������,����ָ���ļ��еľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
				printf("filenameָ��Ҫ�������ļ�����֧��ʹ��������ʽ��\n");
			printf("\n");break;
			case 10:
				printf("����һ���µ��ļ�\n");
				printf("new [path][filename]\n\n");
				printf("path  ����·�������·������,����ָ�������ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼�´����ļ�\n");
				printf("filename �������ļ�����\n");
				printf("�粻��дϵͳ����Ĭ���ļ��������ļ���\n");
				printf("\n");
				printf("\n");break;
			case 11:
				printf("��һ���ļ����Ƶ���һ��λ��\n");
				printf("\n");
				printf("cp [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2 ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
				printf("\n");
				printf("\n");break;
			case 12:
				printf("��һ���ļ����е���һ��λ��\n");
				printf("\n");
				printf("cut [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2 ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
				printf("ִ�гɹ����ļ�1�ᱻɾ��\n");
				printf("\n");
				printf("\n");break;
			case 13:case 14:
				printf("ɾ������һ���ļ�\n");
				printf("\n");
				printf("rm [path]filename\n\n");
				printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("filename ��Ҫɾ�����ļ�����,֧��ʹ��ͨ�����\n\n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
				printf("\n");
				printf("\n");break;
			case 15:
				printf("����ͨ�ı���ʽ��ʾһ���ļ�������\n");
				printf("\n");
				printf("type [path]filename\n\n");
				printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
				printf("filename ��Ҫ��ʾ���ļ�����\n\n");
				printf("ִ�гɹ��󽫻��ָ���ļ��е������������Ļ��\n");
				printf("\n");
				printf("\n");break;
			case 16:
				printf("�Է�ҳ�ı���ʽ��ʾһ���ļ�������\n");
				printf("\n");
				printf("more [path]filename\n\n");
				printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
				printf("filename ��Ҫ��ʾ���ļ�����\n\n");
				printf("ִ�гɹ��󽫻��ָ���ļ��е������Է�ҳ��ʽ�������Ļ��\n");
				printf("\n");
				printf("\n");break;
			case 17:
				printf("�༭�ļ�����\n");
				printf("\n");
				printf("edit [-option] [path]filename \n\n");
				printf("���� option��\n\n");
				printf("	-w : �Ը�д��ʽ���ļ���\n");
				printf("	-a : ��׷����ʽ���ļ���\n");
				printf("	-vim : ʹ��Vim���ļ���\n");
				printf("	��������ѡ����Ĭ��ʹ�� -a ѡ�\n\n");
				printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
				printf("filename ��Ҫ�༭���ļ�����\n");
				printf("ִ�гɹ��󣬿��Լ�����д���ļ��е�����\n\n");
				printf("ʹ�� -w �� -a ѡ��ʱ��Ҫ�����༭��CTRL + C\n");
				printf("\n");
				printf("\n");break;
			case 18:
				printf("��ʾһ���ļ��ľ�������\n");
				printf("\n");
				printf("attdir [path]filename\n");
				printf("path  ����·�������·������,����ָ���ļ��еľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
				printf("ִ�гɹ��󽫻���ʾ�ļ������ԣ���ɶ���д��\n");
				printf("\n");
				printf("\n");break;
			case 19:
				printf("�ָ�һ����ɾ���ļ�\n");
				printf("\n");
				printf("rc [filename]\n\n");
				printf("filename ��Ҫ�ָ��ļ�������\n");
				printf("�粻��д�����ָ����һ��ɾ�����ļ�\n");
				printf("ִ�гɹ����ļ�����ָ�ɾ��ǰ״̬\n");
				printf("\n");
				printf("\n");break;
			case 20:
				printf("��ʾһ���ļ���ʹ�õ����ݿ�\n");
				printf("\n");
				printf("block [path]filename\n");
				printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n");
				printf("filename ��Ҫ��ʾ���ļ�����\n");
				printf("ִ�гɹ��󽫻��ָ���ļ��е����������ݿ���ʽ�������Ļ��\n");
				printf("\n");
				printf("\n");break;
			case 21:
				printf("������һ���ļ�\n");
				printf("\n");
				printf("rename [path]filename1 filename2\n\n");
				printf("path  ����·�������·������,����ָ���ļ��ľ���λ�� \n");
				printf("�粻��д��Ĭ��Ϊ��ǰĿ¼��\n\n");
				printf("filename1 ��Ҫ���������ļ�����\n\n");
				printf("filename2 ���ĺ���ļ�����\n\n");
				printf("ִ�гɹ��󽫻���ļ����������������\n");
				printf("\n");
				printf("\n");break;
			case 22:
				printf("�����νṹչʾ�ļ�ϵͳ\n");
				printf("\n");
				printf("tree [-option]\n\n");
				printf("���� option:\n");
				printf("	-r : �����νṹչʾ�����ļ�ϵͳ\n");
				printf("	-n : �����νṹչʾ��ǰĿ¼�ļ�ϵͳ\n");
				printf("	�����дѡ����Ĭ��ʹ�� -n ѡ�\n\n");
				printf("ִ������tree�󣬽�����������ʽ���ļ�ϵͳ�������Ļ��\n");
				printf("\n");
				printf("\n");break;
			case 23:
				printf("��ʽ������\n");
				printf("\n");
				printf("fmt [-option]\n\n");
				printf("���� option:\n");
				printf("	-d : �ͼ���ʽ��\n");
				printf("	-n : ��ͨ��ʽ��\n");
				printf("	�����дѡ����Ĭ��ʹ�� -n ѡ�\n\n");
				printf("ִ�гɹ��󣬽����ʽ���������̿ռ䣬�������������ļ�\n");
				printf("ϵͳ�ļ��Ƚ����ָ����״̬\n");
				printf("\n");
				printf("\n");break;
			case 24:
				printf("��ʾ��ǰ���̵Ŀռ�ʹ�����\n");
				printf("\n");
				printf("space\n");
				printf("ִ�гɹ��󣬽�����ʾ��ǰ���̿ռ��ʹ���������Ļ��\n");
				printf("\n");
				printf("\n");break;
			case 25:
				printf("��ʾ����վ�е������ļ����ļ���\n");
				printf("\n");
				printf("deleted\n");
				printf("ִ�гɹ��󣬽�����ʾ���л���վ�е��ļ����ļ������Ƶ���Ļ��\n");
				printf("\n");
				printf("\n");break;
			case 26:
				printf("�����û���������\n");
				printf("\n");
				printf("user\n");
				printf("ִ�гɹ��󣬽��������һ������\n");
				printf("���ݲ�������û������������������\n");
				printf("\n");
				printf("\n");break;
			case 27:
				printf("�ر�miniUFSϵͳ\n");
				printf("\n");
				printf("close\n");
				printf("ִ�гɹ��󣬽���ر�miniUFSϵͳ\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");break;
			default:
				printf("�Ҳ�����Ӧ���\n");
				printf("��ǰ֧���������£�\n\n");
				Help(1,0);

		}

	}
}