#include "../Headers/file.h"
#include "file.c"
#include "../Headers/user.h"
#include "user.c"

#define _CRT_SECURE_NO_WARNINGS 1

int main()
{
    UserList L;
    FileType file[FILEMAXN]; //����û��ļ�
    FileTree Userrootfile;   //�û���Ŀ¼
    int n = 0;               //������ʾ����ĳ���
    UserNode *user;
    InitUserInfo(&L); //��ʼ�������û���Ϣ
    // RegisterUser(&L, file, &n);
    user = LogUser(L, file, &n, &Userrootfile); //�û���¼
    FileTree usertree;
    if (user == NULL)
        printf("��¼ʧ��");
    else
    {
        ReadFile(file, &n, user->data->userfilename); //���û���Ϣ�ŵ�������
    }
    return 0;
}