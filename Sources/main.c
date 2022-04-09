#include "../Headers/file.h"
#include "file.c"
#include "../Headers/user.h"
#include "user.c"

#define _CRT_SECURE_NO_WARNINGS 1

int main()
{
    UserList u;
    FileType file[FILEMAXN];
    int n;
    FileTree Userrootfile; //�û���Ŀ¼
    UserNode *user;
    InitUserInfo(&u); //��ʼ�������û���Ϣ
    int input = 0;    //�û��˵�����

    int userinput = 0; //�û��˵�����
    do
    {
    Input:
        usermenu();
        printf("��ѡ��ģʽ[0~2]:>");
        getint(&input);
        switch (input)
        {
        case 0:
            break;
        case 1:
            user = LogUser(u, file, &n, &Userrootfile);
            if (user != NULL)
            {
                UsersOperation(&n, file, Userrootfile, user);
            }

            break;
        case 2:
            RegisterUser(&u, file, &n);
            break;
        default:
            printf("�������,����������[0~2]:");
            system("pause");
            goto Input;
            break;
        }
    } while (input);
    printf("�˳�ϵͳ�ɹ�\n");
    return 0;
}