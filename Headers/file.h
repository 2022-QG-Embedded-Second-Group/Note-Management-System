#ifndef FILE_H
#define FILE_H

#define ERROR   0
#define SUCCESS 1




#define NAMEMAXN 100
#define PATHMAXN 1000
#define FILEMAXN 100 // �ļ�����ഢ���ļ���


//! ������
typedef struct FileType
{
    char fathername[NAMEMAXN]; // ���ڵ�����
    char path[PATHMAXN];       // ����·��
    char name[NAMEMAXN];       // �ļ��������ļ�����
    int flag;                  // �����ļ������ļ��еı�ʶ->0: �ļ��У�1: �ļ�
    char datetime[20];         // �ļ���������
    int tagnum;                // ��ǩ����
    char tag[3][30];           // ����֧��3����ǩ
} FileType;

typedef struct FileNode
{
    char name[NAMEMAXN];           // �ڵ��ļ��������ļ�����
    struct FileNode* fchild, * sbi, *father; // ָ���һ���ӽڵ����һ���ֵܽڵ��ָ��
} FileNode, * FileTree;

//void UsersOperation(char* filename);
//void UsersOperation(int* n, FileType file[], FileTree Userrootfile, , UserNode* user);
void ShowInfo();

/**
 * @brief Get the Date Time object
 *
 * @return char*
 */
char* getDateTime();

/**
 * @brief �����������ݵ����鱣�浽�ļ���ȥ
 *
 * @param file �������ݵ�����
 * @param n ���������
 * @param filename �û��ļ�����
 */
void SaveFile(FileType file[], int n, char* filename);

/**
 * @brief ���ļ��ж�ȡ���������ݵ�����
 *
 * @param file
 * @param n ���֣���ʾ����ĳ��ȣ��ĵ�ֵַ
 * @param filename �û��ļ�����
 */
void ReadFile(FileType file[], int* n, char* filename);

/**
 * @brief Create a File Tree object
 *
 * @param root ���ڵ㴫��"Root"
 * @param file
 * @param n
 * @return FileTree
 */
FileTree CreateFileTree(char* root, FileType file[], int n);

/**
 * @brief ls: ��ʾ��ǰĿ¼�����еıʼ��ļ����ļ���
 *
 * @param pNode
 */
void ls(FileTree pNode);

///**
// * @brief ls -a: ������״�ṹ��ʾ���еıʼ��ļ����Լ��ʼ��ļ�
// *
// * @param pNode
// * @param level = -1
// */
//void ls_a(FileTree pNode, int level);

/**
 * @brief rm <�ʼ��ļ���>���Աʼ��ļ�����ɾ��
 *
 * @param pNode
 * @param filename
 * @param file ����
 * @param n ���鳤��
 */
//void rm(FileTree pNode, char* filename, FileType file[], int* n);

/**
 * @brief rm -r <�ʼ��ļ�������>��ɾ���ƶ��ļ��Լ����ڲ���������
 *
 * @param pNode
 * @param dirname
 * @param file ����
 * @param n ���鳤��
 */
//void rm_r(FileTree pNode, char* filename, FileType file[], int* n);
void PostOrderTraverse(FileTree pNode, FileType file[], int* n);
void DeleteNode(FileTree pNode, FileType file[], int* n);

///**
// * @brief mkdir<�ʼ��ļ���>: �ڵ�ǰ�ļ���pNode���½��ļ�
// *
// * @param pNode
// * @param filename
// * @param file ����
// * @param n ���鳤��
// */
//void mkdir(FileTree* pNode, char* filename, FileType file[], int* n);

///**
// * @brief mkdir -r<�ʼ��ļ�����>: �½��ļ���
// *
// * @param pNode
// * @param dirname
// * @param file ����
// * @param n ���鳤��
// */
//void mkdir_r(FileTree* pNode, char* filename, FileType file[], int* n);


/**
 * @brief tag <�ʼ��ļ���/�ʼ��ļ�����> ��ʾ��ǰĿ¼�µ�ָ���ʼ�/�ļ��еı�ǩ
 *
 * @param pNode,��ǰĿ¼�Ľڵ�
 * @param filename ָ�����ļ��л��ļ�
 * @param file  ���û�������
 * @param n    ����ĳ���
 */
void tag(FileNode* pNode, char* filename, FileType file[], int n);

/**
* @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����> �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ������ӱ�ǩ
*
* @param pNode,��ǰĿ¼�Ľڵ�
* @param filename ָ�����ļ��л��ļ�
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_add(FileNode* pNode, char* filename, char* tagname, FileType file[], int n);

/**
* @brief tag-add <�ʼ��ļ���/�ʼ��ļ�����>> ����ǩ���ݡ�: �ڵ�ǰĿ¼��ָ���ıʼ�/�ʼ��ļ���ɾ��ָ���ı�ǩ
*
* @param pNode,��ǰĿ¼�Ľڵ�
* @param filename ָ�����ļ��л��ļ�
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_del(FileNode* pNode, char* filename, char* tagname, FileType file[], int n);

/**
* @brief tag-s ����ǩ���ݡ��� ���ݱ�ǩ���ݣ��ڵ�ǰĿ¼�½��бʼ����������ƥ��ı�ǩ����Ӧ�ıʼ��ļ���
* @param pNode,��ǰĿ¼�Ľڵ�
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_s(FileNode* pNode, char* tagname, FileType file[], int n);

/**
* @brief tag-sa ����ǩ���ݡ��� ���ݱ�ǩ���ݣ������бʼǽ������������ƥ��ı�ǩ����Ӧ�ıʼǵ��ļ����Լ�����·��
* @param tagname ��ǩ������
* @param file  ���û�������
* @param n    ����ĳ���
*/
void tag_sa(char* tagname, FileType file[], int n);

///*************************��Ҫ����*********************************************/
///**
//* @brief mv <�ʼ��ļ���> <�ʼ��ļ���Ŀ¼>�����ʼ��ļ��ƶ���ָ�����ļ���Ŀ¼�¡�
//*        mv <�ʼ�ԭ�ļ���> <�ʼ�Ŀ���ļ���>�����ʼ��ļ���������������ԭ�ļ�����ΪĿ���ļ�����
//* @param file        ���û�������
//* @param n           ���鳤��
//* @param pfile       �ļ�������
//* @param destination Ŀ���ļ�������
//* @param bt          �û�����
//* @param user        �û��ڵ�
//*/
//void mv(FileType file[], int n, char* pfile, char* destination, FileTree bt, UserNode* user);
//
///*************************��Ҫ����*********************************************/
///**
//* @brief mv -r <���ƶ����ļ���> <Ŀ���ļ���>����ָ���ıʼ��ļ����ƶ���Ŀ���ļ���Ŀ¼�¡�
//* @param file        ���û�������
//* @param n           ���鳤��
//* @param movefile    ���ƶ��ļ�������
//* @param destination Ŀ���ļ�������
//* @param bt          �û�����
//* @param user        �û��ڵ�
//*/
//void mv_r(FileType file[], int n, char* movefile, char* destination, FileTree bt, UserNode* user);




typedef int Status;
typedef FileTree ElemType;

typedef  struct StackNode
{
    ElemType data;
    struct StackNode* next;
}StackNode, * LinkStackPtr;


typedef  struct  LinkStack
{
    LinkStackPtr top;
    int	count;
}LinkStack;



//��ջ
Status initLStack(LinkStack* s);//��ʼ��ջ
Status isEmptyLStack(LinkStack* s);//�ж�ջ�Ƿ�Ϊ��
Status getTopLStack(LinkStack* s, ElemType* e);//�õ�ջ��Ԫ��
Status clearLStack(LinkStack* s);//���ջ
Status destroyLStack(LinkStack* s);//����ջ
Status LStackLength(LinkStack* s, int* length);//���ջ����
Status pushLStack(LinkStack* s, ElemType data);//��ջ
Status popLStack(LinkStack* s, ElemType* data);//��ջ

#endif