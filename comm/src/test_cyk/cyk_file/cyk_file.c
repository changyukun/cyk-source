/*****************************************************************************
File Name   :  hl_file.c

Description :  

     Author   :  changyukun

*****************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif



/*========== ͷ�ļ�==============================================================================================*/
#include <sys/statfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "stdio.h"
#include <unistd.h>
#include <string.h>





/*========== �ⲿ��������=======================================================================================*/






/*========== �궨��==============================================================================================*/
#define DIR_MAX_LEN 	255






/*========== ���ݽṹ����=======================================================================================*/








/*========== ��������============================================================================================*/







/*========== ����ʵ��============================================================================================*/
//-------------------------------------------------------------------------------------------------
int hl_file_op(unsigned char type, char*FullPathName, char* filename, void* privateData)
{
/*
	����:
		1��type			: 	0: ��·��
						  	1: �ر�·��
						  	2: ��ȡ�򿪵�·���е���Ŀ¼���ļ������ɲ���filename ����
						  	3: �жϴ����FullPathName ·���Ƿ�Ϊһ��Ŀ¼
						  	4: ��ô���Ŀ¼���ϼ�Ŀ¼���ɲ���FullPathName ���أ�����filename ������Ŀ¼���ļ�������
						  	5: ���ݴ����·����������һ��Ŀ¼( ��FullPathName ָ��Ҫ������Ŀ¼)
						  	6: ɾ�������Ŀ¼( ��FullPathName ָ��Ҫɾ����Ŀ¼)
						  	7: ɾ��������ļ�( ��FullPathName ָ��Ҫɾ���ļ���ȫ·��)
						  	8: �޸��ļ����ԣ��ļ�ȫ·���ɲ���FullPathName ���룬��ӵ������ɲ���private ���룬0777 Ϊȫ����
		2��FullPathName	: 
		3��filename		: 

	����:
		1��0:�ɹ� other:ʧ��
	
	˵��:
		1��
*/
	
	int				result = 0;
	int				found = 0;
	static DIR* 		dirp = NULL;
	DIR* 			dirp_temp = NULL;
	struct dirent*		direntp;

	switch(type)
	{
		case 0:	/* ��·��*/
			{
				if(dirp!=NULL)
				{
					closedir(dirp);
					dirp = NULL;
				}
				dirp = opendir(FullPathName);
				if(dirp==NULL) 
					result = -1;
			}
			break;
			
		case 1:	/* �ر�·��*/
			{
				closedir(dirp);
				dirp = NULL;
			}
			break;
			
		case 2:	/* ��ȡ·����������Ŀ¼���ļ���*/
			{
				while((direntp = readdir(dirp))!=NULL)
				{
					if((strcmp(direntp->d_name,".")!=0) && (strcmp(direntp->d_name,"..")!=0))
					{
						if(NULL != filename) 
							strcpy(filename,direntp->d_name); 
						found = 1;
						break;
					}
					else
					{
						if((strcmp(direntp->d_name,".")!=0) || (strcmp(direntp->d_name,"..")!=0))
							continue;
						else
						{
							found = 0;
							break;
						}
					}
				}
				
				if(!found)
					result = -1;
			}
			break;
			
		case 3:	/* �ж��Ƿ�Ϊһ��������Ŀ¼*/
			{
				dirp_temp = opendir(FullPathName);
				if(dirp_temp==NULL) 
					result = -1;
				else 
					closedir(dirp_temp);
			}
			break;

		case 4:	/* ��ô���Ŀ¼�ĸ�Ŀ¼*/
			{
				int j,k;
				for (j=strlen((char *)FullPathName);j!=0;j--)
				{
					if(FullPathName[j]=='/') 
						break;
				}
				if (j==0) 
				{
					result = -1;
					break;
				}
				if (FullPathName[j]=='/') { k=j; j=strlen((char *)FullPathName); }
				else
				{
					result = -1;
					break;
				}
				if(filename != NULL)
				{
					strncpy(filename,(char *)&FullPathName[k+1],(j-k-1));
					filename[(j-k-1)]=0;
				}
				FullPathName[k]=0;
			}
			break;

		case 5:	/* ���ݴ����·����������һ��Ŀ¼*/
			{
				#if 1
					/* �𼶷���Ŀ¼�����д���*/
					int j,k;
					char FullDir[DIR_MAX_LEN] = {0};
					char SubDir[DIR_MAX_LEN] = {0};

					sprintf(FullDir,"%s",FullPathName);
					while(1)
					{
						for (j=strlen((char *)FullDir);j!=0;j--)
						{
							if(FullDir[j]=='/') 
								break;
						}
						if (j==0) 
						{
							result = -1;
							break;
						}
						if (FullDir[j]=='/') { k=j; j=strlen((char *)FullDir); }
						else
						{
							result = -1;
							break;
						}
						strncpy(SubDir,(char *)&FullDir[k+1],(j-k-1));
						SubDir[(j-k-1)]=0;
						FullDir[k]=0;

						dirp_temp = opendir(FullDir);
						if(dirp_temp==NULL) 
							continue;
						else 
						{
							closedir(dirp_temp);
							sprintf(FullDir,"%s/%s",FullDir,SubDir);
							if(mkdir(FullDir,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH) != 0)
								return -1;
						}

						sprintf(FullDir,"%s",FullPathName);	
						dirp_temp = opendir(FullDir);
						if(dirp_temp != NULL)
						{
							closedir(dirp_temp);
							break;
						}
					}
				#else
					/* ������Ŀ¼ֱ�ӽ��д���*/
					if(mkdir(FullPathName,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH) != 0)
						result = -1;
				#endif
			}
			break;

		case 6:
			{
				if(0!=rmdir(FullPathName)) /* ɾ�������·��*/
					result = -1;
			}
			break;

		case 7:/* ɾ���ļ�*/
			if(0 == access(FullPathName,F_OK))
			{
				if(0!=remove(FullPathName))	
					result = -1;
			}
			break;

		case 8:/* �޸��ļ�����*/
			{
				/*
					S_ISUID 04000 �ļ���(set user-id on execution) λ
					S_ISGID 02000 �ļ���(set group-id on execution) λ
					S_ISVTX 01000 �ļ���stickyλ
					S_IRUSR (S_IREAD) 00400 �ļ������߾߿ɶ�ȡȨ��
					S_IWUSR (S_IWRITE) 00200 �ļ������߾߿�д��Ȩ��
					S_IXUSR (S_IEXEC) 00100 �ļ������߾߿�ִ��Ȩ��
					S_IRGRP 00040 �û���߿ɶ�ȡȨ��
					S_IWGRP 00020 �û���߿�д��Ȩ��
					S_IXGRP 00010 �û���߿�ִ��Ȩ��
					S_IROTH 00004 �����û��߿ɶ�ȡȨ��
					S_IWOTH 00002 �����û��߿�д��Ȩ��
					S_IXOTH 00001 �����û��߿�ִ��Ȩ��
				*/
				int mod = (int)privateData;
				chmod(FullPathName, mod);
			}
			break;
			
		default:
			result = -1;
			break;
	}

	return result;
}





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif 


