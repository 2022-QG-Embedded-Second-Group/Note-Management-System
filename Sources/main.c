#define _CRT_SECURE_NO_WARNINGS 1
#include "user.h"

int main()
{
	UserList u;
	FileType file[FILEMAXN];
	int n;
	FileTree Userrootfile;//�û���Ŀ¼
	UserNode* user;
	InitUserInfo(&u);//��ʼ�������û���Ϣ
	int input = 0;//�û��˵�����

	int userinput = 0;//�û��˵�����
	do
	{
	Input:
		usermenu();
		printf("��ѡ��ģʽ[0~3]:>");
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
		case 3:
			FindPasswod(u);//�һ�����
			break;
		default:
			printf("�������,����������[0~3]:");
			system("pause");
			goto Input;
			break;
		}
	} while (input);
	printf("�˳�ϵͳ�ɹ�\n");
	return 0;
}