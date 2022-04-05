#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMEMAXN 100
#define PATHMAXN 1000

typedef struct FileNode
{
    char name[NAMEMAXN]; //�ļ��������ļ�����
    char path[PATHMAXN]; //�ļ����У�·��
    int flag;            //�����ļ������ļ��еı�ʶ->0: �ļ��У�1: �ļ�
    char datetime[20];   //�ļ���������
    int filenumber;      //�ļ��а������ļ����У�����
    FileNode **files;    //�ļ��а������ļ����У��б�
    FileNode *pNode;     //�ϼ�Ŀ¼
} FileNode, *FileTree;
