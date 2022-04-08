#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Headers/file.h"

void UsersOperation(char *filename)
{
    FileType file[FILEMAXN];
    int n;
    ReadFile(file, &n, filename);
    FileTree root = CreateFileTree("Root", file, n); // ��������rootΪ���ڵ�
    ShowInfo();
    char operation[NAMEMAXN];
    while (gets(operation) != NULL) //��ȡ����
    {                               // �ָ����������Ͳ���
        char *op_1 = strtok(operation, " ");
        char *op_2 = strtok(NULL, " ");
        char *op_3 = strtok(NULL, " ");
        char *op_4 = strtok(NULL, " ");
        if (strcmp(op_1, "ls") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "cd") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "mv") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "rm") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "mkdir") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "sort") == 0)
        {
            /* code */
        }
        else if (strcmp(op_1, "tag") == 0)
        {
            /* code */
        }
        else
        {
            printf("ERROR:��֧��\"%s\"����, ����������!\n", operation);
        }
    }
}

void ShowInfo()
{
    system("cls");
    printf("  ******************************************************\n\n");
    printf("  *                ��ӭʹ�ñʼǹ���ϵͳ                 *\n \n");
    printf("  ******************************************************\n\n");
    printf("  ��ϵͳĿǰ֧�����¹��ܣ�\n");
    printf("  1.��ʾ��ǰĿ¼�����еıʼ��ļ�: ls\n");
    printf("  2.������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�: ls -a\n");
    printf("  3.��ʾ����ָ���ļ������е�����: ls <�ļ���·��>\n");
    printf("  4.��ʾ����ָ���ļ������еĴ����������ݵ��ļ��������ļ���: ls <�ʼ��ļ���·��> grep ���������ݡ�\n");

    printf("  5.�л�����ǰ·�����ϼ��ļ���: cd ..\n");
    printf("  6.��·���л�Ϊ������������ļ���·��: cd <�ʼ��ļ���·��>\n");

    printf("  7.���ʼ��ļ��ƶ���ָ�����ļ���Ŀ¼��: mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼>\n");
    printf("  8.���ʼ��ļ���������������ԭ�ļ�����ΪĿ���ļ���: mv <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���>\n");
    printf("  9.��ָ���ıʼ��ļ����ƶ���Ŀ���ļ���Ŀ¼��: mv -r <���ƶ����ļ���> <Ŀ���ļ���>\n");

    printf("  10.�Աʼ��ļ�����ɾ��: rm <�ʼ��ļ���>\n");
    printf("  11.ɾ��ָ���ļ����Լ����ڲ���������: rm -r <�ʼ��ļ�������>\n");

    printf("  12.�ڵ�ǰ·�����½��ļ���: mkdir <�ļ���>\n");
    printf("  13.�ڵ�ǰ·�����½��ļ�: mkdir -r <�ļ�����>\n");

    printf("  14.��ָ���ļ����ڵıʼ��ļ����ļ�������ĸ��������: sort <�ʼ��ļ�����>\n");

    printf("  15.��ʾָ���ʼ�/�ļ��еı�ǩ: tag <�ʼ��ļ���/�ʼ��ļ�����>\n");
    printf("  16.Ϊָ���ʼ�/�ʼ��ļ������ӱ�ǩ: tag -add <�ʼ��ļ���/�ʼ��ļ�����> ����ǩ���ݡ�\n");
    printf("  17.ɾ��ָ���ʼ�/�ļ��е�ָ����ǩ: tag -del <�ʼ��ļ���/�ʼ��ļ�����> ����ǩ���ݡ�\n");
    printf("  18.�ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���: tag -s ����ǩ���ݡ�\n");
    printf("  19.�����бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��: tag -sa ����ǩ���ݡ�\n");

    printf("  ******************************************************\n");
    printf("  ������ָ��: ");
    system("pause");
}

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char *getDateTime()
{
    static char cur_time[20]; // ���ؾֲ��������ʼ�static
    time_t t;
    struct tm *lt;
    time(&t);
    lt = localtime(&t); //תΪʱ��ṹ
    sprintf(cur_time, "%04d/%02d/%02d %02d:%02d:%02d", lt->tm_year + 1900, lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
    return cur_time;
}

/**
 * @brief �����������ݵ����鱣�浽�ļ���ȥ
 *
 * @param file �������ݵ�����
 * @param n ���������
 * @param filename �û��ļ�����
 */
void SaveFile(FileType file[], int n, char *filename)
{
    int i;
    FILE *fp;
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("�����ļ��޷���");
        return;
    }
    for (i = 0; i < n; i++)
    {
        fwrite(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief ���ļ��ж�ȡ���������ݵ�����
 *
 * @param file
 * @param n ���֣���ʾ����ĳ��ȣ��ĵ�ֵַ
 * @param filename �û��ļ�����
 */
void ReadFile(FileType file[], int *n, char *filename)
{
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        *n = 0;
        printf("  ");
        return;
    }
    fseek(fp, 0, SEEK_END);         // �ض�λ���ϵ��ļ�ָ��,��fpָ���˻ص����ļ���β0�ֽڴ�
    long length = ftell(fp);        // ���ú���ftell()��õ�ǰλ��������ļ��׵�λ�ƣ���λ��ֵ�����ļ������ֽ���
    rewind(fp);                     // ��λ��ָ������ָ���ļ��Ŀ�ͷ
    *n = length / sizeof(FileType); // �õ�һ���ж��ٸ��ṹ����
    for (int i = 0; i < *n; i++)
    {
        fread(&file[i], sizeof(FileType), 1, fp);
    }
    fclose(fp);
}

/**
 * @brief ��������ȡ�����鹹��һ����
 *
 * @param root ���ڵ㴫��"Root"
 * @param file
 * @param n
 * @return FileTree
 */
FileTree CreateFileTree(char *root, FileType file[], int n)
{
    FileTree bt = (FileTree)malloc(sizeof(FileNode));
    strcpy(bt->name, root);
    bt->fchild = bt->sbi = NULL;
    int i, j;
    for (i = 0; i < n && strcmp(file[i].fathername, root) != 0; i++)
    {
        ;
    }
    if (i < n) // ���ҵ���һ�����ڵ�����Ϊroot��
    {
        FileTree p = (FileTree)malloc(sizeof(FileNode)); // ����һ����ʱָ��
        p->fchild = p->sbi = NULL;
        strcpy(p->name, file[i].name);
        bt->fchild = p;

        for (j = i; j < n; j++)
        {
            if (strcmp(file[j].fathername, root) == 0)
            {
                p = CreateFileTree(file[j].name, file, n); //! �ݹ�
                p = p->sbi;
            }
        }
    }
    return bt;
}

/**
 * @brief ls: ��ʾ��ǰĿ¼�����еıʼ��ļ����ļ���
 *
 * @param pNode
 */
void ls(FileTree pNode)
{
    FileTree p = pNode->fchild;
    for (; p; p = p->sbi)
    {
        printf("%s ", p->name);
    }
    printf("\n");
}

//! ��״�ṹ��ʾ
/**
 * @brief ls -a: ������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�
 *
 * @param pNode
 * @param level = -1
 */
void ls_a(FileTree pNode, int level)
{
    if (strcmp(pNode->name, "Root")) // �׽ڵ㶨��Ϊ������ΪRoot
    {
        printf("%s\n", pNode->name);
    }
    else
    {

        for (int i = 0; i < level; i++)
        {
            printf("|    ");
        }
        printf("|---<%s>\n", pNode->name);
    }
    if (pNode->fchild) // �����ӽڵ�
    {
        ls_a(pNode->fchild, level + 1); // �ݹ����
    }
    if (pNode->sbi)
    {
        ls_a(pNode->sbi, level);
    }
    return;
}

/**
 * @brief ls <�ʼ��ļ���·��>����ʾ����ָ���ļ������е�����(�ӱʼ��ļ��кͱʼ��ļ�)
 * @brief Ŀǰֻ֧�־���·��
 *
 * @param dirpath �����·������
 * @param file ����
 * @param pNode ��Ҫ����Root�ڵ�
 * @param n ���鳤��
 */
void ls_dir(char *dirpath, FileType file[], FileTree pNode, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(file[i].path, dirpath))
        {
            FileTree b = PreOrderFindNode_Path(pNode, file[i].name); // ����ƥ��Ľڵ�
            ls(b);                                                   // ����ls()��������ӡ·���µ���������
        }
        else
        {
            printf("δ���ҵ���·��\n");
        }
    }
}
//! δ���
/**
 * @brief ����������ݹ����ƥ��Ľڵ�
 *
 * @param pNode
 * @param filename
 * @return FileTree
 */
FileTree PreOrderFindNode_Path(FileTree pNode, char *filename)
{
}

/**
 * @brief rm <�ʼ��ļ���>���Աʼ��ļ�����ɾ��
 *
 * @param pNode
 * @param filename
 * @param file ����
 * @param n ���鳤��
 */
void rm(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (file[i].fathername != pNode->name)
            {
                printf("���ļ����ڵ�ǰĿ¼��\n");
                return;
            }

            if (file[i].flag == 0)
            {
                printf("����һ���ļ���,��Ҫɾ��,�����롰rm -r <Ҫɾ���ıʼ��ļ�������>��\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // ������״��ĵ�һ���ӽڵ�
            {
                pNode->fchild = p->sbi;
                free(p);
            }
            else // ������ֵܽڵ㣬���޽ӡ�
            {
                FileTree q = p->sbi;
                while (q->sbi)
                {
                    if (strcmp(q->name, filename) == 0)
                    {
                        p->sbi = q->sbi;
                        free(q);
                        break;
                    }
                    else
                    {
                        p = p->sbi;
                        q = q->sbi;
                    }
                }
            }

            for (int j = i; j < *n; j++) // ���������ǰ��
            {
                file[j] = file[j + 1];
            }

            (*n)--;
        }
    }
    printf("δ���ҵ����ļ�\n");
    return;
}

/**
 * @brief rm -r <�ʼ��ļ�������>��ɾ���ƶ��ļ��Լ����ڲ���������
 *
 * @param pNode
 * @param dirname
 * @param file ����
 * @param n ���鳤��
 */
void rm_r(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            if (file[i].fathername != pNode->name)
            {
                printf("���ļ����ڵ�ǰĿ¼��\n");
                return;
            }

            if (file[i].flag == 1)
            {
                printf("����һ���ļ�,��Ҫɾ��,�����롰rm <Ҫɾ���ıʼ��ļ���>��\n");
                return;
            }

            FileTree p = pNode->fchild;
            if (strcmp(p->name, filename) == 0) // ������״��ĵ�һ���ӽڵ�
            {
                pNode->fchild = p->sbi;
                PostOrderTraverse(p, file, n);
                free(p);
            }
            else // ������ֵܽڵ㣬���޽ӡ�
            {
                FileTree q = p->sbi;
                while (q->sbi)
                {
                    if (strcmp(q->name, filename) == 0)
                    {
                        p->sbi = q->sbi;
                        PostOrderTraverse(q, file, n);
                        free(q);
                        break;
                    }
                    else
                    {
                        p = p->sbi;
                        q = q->sbi;
                    }
                }
            }
        }
    }
    printf("δ���ҵ����ļ�\n");
    return;
}
void PostOrderTraverse(FileTree pNode, FileType file[], int *n)
{
    if (pNode)
    {
        PostOrderTraverse(pNode->fchild, file, n);
        PostOrderTraverse(pNode->sbi, file, n);
        DeleteNode(pNode, file, n);
    }
    return; //������Ϊ�գ�������һ��
}
void DeleteNode(FileTree pNode, FileType file[], int *n)
{

    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, pNode->name) == 0)
        {
            for (int j = i; j < *n; j++) // ���������ǰ��
            {
                file[j] = file[j + 1];
            }

            (*n)--;
        }
    }
}

/**
 * @brief mkdir<�ʼ��ļ���>: �ڵ�ǰ�ļ���pNode���½��ļ�
 *
 * @param pNode
 * @param filename
 * @param file ����
 * @param n ���鳤��
 */
void mkdir(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("���ļ����У������Ѵ���\n");
            return;
        }

        if (strcmp(file[i].name, pNode->name) == 0)
        {
            if (file[i].flag == 1)
            {
                printf("����һ���ļ����޷��ڴ�Ŀ¼�´����ļ�\n");
                return;
            }
            strcpy(file[*n].fathername, pNode->name);
            strcpy(file[*n].name, filename);
            file[*n].flag = 1; // 1��ʾ����һ���ļ�
            strcpy(file[*n].datetime, getDateTime());
            FileTree p = pNode->fchild;
            if (p)
            {
                while (p->sbi)
                {
                    p = p->sbi;
                }
                strcpy(p->sbi->name, filename);
            }
            else
            {
                strcpy(p->name, filename);
            }

            (*n)++;
        }
    }
}

/**
 * @brief mkdir -r<�ʼ��ļ�����>: �½��ļ���
 *
 * @param pNode
 * @param dirname
 * @param file ����
 * @param n ���鳤��
 */
void mkdir_r(FileTree pNode, char *filename, FileType file[], int *n)
{
    for (int i = 0; i < *n; i++)
    {
        if (strcmp(file[i].name, filename) == 0)
        {
            printf("���ļ����У������Ѵ���\n");
            return;
        }

        if (strcmp(file[i].name, pNode->name) == 0)
        {
            if (file[i].flag == 1)
            {
                printf("����һ���ļ����޷��ڴ�Ŀ¼�´����ļ�");
                return;
            }
            strcpy(file[*n].fathername, pNode->name);
            strcpy(file[*n].name, filename);
            // ���ɵ�ǰ·��
            char tmp[PATHMAXN];
            strcpy(tmp, file[i].path);
            strcat(tmp, "\\");
            strcat(tmp, filename);
            strcpy(file[*n].path, tmp);

            file[*n].flag = 0; // 0��ʾ����һ���ļ���
            strcpy(file[*n].datetime, getDateTime());
            FileTree p = pNode->fchild;
            if (p)
            {
                while (p->sbi)
                {
                    p = p->sbi;
                }
                strcpy(p->sbi->name, filename);
            }
            else
            {
                strcpy(p->name, filename);
            }

            (*n)++;
        }
    }
}

/**
 * @brief tag <�ʼ��ļ���/�ʼ��ļ�����> ��ʾ��ǰĿ¼�µ�ָ���ʼ�/�ļ��еı�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ�
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag(FileNode *pNode, char *filename, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0) //�ҵ���ͬ������, ����һ���Ǹ�Ŀ¼�µ�
        {
            if (strcmp(file[i].fathername, pNode->name) == 0) //��ʾ�ڸ�Ŀ¼��
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    printf("��ǩ%d: %s\n", j + 1, file[i].tag[j]); //��ӡ��ǩ
                }
                break;
            }
        }
    }
    if (i == n) //û���ҵ����ļ�(��)
    {
        printf("��Ŀ¼��û��ָ�����ļ�(��)\n");
    }
}

/**
 * @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����> �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ������ӱ�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ�
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_add(FileNode *pNode, char *filename, char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0) //�ҵ���ͬ������, ����һ���Ǹ�Ŀ¼�µ�
        {
            if (strcmp(file[i].fathername, pNode->name) == 0) //��ʾ�ڸ�Ŀ¼��
            {
                if (file[i].tagnum > 2) //��ʾ������ǰ���ı�ǩ����
                {
                    printf("�������ı�ǩ��\n");
                }
                else
                {
                    for (j = 0; j < file[i].tagnum; j++) //Ѱ���Ƿ�����ͬ�ı�ǩ����
                    {
                        if (strcmp(file[i].tag[j], tagname) == 0)
                        {
                            printf("���ʧ��, �ñ�ǩ�Ѵ���\n");
                            break;
                        }
                    }
                    if (j == file[i].tagnum) //û���ҵ���ͬ�ı�ǩ����
                    {
                        strcpy(file[i].tag[j], tagname);
                        file[i].tagnum++;
                        printf("��ӳɹ�\n");
                    }
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("��Ŀ¼��û���ҵ�ָ�����ļ�(��)\n");
    }
}

/**
 * @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����>> ����ǩ���ݡ�: �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ���ɾ��ָ���ı�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ�
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_del(FileNode *pNode, char *filename, char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        if (strcmp(filename, file[i].name) == 0) //�ҵ���ͬ������, ����һ���Ǹ�Ŀ¼�µ�
        {
            if (strcmp(file[i].fathername, pNode->name) == 0) //��ʾ�ڸ�Ŀ¼��
            {
                for (j = 0; j < file[i].tagnum; j++)
                {
                    if (strcmp(file[i].tag[j], tagname) == 0) //�ҵ��ñ�ǩ
                    {
                        file[i].tagnum--;                                  //��ǩ����-1
                        memset(file[i].tag[j], 0, sizeof(file[i].tag[j])); //�������
                        printf("ɾ���ɹ�\n");
                    }
                }
                if (j == file[i].tagnum)
                {
                    printf("û���ҵ��ñ�ǩ\n");
                }
                break;
            }
        }
    }
    if (i == n)
    {
        printf("��Ŀ¼��û���ҵ�ָ�����ļ�(��)\n");
    }
}

/**
 * @brief tag-s ����ǩ���ݡ��� ���ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_s(FileNode *pNode, char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++) // �ҵ���ǰ·���µ��ļ�(��)
    {
        if (strcmp(file[i].fathername, pNode->name) == 0) //�ڵ�ǰĿ¼�µ�
        {
            for (j = 0; j < file[i].tagnum; j++)
            {
                if (strcmp(file[i].tag[j], tagname) == 0) //�ҵ���ͬ�ı�ǩ
                {
                    printf("<%s>\n", file[i].name); //��ӡ�ļ�(��)����
                }
            }
        }
    }
}

/**
 * @brief tag-sa ����ǩ���ݡ��� ���ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_sa(char *tagname, FileType file[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < file[i].tagnum; j++)
        {
            if (strcmp(tagname, file[i].tag[j]) == 0) //�ҵ���ͬ���Ƶı�ǩ
            {
                printf("%-20s\t%-20s", file[i].name, file[i].path); //��ӡ�ļ������ļ�·��
            }
        }
    }
}