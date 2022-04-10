#define _CRT_SECURE_NO_WARNINGS 1
#include "user.h"

int main()
{
	UserList u;
	FileType file[FILEMAXN];
	int n;
	FileTree Userrootfile;//用户根目录
	UserNode* user;
	InitUserInfo(&u);//初始化所有用户信息
	int input = 0;//用户菜单输入

	int userinput = 0;//用户菜单输入
	do
	{
	Input:
		usermenu();
		printf("请选择模式[0~3]:>");
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
			FindPasswod(u);//找回密码
			break;
		default:
			printf("输入错误,请重新输入[0~3]:");
			system("pause");
			goto Input;
			break;
		}
	} while (input);
	printf("退出系统成功\n");
	return 0;
}