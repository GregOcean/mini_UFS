#pragma once
#include "structure.h"

//Public Function


int AddressOfBlock(int BlockID);//�ļ����Ӳ��λ�ö�
bool WriteToBlock(int BlockID,char *indata,int length);//д���ݿ飨���ݿ��š�д������ݡ����ݴ�С��
int  ReadBlock(int BlockID,char *outdata,int length);//�����ݿ飨���ݿ��š���ȡ�����ݡ����ݴ�С��
bool ChangeAttribute(int mode,int fid);//�����ļ�/�����ԣ��ļ��ڵ��š��ļ����ƿ飩
int  GetFileID(char*filename,char*extention);//��ȡ�ļ��ڵ���
int ThreeToInt(char *source);						//���ֽ�ת�����ֽ�
void IntToThree(int source,char *Dest);		//���ֽ�ת�����ֽ�
int GetNextBlankFDB();									//��ȡ��һ���������ݿ���
bool ChangeNowDir(char *dir);						//�ı䵱ǰĿ¼
void ChangeNowDirFid(int fid);						//�ı䵱ǰĿ¼
void ChangeNowDirName(int mode,char *Dir);//�ı�NowDirRoute������ֵ
int GetDirID(int mode,char *Dir);//mode1 �ӵ�ǰĿ¼Ѱ��
													//mode2�Ӹ�Ŀ¼Ѱ��
int GetOperateID(char *op);		//������ǰ����
void str2Reg(char *str);
int ReplaceStr(char *sSrc, char *sMatchStr, char *sReplaceStr);


//Private Function

void InitOnStart();//��ʼ�����̿ռ�
void ParseCmd(char *cmd);//����ָ��
void Format(int mode);//��ʽ��
void Dir(char *filename,char *extention);//��ʾ�ļ�Ŀ¼
int Copy(int mode,char *filenameSourc,char *fileextSourc,
	char *fileextDest,char* filenameDest);//�����ļ�(ģʽ��ǡ��ļ�Դ���ļ�Ŀ�ĵ�)
bool New(int mode,char *filename,char *extention);//�½��ļ���1��/�У�2��
bool Delete(int mode,char *filename,char *extention);//ɾ���ļ����ļ������Ƿ���ɾ����
void Display(int mode,int fid);//��ʾ�ļ�����
void DisplayAttribute(int mode,char *filename,char *extention);//��ʾ�ļ�����
void Help(int mode,char *command);//����(ģʽ������ѯ��ָ��)
void Close();
bool Edit(int mode,char *filename,char *extention/*,int mode*/);
void recovery(char *filename,char *extention);
void BlockOfFile(char *filename,char *extention);
bool Login();
void Tree(int deep,int fid);
bool rename(int mode,int fid,char *filename,char *extention);
bool cut(int mode,int fidsource,int fiddest);
void Search(char *filename,char *extention);
void DisplayCrtTime(FileNode* fn);//��ʾ����ʱ������_��ʽ
int BuildFileTree(int rootFCB,int fid,int fatherFid);
void GetSonFCB(int SonNum,int FDB,int *outData);
void cpdir(int fidsource,int fiddest);