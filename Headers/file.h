#ifndef FILE_H
#define FILE_H

#define NAMEMAXN 100
#define PATHMAXN 1000
#define FILEMAXN 100 // �ļ�����ഢ���ļ���

//! ��һ��
/* typedef struct FileNode
{
    char name[NAMEMAXN]; // �ļ��������ļ�����
    char path[PATHMAXN]; // �ļ����У�·��
    int flag;            // �����ļ������ļ��еı�ʶ->0: �ļ��У�1: �ļ�
    char datetime[20];   // �ļ���������
    int filenumber;      // �ļ��а������ļ����У�����
    FileTree *files;     // �ļ��а������ļ����У��б�
    FileTree pNode;      // �ϼ�Ŀ¼
    char tag[3][30];     // ����֧��3����ǩ
} FileNode, *FileTree; */

//! �ڶ���
/* typedef struct Elem
{
    char name[NAMEMAXN]; // �ļ��������ļ�����
    char path[PATHMAXN]; // �ļ����У�·��
    char datetime[20];   // �ļ���������
    char tag[3][30];     // ����֧��3����ǩ
} Elem;
typedef struct Node
{
    Elem data;       // �ڵ�����
    Tree child, sbi; // ָ���һ���ӽڵ����һ���ֵܽڵ��ָ��
} Node, *Tree; */

//! ������
typedef struct FileType
{
    char fathername[NAMEMAXN]; // ���ڵ�����
    char name[NAMEMAXN];       // �ļ��������ļ�����
    int flag;                  // �����ļ������ļ��еı�ʶ->0: �ļ��У�1: �ļ�
    char datetime[20];         // �ļ���������
    char tag[3][30];           // ����֧��3����ǩ
} FileType;
typedef struct FileNode
{
    char name[NAMEMAXN];  // �ڵ��ļ��������ļ�����
    FileTree fchild, sbi; // ָ���һ���ӽڵ����һ���ֵܽڵ��ָ��
} FileNode, *FileTree;

#endif