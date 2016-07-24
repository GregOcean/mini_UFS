#include "Global.h"

void Help(int mode,char *command)
{
	if (mode==1)
	{
		printf("有关某个命令的详细信息，请键入 help 命令名\n\n");
		printf("cd		变更到指定目录下\n");
		printf("new		创建一个新的文件\n");
		printf("newdir		创建一个新的文件夹\n");
		printf("cp		将一个文件复制到另一个位置\n");
		printf("cpdir		将一个文件夹复制到另一个位置\n");
		printf("cut		将一个文件剪切到另一个位置\n");
		printf("cutdir		将一个文件夹剪切到另一个位置\n");
		printf("rename		重命名一个文件\n");
		printf("renamedir	重命名一个文件夹\n");
		printf("rm		删除至少一个文件\n");
		printf("rmdir		删除至少一个文件夹\n");
		printf("del		删除至少一个文件\n");
		printf("deldir		删除至少一个文件夹\n");
		printf("dr		显示当前目录中的文件和文件夹\n");
		printf("tree		以树形结构展示文件系统\n");
		printf("type		以普通文本形式显示一个文件的内容\n");
		printf("more		以分页文本形式显示一个文件的内容\n");
		printf("search		搜索文件系统中的文件。\n");
		printf("fmt		格式化磁盘\n");
		printf("space		显示当前磁盘的空间使用情况\n");
		printf("att		显示一个文件的具体属性\n");
		printf("attdir		显示一个文件夹的具体属性\n");
		printf("rc		恢复一个已删除文件\n");
		printf("deleted		显示回收站中的所有文件和文件夹\n");
		printf("user		更改用户名和密码\n");
		printf("block		用数据块形式显示一个文件\n");
		printf("edit		编辑文件功能\n");
		printf("rename		重命名一个文件\n");
		printf("close		关闭miniUFS系统\n");
		printf("\n");
	}else
	{
		int num1=GetOperateID(command);
		switch (num1)
		{
			case 0:
				printf("变更到指定目录下\n");
				printf("\n");
				printf("CD  [path]\n");
				printf("CD  ~\\[path]\n");
				printf("CD  ..\n\n");
				printf("使用..指定改成父目录。\n");
				printf("使用~指定目录的绝对路径。\n");
				printf("path 目录的相对路径\n\n");
				printf("例如 键入 cd ~\\temp 将会变更到temp文件夹下  \n");
				printf("当前的目录字符串会被转换成使用磁盘名上的大小写。所以，\n");
				printf("如果磁盘上的大小写如此，CD ~\\TEMP 会将当前目录设为~\\Temp。\n\n");
				printf("CD 命令将空格视为分隔符，所以目录中请不要包含空格。\n");
				printf("\n");
				printf("\n");break;
			case 1:
				printf("创建一个新的文件夹\n");
				printf("\n");
				printf("newdir [path] [dirname]\n\n");
				printf("path		绝对路径或相对路径均可,用于指明需要删除文件夹的具体位置\n");
				printf("dirname		创建的文件夹名称\n");
				printf("如果不输入则系统会使用默认文件夹名创建文件夹。\n\n");
				printf("在当前目录下创建一个新的文件夹\n");
				printf("NEWDIR 命令将空格视为分隔符，所以目录中请不要包含空格。\n");
				printf("\n");

				printf("\n");break;
			case 2:case 3:
				printf("删除至少一个文件夹\n");
				printf("\n");
				printf("deldir [path] dirname\n\n");
				printf("path		绝对路径或相对路径均可,用于指明需要删除文件夹的具体位置\n");
				printf("dirname		需要删除的文件夹名称，支持使用通配符。\n\n");
				printf("将会把文件夹以及里面的子文件夹和文件一并删除\n");
				printf("DELDIR 命令将空格视为分隔符，所以目录中请不要包含空格。\n");
				printf("\n");
				printf("\n");break;
			case 4:
				printf("将一个文件夹剪切到另一个位置\n");
				printf("\n");
				printf("cutdir [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2		绝对路径或相对路径均可,用于指明文件夹的具体位置 \n\n");
				printf("如不填写，默认为当前目录下\n");
				printf("执行成功后文件夹1会被删除\n");
				printf("CUTDIR 命令将空格视为分隔符，所以目录中请不要包含空格。\n\n");
				printf("\n");
				printf("\n");break;
			case 5:
				printf("显示当前目录中的文件和文件夹\n");
				printf("\n");
				printf("dr [filename]\n\n");
				printf("filename 指定要列出的文件名，支持正则表达式。\n\n");
				printf("如果不填，执行成功后将在屏幕中列出当前目录下的所有文件和文件夹\n\n");			
				printf("文件和文件夹将以文件名字母顺序排序。\n");		
				printf("\n");
				printf("\n");break;
			case 6:
				printf("将一个文件夹复制到另一个位置\n");
				printf("\n");
				printf("cpdir [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2		绝对路径或相对路径均可,用于指明文件夹的具体位置 \n\n");
				printf("如不填写，默认为当前目录下\n");
				printf("\nCPDIR 命令将空格视为分隔符，所以目录中请不要包含空格。\n\n");
				printf("\n");
				printf("\n");break;
			case 7:
				printf("显示一个文件夹的具体属性\n");
				printf("\n");
				printf("attdir [path]dirname\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件夹的具体位置 \n\n");
				printf("如不填写，默认为当前目录下\n");
				printf("执行成功后将会显示文件夹的属性，如可读可写等\n");
				printf("\n");
				printf("\n");break;
			case 8:
				printf("重命名文件夹。\n\n");
				printf("renamedir [path]dirname\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件夹的具体位置 \n\n");
				printf("如不填写，默认为当前目录下\n");
				printf("\n");break;
			case 9:
				printf("在文件系统内搜索文件。\n");
				printf("search [path]filename\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件夹的具体位置 \n");
				printf("如不填写，默认为当前目录下\n\n");
				printf("filename指定要搜索的文件名，支持使用正则表达式。\n");
			printf("\n");break;
			case 10:
				printf("创建一个新的文件\n");
				printf("new [path][filename]\n\n");
				printf("path  绝对路径或相对路径均可,用于指明创建文件的具体位置 \n");
				printf("如不填写，默认为当前目录下创建文件\n");
				printf("filename 创建的文件名称\n");
				printf("如不填写系统将以默认文件名创建文件。\n");
				printf("\n");
				printf("\n");break;
			case 11:
				printf("将一个文件复制到另一个位置\n");
				printf("\n");
				printf("cp [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2 绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("如不填写，默认为当前目录下\n\n");
				printf("\n");
				printf("\n");break;
			case 12:
				printf("将一个文件剪切到另一个位置\n");
				printf("\n");
				printf("cut [path1]filename1  [path2]filename2\n\n");
				printf("path1 path2 绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("如不填写，默认为当前目录下\n\n");
				printf("执行成功后文件1会被删除\n");
				printf("\n");
				printf("\n");break;
			case 13:case 14:
				printf("删除至少一个文件\n");
				printf("\n");
				printf("rm [path]filename\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("filename 需要删除的文件名称,支持使用通配符。\n\n");
				printf("如不填写，默认为当前目录下\n");
				printf("\n");
				printf("\n");break;
			case 15:
				printf("以普通文本形式显示一个文件的内容\n");
				printf("\n");
				printf("type [path]filename\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("如不填写，默认为当前目录下\n\n");
				printf("filename 需要显示的文件名称\n\n");
				printf("执行成功后将会把指定文件中的内容输出到屏幕上\n");
				printf("\n");
				printf("\n");break;
			case 16:
				printf("以分页文本形式显示一个文件的内容\n");
				printf("\n");
				printf("more [path]filename\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("如不填写，默认为当前目录下\n\n");
				printf("filename 需要显示的文件名称\n\n");
				printf("执行成功后将会把指定文件中的内容以分页形式输出到屏幕上\n");
				printf("\n");
				printf("\n");break;
			case 17:
				printf("编辑文件功能\n");
				printf("\n");
				printf("edit [-option] [path]filename \n\n");
				printf("可用 option：\n\n");
				printf("	-w : 以覆写形式打开文件。\n");
				printf("	-a : 以追加形式打开文件。\n");
				printf("	-vim : 使用Vim打开文件。\n");
				printf("	如果不添加选项则默认使用 -a 选项。\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("如不填写，默认为当前目录下\n\n");
				printf("filename 需要编辑的文件名称\n");
				printf("执行成功后，可以键入想写入文件中的内容\n\n");
				printf("使用 -w 和 -a 选项时需要结束编辑按CTRL + C\n");
				printf("\n");
				printf("\n");break;
			case 18:
				printf("显示一个文件的具体属性\n");
				printf("\n");
				printf("attdir [path]filename\n");
				printf("path  绝对路径或相对路径均可,用于指明文件夹的具体位置 \n");
				printf("如不填写，默认为当前目录下\n");
				printf("执行成功后将会显示文件的属性，如可读可写等\n");
				printf("\n");
				printf("\n");break;
			case 19:
				printf("恢复一个已删除文件\n");
				printf("\n");
				printf("rc [filename]\n\n");
				printf("filename 需要恢复文件的名称\n");
				printf("如不填写，将恢复最近一次删除的文件\n");
				printf("执行成功后，文件将会恢复删除前状态\n");
				printf("\n");
				printf("\n");break;
			case 20:
				printf("显示一个文件所使用的数据块\n");
				printf("\n");
				printf("block [path]filename\n");
				printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("如不填写，默认为当前目录下\n");
				printf("filename 需要显示的文件名称\n");
				printf("执行成功后将会把指定文件中的内容以数据块形式输出到屏幕上\n");
				printf("\n");
				printf("\n");break;
			case 21:
				printf("重命名一个文件\n");
				printf("\n");
				printf("rename [path]filename1 filename2\n\n");
				printf("path  绝对路径或相对路径均可,用于指明文件的具体位置 \n");
				printf("如不填写，默认为当前目录下\n\n");
				printf("filename1 需要重命名的文件名称\n\n");
				printf("filename2 更改后的文件名称\n\n");
				printf("执行成功后将会把文件名变更成所需名称\n");
				printf("\n");
				printf("\n");break;
			case 22:
				printf("以树形结构展示文件系统\n");
				printf("\n");
				printf("tree [-option]\n\n");
				printf("可用 option:\n");
				printf("	-r : 以树形结构展示整个文件系统\n");
				printf("	-n : 以树形结构展示当前目录文件系统\n");
				printf("	如果不写选项则默认使用 -n 选项。\n\n");
				printf("执行命令tree后，将会以树形形式把文件系统输出在屏幕上\n");
				printf("\n");
				printf("\n");break;
			case 23:
				printf("格式化磁盘\n");
				printf("\n");
				printf("fmt [-option]\n\n");
				printf("可用 option:\n");
				printf("	-d : 低级格式化\n");
				printf("	-n : 普通格式化\n");
				printf("	如果不写选项则默认使用 -n 选项。\n\n");
				printf("执行成功后，将会格式化整个磁盘空间，清空里面的所有文件\n");
				printf("系统文件等将被恢复最初状态\n");
				printf("\n");
				printf("\n");break;
			case 24:
				printf("显示当前磁盘的空间使用情况\n");
				printf("\n");
				printf("space\n");
				printf("执行成功后，将会显示当前磁盘空间的使用情况到屏幕中\n");
				printf("\n");
				printf("\n");break;
			case 25:
				printf("显示回收站中的所有文件和文件夹\n");
				printf("\n");
				printf("deleted\n");
				printf("执行成功后，将会显示所有回收站中的文件和文件夹名称到屏幕中\n");
				printf("\n");
				printf("\n");break;
			case 26:
				printf("更改用户名和密码\n");
				printf("\n");
				printf("user\n");
				printf("执行成功后，将会进入下一步操作\n");
				printf("根据操作完成用户名和密码的重新设置\n");
				printf("\n");
				printf("\n");break;
			case 27:
				printf("关闭miniUFS系统\n");
				printf("\n");
				printf("close\n");
				printf("执行成功后，将会关闭miniUFS系统\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");
				printf("\n");break;
			default:
				printf("找不到对应命令。\n");
				printf("当前支持命令如下：\n\n");
				Help(1,0);

		}

	}
}