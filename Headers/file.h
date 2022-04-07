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
    char name[NAMEMAXN];           // �ڵ��ļ��������ļ�����
    struct FileNode *fchild, *sbi; // ָ���һ���ӽڵ����һ���ֵܽڵ��ָ��
} FileNode, *FileTree;

void UsersOperation(char *filename);
void ShowInfo();

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char *getDateTime();

/**
 * @brief �����������ݵ����鱣�浽�ļ���ȥ
 *
 * @param file �������ݵ�����
 * @param n ���������
 * @param filename �û��ļ�����
 */
void SaveFile(FileType file[], int n, char *filename);

/**
 * @brief ���ļ��ж�ȡ���������ݵ�����
 *
 * @param file
 * @param n ���֣���ʾ����ĳ��ȣ��ĵ�ֵַ
 * @param filename �û��ļ�����
 */
void ReadFile(FileType file[], int *n, char *filename);

/**
 * @brief Create a File Tree object
 *
 * @param root ���ڵ㴫��"Root"
 * @param file
 * @param n
 * @return FileTree
 */
FileTree CreateFileTree(char *root, FileType file[], int n);

/**
 * @brief ls: ��ʾ��ǰĿ¼�����еıʼ��ļ����ļ���
 *
 * @param pNode
 */
void ls(FileTree pNode);

/**
 * @brief ls -a: ������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�
 *
 * @param pNode
 * @param level = -1
 */
void ls_a(FileTree pNode, int level);

/**
 * @brief rm <�ʼ��ļ���>���Աʼ��ļ�����ɾ��
 *
 * @param pNode
 * @param filename
 * @param file ����
 * @param n ���鳤��
 */
void rm(FileTree pNode, char *filename, FileType file[], int *n);

/**
 * @brief rm -r <�ʼ��ļ�������>��ɾ���ƶ��ļ��Լ����ڲ���������
 *
 * @param pNode
 * @param dirname
 * @param file ����
 * @param n ���鳤��
 */
void rm_r(FileTree pNode, char *filename, FileType file[], int *n);
void PostOrderTraverse(FileTree pNode, FileType file[], int *n);
void DeleteNode(FileTree pNode, FileType file[], int *n);

/**
 * @brief mkdir<�ʼ��ļ���>: �ڵ�ǰ�ļ���pNode���½��ļ�
 *
 * @param pNode
 * @param filename
 * @param file ����
 * @param n ���鳤��
 */
void mkdir(FileTree pNode, char *filename, FileType file[], int *n);

/**
 * @brief mkdir -r<�ʼ��ļ�����>: �½��ļ���
 *
 * @param pNode
 * @param dirname
 * @param file ����
 * @param n ���鳤��
 */
void mkdir_r(FileTree pNode, char *filename, FileType file[], int *n);

#endif