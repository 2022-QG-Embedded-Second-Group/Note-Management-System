#ifndef FILE_H
#define FILE_H

#define NAMEMAXN 100
#define PATHMAXN 1000
#define FILEMAXN 200 // �ļ�����ഢ���ļ���

//! ������
typedef struct FileType
{
    char fathername[NAMEMAXN]; // ���ڵ�����
    char name[NAMEMAXN];       // �ļ��������ļ�����
    char path[PATHMAXN];       // �ļ����У�·��
    int flag;                  // �����ļ������ļ��еı�ʶ->0: �ļ��У�1: �ļ�
    char datetime[20];         // �ļ���������
    int tagnum;                // ��ǩ����
    char tag[3][30];           // ����֧��3����ǩ
} FileType;
typedef struct FileNode
{
    char name[NAMEMAXN];           // �ڵ��ļ��������ļ�����
    struct FileNode *father,*fchild, *sbi; // ָ���ڵ㡢��һ���ӽڵ����һ���ֵܽڵ��ָ��
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
 * @brief ls <�ʼ��ļ���·��>����ʾ����ָ���ļ������е�����(�ӱʼ��ļ��кͱʼ��ļ�)
 * //!Ŀǰֻ֧�־���·��
 *
 * @param dirpath �����·������
 * @param file ����
 * @param pNode ��Ҫ����Root�ڵ�
 * @param n ���鳤��
 */
void ls_dir(char *dirpath, FileType file[], FileTree pNode, int n);

/**
 * @brief ͨ��file[i].name��pNode->nameƥ��
 * ����������ݹ����ƥ��Ľڵ�
 *
 * @param pNode
 * @param filename
 * @param b ��Ҫ��ȡ��Ŀ��ڵ�
 */
void PreOrderFindNode_Path(FileTree pNode, char *filename, FileTree b);

/**
 * @brief ls <�ʼ��ļ���·��> grep ���������ݡ�����ʾ����ָ���ļ������еĴ�
���������ݵ��ļ��������ļ���
 *
 * @param dirpath �ʼ��ļ���·��
 * @param SearchContent ��������
 * @param file ����
 * @param pNode ��Ҫ����Root�ڵ�
 * @param n ���鳤��
 */
void ls_grep(char *dirpath, char *SearchContent, FileType file[], FileTree pNode, int n);

/**
 * @brief ģ�������ж��Ƿ����ɸѡ����
 *
 * @param key �ؼ���
 * @param str �����ҵ��ַ���
 * @return int 1Ϊ����,0������
 */
int result_mohu(const char *key, char *str);

/**
 * @brief cd ..����·���л�Ϊ��ǰĿ¼�ĸ�Ŀ¼.���Ǹ�Ŀ¼���򲻽����л�
 * ���ڲ����������ж��ٽ��е��ã��ǵ������ǰ�ڵ�·��Ӵ
 *
 * @param pNode ��ǰ�ڵ�
 * @return FileTree
 */
FileTree cd(FileTree pNode);

/**
 * @brief cd <�ʼ��ļ���·��>����·���л�Ϊ������������ļ���·��
 * //!Ŀǰֻ֧�־���·��
 *
 * @param dirpath �����·������
 * @param file ����
 * @param pNode �Ƚڵ�
 * @param root ��Ҫ����Root�ڵ�
 * @param n ���鳤��
 * @return FileTree ���ؽڵ�
 */
FileTree cd_dir(char *dirpath, FileType file[],FileTree pNode, FileTree root, int n);

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

/**
 * @brief tag <�ʼ��ļ���/�ʼ��ļ�����> ��ʾ��ǰĿ¼�µ�ָ���ʼ�/�ļ��еı�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ�
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag(FileNode *pNode, char *filename, FileType file[], int n);

/**
 * @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����> �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ������ӱ�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ�
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_add(FileNode *pNode, char *filename, char *tagname, FileType file[], int n);

/**
 * @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����>> ����ǩ���ݡ�: �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ���ɾ��ָ���ı�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ�
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_del(FileNode *pNode, char *filename, char *tagname, FileType file[], int n);

/**
 * @brief tag-s ����ǩ���ݡ��� ���ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_s(FileNode *pNode, char *tagname, FileType file[], int n);

/**
 * @brief tag-sa ����ǩ���ݡ��� ���ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��
 * @param tagname ��ǩ������
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag_sa(char *tagname, FileType file[], int n);

#endif