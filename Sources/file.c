#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/file.h"

/**
 * @brief ��ʼ���ļ�ϵͳ���½�һ����Ŀ¼�ڵ�ROOT
 * 
 * @return FileTree 
 */
FileTree init()
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
}

/**
 * @brief ls: ��ʾ��ǰĿ¼�����еıʼ��ļ����ļ���
 * 
 * @param pNode 
 */
void ls(FileTree pNode)
{
    for (int i = 0; i < pNode->filenumber; i++)
    {
        printf("%s ", pNode->files[i]->name);
    }
    printf("\n");
}

//! �д�����
/**
 * @brief ls -a: ������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�
 * 
 * @param pNode 
 */
void ls_a(FileTree pNode)
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
}

/**
 * @brief ls <�ʼ��ļ���·��>����ʾ����ָ���ļ������е�����(�ӱʼ��ļ��кͱʼ��ļ�)
 * 
 */

/**
 * @brief mkdir<�ʼ��ļ���>: �ڵ�ǰ�ļ���pNode���½��ļ�
 * 
 * @param pNode 
 * @param filename 
 */
void mkdir(FileTree pNode, char *filename)
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
}

/**
 * @brief mkdir -r<�ʼ��ļ�����>: �½��ļ���
 * 
 * @param pNode 
 * @param dirname 
 */
void mkdir_r(FileTree pNode, char *dirname)
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
}
