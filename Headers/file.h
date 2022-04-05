#ifndef FILE_H
#define FILE_H

#define NAMEMAXN 100
#define PATHMAXN 1000
#define FILEMAXN 100 // �ļ�����ഢ���ļ���

typedef struct FileNode
{
    char name[NAMEMAXN]; // �ļ��������ļ�����
    char path[PATHMAXN]; // �ļ����У�·��
    int flag;            // �����ļ������ļ��еı�ʶ->0: �ļ��У�1: �ļ�
    char datetime[20];   // �ļ���������
    int filenumber;      // �ļ��а������ļ����У�����
    FileTree *files;     // �ļ��а������ļ����У��б�
    FileTree pNode;      // �ϼ�Ŀ¼
    char tag[3][30];     // ����֧��3����ǩ��ǩ
} FileNode, *FileTree;

/**
 * @brief ��ʼ���ļ�ϵͳ���½�һ����Ŀ¼�ڵ�ROOT
 * 
 * @return FileTree 
 */
FileTree init();

#endif