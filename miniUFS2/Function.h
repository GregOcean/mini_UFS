#pragma once
#include "structure.h"

//Public Function


int AddressOfBlock(int BlockID);//文件块的硬盘位置定
bool WriteToBlock(int BlockID,char *indata,int length);//写数据块（数据块编号、写入的数据、数据大小）
int  ReadBlock(int BlockID,char *outdata,int length);//读数据块（数据块编号、读取的数据、数据大小）
bool ChangeAttribute(int mode,int fid);//更改文件/夹属性（文件节点编号、文件控制块）
int  GetFileID(char*filename,char*extention);//获取文件节点编号
int ThreeToInt(char *source);						//三字节转向四字节
void IntToThree(int source,char *Dest);		//四字节转向三字节
int GetNextBlankFDB();									//获取下一个空闲数据块编号
bool ChangeNowDir(char *dir);						//改变当前目录
void ChangeNowDirFid(int fid);						//改变当前目录
void ChangeNowDirName(int mode,char *Dir);//改变NowDirRoute变量的值
int GetDirID(int mode,char *Dir);//mode1 从当前目录寻找
													//mode2从根目录寻找
int GetOperateID(char *op);		//解析当前操作
void str2Reg(char *str);
int ReplaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr);


//Private Function

void InitOnStart();//初始化磁盘空间
void ParseCmd(char *cmd);//解析指令
void Format(int mode);//格式化
void Dir(char *filename,char *extention);//显示文件目录
int Copy(int mode,char *filenameSourc,char *fileextSourc,
	char *fileextDest,char* filenameDest);//拷贝文件(模式标记、文件源、文件目的地)
bool New(int mode,char *filename,char *extention);//新建文件（1）/夹（2）
bool Delete(int mode,char *filename,char *extention);//删除文件（文件名、是否级联删除）
void Display(int mode,int fid);//显示文件内容
void DisplayAttribute(int mode,char *filename,char *extention);//显示文件属性
void Help(int mode,char *command);//帮助(模式、所查询的指令)
void Close();
bool Edit(int mode,char *filename,char *extention/*,int mode*/);
void recovery(char *filename,char *extention);
void BlockOfFile(char *filename,char *extention);
bool Login();
void Tree(int deep,int fid);
bool rename(int mode,int fid,char *filename,char *extention);
bool cut(int mode,int fidsource,int fiddest);
void Search(char *filename,char *extention);
void DisplayCrtTime(FileNode* fn);//显示创建时间属性_格式
int BuildFileTree(int rootFCB,int fid,int fatherFid);
void GetSonFCB(int SonNum,int FDB,int *outData);
void cpdir(int fidsource,int fiddest);