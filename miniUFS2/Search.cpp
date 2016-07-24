#include "Global.h"
#include "string.h"
#define PCRE_STATIC // æ≤Ã¨ø‚±‡“Î—°œÓ         
#include "pcre.h"      
#define OVECCOUNT 30 /* should be a multiple of 3 */      
#define EBUFLEN 128      
#define BUFLEN 1024      
#pragma  comment (lib,"pcre.lib")   

void Search(char *filename,char *extention)
{
	FileNode fn;
	pcre  *re1; 
	pcre  *re2;  
	const char *error;     
	int  erroffset;     
	int  ovector1[OVECCOUNT],ovector2[OVECCOUNT];     
	int  rc1, rc2;     
	char  srcfilename[1000];   
	char  srcextention[1000];  
	char  pattern1[1000];   
	char  pattern2[1000]; 
	FileNode fn1=*fileIndex[NowDirFid].node;
	for (int i=0;i<fn1.SonNum;i++)
	{
		fn=*fileIndex[fn1.childnode[i]].node;
		if (fn.type==t_File)
		{
			memset(ovector1,0,sizeof(ovector1));
			memset(ovector2,0,sizeof(ovector2));

			strcpy(srcfilename,fn.filename);
			strcpy(pattern1,filename);
			strcpy(srcextention,fn.extention);
			strcpy(pattern2,extention);

			re1 = pcre_compile(pattern1,       
				0,         
				&error,       
				&erroffset,  
				NULL);      			    
			rc1 = pcre_exec(re1,              
				NULL,           
				srcfilename,           
				strlen(srcfilename),       
				0,              
				0,            
				ovector1,      
				OVECCOUNT);   

			re2 = pcre_compile(pattern2,       
				0,         
				&error,       
				&erroffset,  
				NULL);      
			rc2 = pcre_exec(re2,              
				NULL,           
				srcextention,           
				strlen(srcextention),       
				0,              
				0,            
				ovector2,      
				OVECCOUNT); 
			int substring_length1 = ovector1[2*0+1] - ovector1[2*0]; 
			int substring_length2 = ovector2[2*0+1] - ovector2[2*0]; 
			if (rc1 >= 0 && rc2>=0 &&strlen(fn.filename)==substring_length1 
				&& strlen(fn.extention)==substring_length2) 
			{                      
				printf("%s\\",NowDirRoute);
				printf("%s",fn.filename);
				printf(".%s",fn.extention);
				printf("\n");
			}     
		}
		else
		{
			char Ori[2000];
			strcpy(Ori,NowDirRoute);
			ChangeNowDir(fn.filename);
			Search(filename,extention);
			ChangeNowDir(Ori);
		}
	}


}