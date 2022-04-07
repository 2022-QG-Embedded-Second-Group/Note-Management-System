#ifndef _USER_H_
#define _USER_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "../Headers/file.h"
typedef int Status;//������������


#define SUCCESS 1
#define ERROR   0
#define MAX_USERIDSZ        30
#define MAX_PASSWORDSZ      20
#define MAX_FINDPASSWORDSZ  20
#define MAX_USERFILENAMESZ  40


//�û���Ϣ
typedef struct UserInfo
{
    char userid[MAX_USERIDSZ + 1];  //���֧��20���ַ�       �û�id
    char password[MAX_PASSWORDSZ + 1];//���֧��20���ַ�     �û�����
    long long phonenum;//�û��ֻ����룬�����һ�����
    char userfilename[MAX_USERFILENAMESZ + 1];//�û���Ӧ���ļ�������ͨ���ļ����ҵ��Լ����ļ���Ϣ
    int privacyflag;//0��ʾΪ��˽ģʽ��1��ʾΪ����״̬
    int modifyflag;//0��ʾֻ�ܲ鿴�û��ʼǣ�1��ʾ�������ܶ�����ɾ��
}UserInfo;

typedef struct UserNode
{
    UserInfo* data;  //����û�����
    struct UserNode* next;//ָ����һ���ڵ�
}UserNode, * UserList;


Status InitUserList(UserList* L);//��ʼ���û�����
Status InsertNewUser(UserList* L, UserInfo* data);//�������û�
UserNode* SearchUser(UserList L, const char* userid);//Ѱ���û�������ڵ�ĵ�ַ,���û�оͷ���NULL
int getstring(int num, char* str);//��ȡ�ַ���
long long getlonglong(long long* num);//��ȡ����
Status getint(int* num); //��ȡ����
/***********��Ҫ����************************/
Status FileSave(UserInfo* user);//�ļ�����
/***********��Ҫ����************************/
//ע��һ�����û�,ͬʱ����һ�����û���Ϊ���Ƶ��ļ��У����浽��(user.id+.info)���ļ���
void RegisterUser(UserList* L, FileType file[], int* n);
Status InitUserInfo(UserList* L);//��ʼ���û���Ϣ
Status FileUpdata(UserList L);//�ļ��������� 
Status FindPasswod(UserList L);//�һ�����
/************��Ҫ����**********************/
//�û���¼������ʼ��file, �Լ�n��ֵ, ����һ����
UserNode* LogUser(UserList L, FileType file[], int* n, FileTree* Userrootfile);//�û���¼




#endif
