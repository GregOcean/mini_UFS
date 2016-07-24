#pragma once


struct FileNode
{

	int fid;

	char filename[9];
	char extention[4];
	char createtime[14];
	char lastedittime[14];
	int  FDBBlock;


	char IfDelete;;
	char IfCanRead;
	char IfCanWrite;

	int  filesize;
	int  FCBBlock;

	char type;

	int SonNum;
	int *childnode;
	int fatherFid;

};

struct FileIndex
{
	char filename[9];
	char extention[4];
	char type;
	FileNode *node;
};

