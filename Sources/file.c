#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Headers/file.h"

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char *getDateTime()
{
    char cur_time[20];
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
 * @brief Create a File Tree object
 *
 * @param root
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
 * @brief ��ʼ���ļ�ϵͳ���½�һ����Ŀ¼�ڵ�ROOT
 *
 * @return FileTree
 */
/*FileTree init()
{
    FileTree root;
    root = (FileTree)malloc(sizeof(FileNode)); // �����ڴ�ռ�
    strcpy(root->name, "ROOT");                // ����
    strcpy(root->path, "ROOT");                // ����·��
    root->flag = 0;                            // ��ʶΪ�ļ���
    root->filenumber = 0;                      // ��ʼ�����ļ���Ϊ0
    root->files = NULL;                        // �����б�Ϊ��
    root->pNode;                               // ���ϼ�Ŀ¼
    return root;                               // ���س�ʼ���Ľڵ�
}*/

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
/*void ls(FileTree pNode)
{
    for (int i = 0; i < pNode->filenumber; i++)
    {
        printf("%s ", pNode->files[i]->name);
    }
    printf("\n");
}*/

//! �д����⣬��״�ṹ�����ʾ
/**
 * @brief ls -a: ������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�
 *
 * @param pNode
 */
void ls_a(FileTree pNode)
{
    FileTree p = pNode->fchild;
    for (; p; p = p->sbi)
    {
        printf("%s ", p->name);
        if (p->fchild) // �����ӽڵ�
        {
            printf("<");
            ls_a(p->fchild); // �ݹ����
            printf(">");
        }
    }
    printf("\n");
}
/*void ls_a(FileTree pNode)
{
    for (int i = 0; i < pNode->filenumber; i++)
    {
        printf("%s ", pNode->files[i]->name);
        if (pNode->files[i]->flag == 0) // ������ļ���
        {
            printf("<");
            ls_a(pNode->files[i]); // �ݹ����
            printf(">");
        }
        printf("\n");
    }
    printf("\n");
}*/

/**
 * @brief ls <�ʼ��ļ���·��>����ʾ����ָ���ļ������е�����(�ӱʼ��ļ��кͱʼ��ļ�)
 * ���Բ��ñ���
 */

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
                while (p->sbi->sbi)
                {
                    if (strcmp(p->sbi->name, filename) == 0)
                    {
                        p->sbi=p->sbi->sbi;
                        free(p->sbi);
                        break;
                    }
                }
            }

            for (int j = i; j < *n; j++) // ���������ǰ��
            {
                file[j]=file[j+1];
            }
            
            (*n)--;
        }
    }
    printf("δ���ҵ����ļ�\n");
    return;
}
/*int rm(FileTree pNode, char *filename)
{
    for (int i = 0; i < pNode->filenumber; i++)
    {
        if (!strcmp(pNode->files[i]->name, filename)) // �ļ������
        {
            free(pNode->files[i]);                            // ɾ���ڵ�
            for (int j = i; j < (pNode->filenumber - 1); j++) // ����Ľڵ�ǰ��
            {
                pNode->files[j] = pNode->files[j + 1];
            }
            pNode->filenumber--;
            return 1;
        }
    }
    return 0;
}*/

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
                free(p);
            }
            else // ������ֵܽڵ㣬���޽ӡ�
            {
                while (p->sbi->sbi)
                {
                    if (strcmp(p->sbi->name, filename) == 0)
                    {
                        p->sbi=p->sbi->sbi;
                        free(p->sbi);
                        break;
                    }
                }
            }

            for (int j = i; j < *n; j++) // ���������ǰ��
            {
                file[j]=file[j+1];
            }
            
            (*n)--;
        }
    }
    printf("δ���ҵ����ļ�\n");
    return;
}
/*int rm_r(FileTree pNode, char *dirname)
{
    for (int i = 0; i < pNode->filenumber; i++)
    {
        if (!strcmp(pNode->files[i]->name, dirname)) // �ļ������
        {
            deleteFolder_Recursion(pNode->files[i]); //! ɾ�����ڲ���������,�ݹ�

            free(pNode->files[i]);                            // ɾ���ڵ�
            for (int j = i; j < (pNode->filenumber - 1); j++) // ����Ľڵ�ǰ��
            {
                pNode->files[j] = pNode->files[j + 1];
            }
            pNode->filenumber--;
            return 1;
        }
    }
    return 0;
}*/
/**
 * @brief �ݹ�ɾ���ļ�������������
 *
 * @param pNode
 */
/*void deleteFolder_Recursion(FileTree pNode)
{
    if (pNode->flag == 1) // ������ļ�,ɾ���������ݹ�
    {
        free(pNode);
        return;
    }
    for (int i = 0; i < pNode->filenumber; i++)
    {
        deleteFolder_Recursion(pNode->files[i]);
    }
    return;
}*/

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
/*void mkdir(FileTree pNode, char *filename)
{
    if (pNode->files == NULL) // ����ǰ�ļ���pNode���¼��б�����ڴ�
    {
        pNode->files = (FileTree *)malloc(sizeof(FileTree) * FILEMAXN);
    }
    pNode->files[pNode->filenumber] = (FileTree)malloc(sizeof(FileNode));

    FileTree dir = pNode->files[pNode->filenumber++];
    strcpy(dir->name, filename); // �ļ���
    dir->flag = 1;               // ��ʶ1Ϊ�ļ�
    dir->filenumber = 0;         // �����������ļ����У�
    dir->files = NULL;           // �ް����ļ��б�
    dir->pNode = pNode;          // �ϼ�Ŀ¼
}*/

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
/*void mkdir_r(FileTree pNode, char *dirname)
{
    if (pNode->files == NULL) // ����ǰ�ļ���pNode���¼��б�����ڴ�
    {
        pNode->files = (FileTree *)malloc(sizeof(FileTree) * FILEMAXN);
    }
    pNode->files[pNode->filenumber] = (FileTree)malloc(sizeof(FileNode));

    FileTree dir = pNode->files[pNode->filenumber++];
    strcpy(dir->name, dirname); // �ļ�����
    dir->flag = 0;              // ��ʶ0Ϊ�ļ���
    dir->filenumber = 0;        // �����������ļ����У�
    dir->files = NULL;          // �ް����ļ��б�
    dir->pNode = pNode;         // �ϼ�Ŀ¼
                                // ���ɵ�ǰ·��
    char tmp[PATHMAXN];
    strcpy(tmp, pNode->path);
    strcat(tmp, "\\");
    strcat(tmp, dirname);
    strcpy(dir->path, tmp);
}*/
