#define _CRT_SECURE_NO_WARNINGS 1
#include "../Headers/user.h"

//��ʼ���û�����
//ͷ�ڵ㲻�������
Status InitUserList(UserList *L)
{
	*L = (UserList)malloc(sizeof(UserNode)); //�����û�����ռ�
	if ((*L) == NULL)						 //���ٿռ�ʧ��
	{
		printf("%s\n", strerror(errno)); //��ӡ����ʧ�ܵ�ԭ��
		return ERROR;
	}
	UserList p = (*L);
	p->data = (UserInfo *)malloc(sizeof(UserInfo)); //Ϊָ������ݿ��ٿռ�
	if (p->data == NULL)							//���ٿռ�ʧ��
	{
		printf("%s\n", strerror(errno));
		return ERROR;
	}
	p->next = NULL; //��һ���ڵ�ָ���
	return SUCCESS;
}

//�������û�
Status InsertNewUser(UserList *L, UserInfo *data)
{
	UserList La = (*L), Ltail = (*L);
	while (La) //�ҵ�β�ڵ�
	{
		Ltail = La;
		La = La->next;
	}
	UserList user;
	user = (UserList)malloc(sizeof(UserNode)); //���ٿռ�
	if (user == NULL)						   //���ٿռ�ʧ��
	{
		printf("%s\n", strerror(errno));
		return ERROR;
	}
	user->data = (UserInfo *)malloc(sizeof(UserInfo)); //���ٿռ�
	if (user->data == NULL)							   //���ٿռ�ʧ��
	{
		printf("%s\n", strerror(errno));
		return ERROR;
	}
	user->data = data;	//��ȡ����
	user->next = NULL;	//��һ���ڵ�ָ���
	Ltail->next = user; //�û������������û���Ϣ
	return SUCCESS;
}

//Ѱ���û�
//������ڵ�ĵ�ַ,���û�оͷ���NULL
UserNode *SearchUser(UserList L, const char *userid)
{
	UserList p = L->next; //ָ���һ��Ԫ��
	while (p)			  //Ѱ���û���
	{
		if ((strcmp(userid, p->data->userid)) == 0) //�ҵ���Ӧ���û���
		{
			return p; //�����û��Ľڵ�
		}
		p = p->next; //û���ҵ�ָ����һ���ڵ�
	}
	return NULL; //�Ҳ����ͷ��ؿ�ָ��
}

//��ȡ�ַ���
//���ض�ȡ�����ַ�����
//����-1���ȡ��������
// num������ַ���,��ȡ�ɹ����ַ�����ŵ�str��
int getstring(int num, char *str)
{
	int i = 0;
	char ch;				 //��Ŷ�ȡ�����ַ�
	int count = 1;			 //����
	scanf(" %c", &(str[0])); //��ȡ��һ���ǿ��ַ�
	for (i = 1; i < num; i++)
	{
		ch = getchar();
		if (ch == '\n')
		{
			str[i] = '\0';
			break;
		}
		str[i] = ch; //��ÿ���ַ���ŵ�str��
		count++;	 //�ַ�����1
	}
	if (i == num) //��������ַ���
	{
		scanf("%*[^\n]%*c");	  //��ջ�����
		for (i = 0; i < num; i++) //�������
			str[i] = 0;
		printf("������ַ�����������������!\n");
		return -1;
	}
	return count; //���ض�ȡ�����ַ���
}

//��ȡ����
//���ض�ȡ������
// ����ȡ�ɹ������֣���ֵ��num
long long getlonglong(long long *num)
{
	long long numtemp;
	while (1)
	{
		if (scanf("%lld", &numtemp) == 1) //�ɹ���ȡ������
		{
			*num = numtemp; //����ȡ��������ֵ��num
			return numtemp;
		}
		scanf("%*[^\n]%*c"); //��ջ�����
		printf("�����������������:> ");
	}
}

//��ȡ����
int getint(int *num)
{
	int numtemp;
	while (1)
	{
		if (scanf("%d", &numtemp) == 1) //�ɹ���ȡ������
		{
			*num = numtemp; //����ȡ��������ֵ��num
			return numtemp;
		}
		//��ȡ���ɹ���������Ĳ�������
		scanf("%*[^\n]%*c"); //��ջ�����
		printf("�����������������:> ");
	}
}

//��Ҫ�޸�
//�ļ�����
Status FileSave(UserInfo *user)
{
	FILE *fwrite = fopen("userinfo.txt", "a+");
	fprintf(fwrite, "%-30s\t", user->userid);		//�û�����¼��
	fprintf(fwrite, "%-20s\t", user->password);		//�û�����¼��
	fprintf(fwrite, "%-12lld\t", user->phonenum);	//¼���ֻ�����
	fprintf(fwrite, "%-40s\t", user->userfilename); //¼���ļ���
	fprintf(fwrite, "%-2d\t", user->privacyflag);	//¼����˽��־λ
	fprintf(fwrite, "%-2d\n", user->modifyflag);	//¼������Ȩ��

	fclose(fwrite);
	fwrite = NULL;
	return SUCCESS;
}

//����иĶ�
//ע��һ�����û�
// n��ǰ�ļ��ĸ���
// file[]����ļ�������
void RegisterUser(UserList *L, FileType file[], int *n)
{
	UserInfo userdata; //����һ���û���Ϣ�Ľṹ��

	/*******************�û�ע�����û���***********************/
	do
	{
		printf("���������봴�����û���(������20���ַ�): ");
		if (-1 == getstring(MAX_USERIDSZ, userdata.userid)) //��ȡid,�����������������ѭ������
		{
			continue;
		}
		if (SearchUser(*L, userdata.userid) != NULL) // ID�ظ�
		{
			printf("���û����ѱ�ע��,�����´���һ���µ��û���!!!\n");
		}
		else
			break; //������������������˳�ѭ��
	} while (1);
	/**********************************************************/

	/********************�û���������**************************/
mode1:
	do //������������һֱ�����������Ҫ�󣬾�һֱ������ѭ����
	{
		printf("���������봴��������(����6���ַ������20���ַ�): ");
		int length = getstring(MAX_PASSWORDSZ, userdata.password);
		if (length == -1) //����ĳ��ȹ���
			continue;	  //ѭ������
		if (length < 6)	  //����ĳ��ȹ���
		{
			printf("���õ���������6���ַ�������������!\n");
			continue; //ѭ������
		}
		break;
	} while (1);
mode2:
	do //������������һֱ�����������Ҫ�󣬾�һֱ������ѭ����
	{
		char str[MAX_PASSWORDSZ + 1] = {0};
		printf("���ٴ�ȷ������(����6���ַ������20���ַ�): ");
		int length = getstring(MAX_PASSWORDSZ, str); //��ȡ���볤��
		int flag = strcmp(str, userdata.password);	 //�Ƚ�ǰ�������Ƿ�һ��
		if (flag == 0)								 //����һ���˳�ѭ��
		{
			break;
		}
		else //���벻һ��
		{
			printf("�����������\n");
		mode0:
			printf("1. ������������\n");
			printf("2. ����ȷ������\n");
			printf("��ѡ����: "); //���û�ѡ����
			int mode = 0;
			mode = getint(&mode);
			if (mode == 1) //������������
			{
				goto mode1; //�ص����������ҳ��
			}
			else if (mode == 2) //����ȷ������
			{
				goto mode2; //�ص�����ȷ�������ҳ��
			}
			else //û�иù���
			{
				scanf("%*[^\n]%*c"); //��ջ�����
				printf("û�иù���\n");
				printf("��ѡ�����еĹ���!\n");
				goto mode0; //�ص�����ȷ�������ҳ��
			}
		}
	} while (1);
	/*******************************************************/

	/********************�ܱ�����************************/
	do
	{
		printf("����������ֻ�����(�������������һ�): ");
		long long telephonenum = 0; //��ŵ绰����
		getlonglong(&telephonenum);
		if (telephonenum >= pow(10, 10) && telephonenum < pow(10, 11)) //������ֻ���λ��Ϊ11ʱ
		{
			userdata.phonenum = telephonenum;
			break;
		}
		else //����ĵ绰���벻����λ��
		{
			printf("�������ֻ�����ĸ�ʽ\n");
		}
	} while (1);

	userdata.privacyflag = 0; //Ĭ��Ϊ��˽ģʽ
	userdata.modifyflag = 0;  //Ĭ��ֻ�ܲ鿴״̬

	char userfile[MAX_USERIDSZ + 1] = {0};
	strcpy(userfile, userdata.userid);
	strcat(userfile, ".info");				 //��ֹ�����ظ� �ļ���: userid.info
	strcpy(userdata.userfilename, userfile); //���ļ������ƹ�ȥ

	//����һ���µ��ļ���(���û���Ϊ����)
	*n = 0;									  //��ʼ��Ϊ0
	strcpy(file[*n].name, userdata.userid);	  //���û���Ϊ���ִ����ļ���
	strcpy(file[*n].datetime, getDateTime()); //��ȡ����ʱ��
	file[*n].flag = 0;						  // 0��ʾ�ļ���
	(*n)++;
	SaveFile(file, *n, userdata.userfilename); //���浽�ļ���

	InsertNewUser(L, &userdata); //�����½ڵ�
	//���б�������
	FileSave(&userdata);
	InitUserInfo(L); //��ʼ���û���Ϣ
}

//��Ķ�
//��ʼ���û���Ϣ
Status InitUserInfo(UserList *L)
{
	InitUserList(L);
	FILE *pfread = fopen("userinfo.txt", "r");
	if (pfread == NULL)
	{
		return ERROR;
	}
	while (!feof(pfread))
	{
		UserInfo *userdata = (UserInfo *)malloc(sizeof(UserInfo)); //����һ���µĿռ�
		if (userdata == NULL)
		{
			printf("%s\n", strerror(errno));
			return ERROR;
		}
		fscanf(pfread, "%s", userdata->userid);
		fscanf(pfread, "%s", userdata->password);
		fscanf(pfread, "%lld", &(userdata->phonenum));
		fscanf(pfread, "%s", userdata->userfilename); //��ȡ�ļ�λ��  ��Ҫ����
		fscanf(pfread, "%d", &(userdata->privacyflag));
		fscanf(pfread, "%d\n", &(userdata->modifyflag));
		InsertNewUser(L, userdata); //�����½ڵ�
	}
	fclose(pfread);
	pfread = NULL;
	return SUCCESS;
}

//���޸�
//�����û���Ϣ���ļ����и���
//�ļ���������
Status FileUpdata(UserList L)
{
	UserList user = L->next;
	FILE *fupdate = fopen("temp.txt", "a+");
	while (user) //
	{
		fprintf(fupdate, "%-30s\t", user->data->userid);	   //���û�id��Ϣ�浽�ļ���
		fprintf(fupdate, "%-20s\t", user->data->password);	   //���û�������Ϣ�浽�ļ���
		fprintf(fupdate, "%-12lld\t", user->data->phonenum);   //���û��ֻ�����浽�ļ���
		fprintf(fupdate, "%-40s\t", user->data->userfilename); //���û��ļ����浽�ļ���
		fprintf(fupdate, "%-2d\t", user->data->privacyflag);   //������Ȩ�޷ŵ��ļ���
		fprintf(fupdate, "%-2d\n", user->data->modifyflag);	   //���޸�Ȩ�޷ŵ��ļ���
		user = user->next;									   //ָ����һ���ڵ�
	}
	fclose(fupdate);
	fupdate = NULL;
	remove("userinfo.txt");				//��ԭ�е��ļ���ɾ��
	rename("temp.txt", "userinfo.txt"); //���½������ļ�����Ϊuserinfo.txt
	return SUCCESS;
}

//�����һ�
Status FindPasswod(UserList L)
{
	int findmode = 0;
	char nameid[MAX_USERIDSZ + 1] = {0};
findmode1:
	do //��ȡ�û���
	{
		printf("����������û���: ");
	} while (-1 == getstring(MAX_USERIDSZ, nameid));
	UserList user = SearchUser(L, nameid); //Ѱ���Ƿ��и��û���

	if (user == NULL) //û���ҵ����û���
	{
		printf("û���ҵ����û�\n");
	findmode0:
		printf("1. ���������û���\n");
		printf("2. ����\n");
		getint(&findmode);	//��ȡ����
		if (findmode == 1)	//ģʽ1
			goto findmode1; //���ص����������û���ģʽ
		if (findmode == 2)	//ģʽ2
			return ERROR;	//����
		else				//�����ģʽ�������������
			goto findmode0;
	}
phonemode1:
	printf("����������ֻ�����: ");
	long long telephonenum = 0; //��ŵ绰����
	int phonemode;
	getlonglong(&telephonenum); //��ȡ������ֻ�����

	if (telephonenum != user->data->phonenum) //�绰���벻һ��
	{
		printf("������ֻ����벻��ȷ\n");
	phonemode0:
		printf("1. ���������ֻ�����\n");
		printf("2. ���������û���\n");
		printf("3. ����\n");
		getint(&phonemode); //��ȡ����
		if (phonemode == 1) //ģʽ1
			goto phonemode1;
		else if (phonemode == 2) //ģʽ2
			goto findmode1;
		else if (phonemode == 3) //ģʽ3
			return ERROR;
		else //�����ģʽ������
			goto phonemode0;
	}

	//�ֻ�������ȷ,���´�������
modifymode1:
	do //������������һֱ�����������Ҫ�󣬾�һֱ������ѭ����
	{
		printf("�������µ�����(����6���ַ������20���ַ�): ");
		int length = getstring(MAX_PASSWORDSZ, user->data->password);
		if (length == -1) //����ĳ��ȹ���
			continue;	  //ѭ������
		if (length < 6)	  //����ĳ��ȹ���
		{
			printf("���õ���������6���ַ�������������!\n");
			continue; //ѭ������
		}
		break;
	} while (1);
modifymode2:
	do //������������һֱ�����������Ҫ�󣬾�һֱ������ѭ����
	{
		char str[MAX_PASSWORDSZ + 1] = {0};
		printf("���ٴ�ȷ������(����6���ַ������20���ַ�): ");
		int length = getstring(MAX_PASSWORDSZ, str);  //��ȡ���볤��
		int flag = strcmp(str, user->data->password); //�Ƚ�ǰ�������Ƿ�һ��
		if (flag == 0)								  //����һ���˳�ѭ��
		{
			break;
		}
		else //���벻һ��
		{
			printf("�����������\n");
		modifymode0:
			printf("1. ������������\n");
			printf("2. ����ȷ������\n");
			printf("��ѡ����: "); //���û�ѡ����
			int mode = 0;
			mode = getint(&mode);
			if (mode == 1) //������������
			{
				goto modifymode1; //�ص����������ҳ��
			}
			else if (mode == 2) //����ȷ������
			{
				goto modifymode2; //�ص�����ȷ�������ҳ��
			}
			else //û�иù���
			{
				scanf("%*[^\n]%*c"); //��ջ�����
				printf("û�иù���\n");
				printf("��ѡ�����еĹ���!\n");
				goto modifymode0; //�ص�����ȷ�������ҳ��
			}
		}
	} while (1);

	printf("���ĳɹ�\n");
	FileUpdata(L); //�����ļ�����
	return SUCCESS;
}

//�û���¼
//��¼�ɹ��������û��ڵ�
UserNode *LogUser(UserList L, FileType file[], int *n, FileTree *Userrootfile)
{
	char struser[MAX_USERIDSZ + 1] = {0}; //����û���
	int errorflag = 0;					  //�����־λ
	UserList user;
	//�����û���
passwordmode1:
	do
	{
		printf("�û���(������30���ַ�): ");
		if (-1 == getstring(MAX_USERIDSZ, struser)) //������û�������
		{
			continue;
		}
		user = SearchUser(L, struser); //Ѱ���Ƿ��и��û���
		if (user == NULL)			   //�Ҳ������û���
		{
			errorflag = 1; //�����־λ��1
			break;
		}
		else
			break;
	} while (1);

	//��������
	char strpassword[MAX_PASSWORDSZ + 1] = {0};
	do
	{
		printf("����: ");
		int length = getstring(MAX_PASSWORDSZ, strpassword); //��ȡ����
		if (length == -1)									 //�������벻�淶
			continue;
		break;
	} while (1);

	int judgeflag = -1; //�ж�
	if (errorflag == 1) //�û������벻ƥ��
	{
		errorflag = 0; //��־λ��0
		printf("�û����������\n");
	passwordmode3:
		printf("1. ��������\n");
		printf("2. ����\n");
		printf("��ѡ��ģʽ: ");
		int passwordmode = 0;
		if (scanf("%d", &passwordmode))
		{
			if (passwordmode == 1)
			{
				goto passwordmode1;
			}
			else if (passwordmode == 2)
			{
				return NULL;
			}
			else
			{
				scanf("%*[^\n]%*c"); //��ջ�����
				printf("û�иù���,����������\n");
				goto passwordmode3;
			}
		}
		else
		{
			printf("�������\n");
			scanf("%*[^\n]%*c"); //��ջ�����
			goto passwordmode3;
		}
	}
	else
	{
		judgeflag = strcmp(strpassword, user->data->password);
		if (judgeflag == 0) //����������ȷ
		{
			printf("��¼�ɹ�\n");

			ReadFile(file, n, user->data->userfilename);					//��file��ʼ��
			(*Userrootfile) = CreateFileTree(user->data->userid, file, *n); //����һ���������ڵ����û������ļ���
			system("pause");
			return user;
		}
		else
		{
			printf("�����������\n");
		passwordmode0:
			printf("1. ��������\n");
			printf("2. ����\n");
			printf("������ģʽ: ");
			int passwordmode = 0;
			if (scanf("%d", &passwordmode))
			{
				if (passwordmode == 1)
				{
					goto passwordmode1;
				}
				else if (passwordmode == 2)
				{
					return NULL;
				}
				else
				{
					scanf("%*[^\n]%*c"); //��ջ�����
					printf("û�иù���,����������\n");
					goto passwordmode0;
				}
			}
			else
			{
				printf("�������\n");
				scanf("%*[^\n]%*c"); //��ջ�����
				goto passwordmode0;
			}
		}
	}
}
